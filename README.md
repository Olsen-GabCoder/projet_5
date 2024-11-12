# Filtrage d'image Concurrent sous Visual Studio

## Description
Ce projet implémente un filtre de flou moyen appliqué sur une image en utilisant des threads sous Windows avec Visual Studio et OpenCV.

## Prérequis
- **Visual Studio** (2019 ou plus récent)
- **OpenCV pour Windows** ([téléchargement](https://opencv.org/releases/))

## Installation d'OpenCV
1. Téléchargez OpenCV et extrayez-le dans `C:\opencv`.
2. Configurez les chemins dans Visual Studio pour utiliser OpenCV :
   - **Include Directories** : `C:\opencv\build\include`
   - **Library Directories** : `C:\opencv\build\x64\vc15\lib`
   - **Path** (variable d'environnement) : `C:\opencv\build\x64\vc15\bin`

## Compilation et Exécution
1. Ouvrez le projet dans Visual Studio.
2. Ajoutez les bibliothèques dans les **Additional Dependencies** :
