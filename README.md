# TD2-OpenMP
TD 2 de OpenMP, Sema31, Cartographie et réduction de vecteurs de caractères

Le fichier `main.cpp` contient le code pour la question 2.4, en particulier les méthodes
`parallelInitLetterMat(char** mat, int height, int width)` et
`parallelLetterCount(char** mat, int height, int width, int* result)`.

Pour le compiler, on a utilisé g++ :
`$ g++ -fopenmp -o out main_mat.cpp`

Il en sort le fichier `out` qui est l'exécutable. 
Ce programme s'éxecute de la façon suivante : 
`$ out nombre_de_threads_OpenMP nombre_de_colonnes_de_la_matrice nombre_de_lignes_de_la_matrice`

Il donne en sortie la matrice générée, le comptage de chaque occurence lettre dans la matrice et le temps de calcul du
comptage