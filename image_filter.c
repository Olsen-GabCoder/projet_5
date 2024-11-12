#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <opencv2/opencv.hpp>

#define NUM_THREADS 4  // Nombre de threads à utiliser pour le traitement en parallèle

// Structure pour transmettre les données aux threads
typedef struct {
    cv::Mat *image;
    int start_row;
    int end_row;
} ThreadData;

// Fonction qui applique un flou moyen sur une section de l'image
void apply_blur_filter(cv::Mat &image, int start_row, int end_row) {
    for (int i = start_row; i < end_row; i++) {
        for (int j = 0; j < image.cols; j++) {
            cv::Vec3b &pixel = image.at<cv::Vec3b>(i, j);
            // Applique une moyenne des couleurs des canaux pour créer un effet de flou
            pixel[0] = (pixel[0] + pixel[1] + pixel[2]) / 3;
            pixel[1] = pixel[0];
            pixel[2] = pixel[0];
        }
    }
}

// Fonction exécutée par chaque thread
void *thread_function(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    apply_blur_filter(*data->image, data->start_row, data->end_row);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <input_image> <output_image>\n", argv[0]);
        return -1;
    }

    // Charger l'image
    cv::Mat image = cv::imread(argv[1]);
    if (image.empty()) {
        printf("Erreur lors du chargement de l'image.\n");
        return -1;
    }

    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];
    int rows_per_thread = image.rows / NUM_THREADS;

    // Diviser l'image en sections et créer les threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].image = &image;
        thread_data[i].start_row = i * rows_per_thread;
        thread_data[i].end_row = (i == NUM_THREADS - 1) ? image.rows : (i + 1) * rows_per_thread;
        pthread_create(&threads[i], NULL, thread_function, (void *)&thread_data[i]);
    }

    // Attendre que tous les threads terminent leur traitement
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Sauvegarder l'image modifiée
    if (cv::imwrite(argv[2], image)) {
        printf("Image filtrée sauvegardée sous : %s\n", argv[2]);
    } else {
        printf("Erreur lors de la sauvegarde de l'image.\n");
    }

    return 0;
}