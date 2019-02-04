# TD2-OpenMP
TD 2 de OpenMP, Sema31, Cartographie et réduction de vecteurs de caractères

Le fichier `main.cpp` contient le code pour la question 2.6, en particulier les méthodes
`underParallelLetterCount(char*** mats, int n, int height, int width, int** results)` et
`displayLetterCounts(char*** mats, int n, int height, int width)`.

Pour le compiler, on a utilisé g++ :
`$ g++ -fopenmp -o out main.cpp`

Il en sort le fichier `out` qui est l'exécutable.

Ce programme s'éxecute de la façon suivante : 
`$ out nombre_de_threads_OpenMP nombre_de_lignes_de_la_matrice nombre_de_colonnes_de_la_matrice
nombre_de_lignes_de_chaque_matrice_issue_du_decoupage nombre_de_colonnes_de_chaque_matrice_issue_du_decoupage`

Il donne en sortie la matrice générée, chaque sous matrice issue du découpage de la matrice en sous-matrices et, dans le
même ordre, le comptage des lettres de chaque sous-matrice.