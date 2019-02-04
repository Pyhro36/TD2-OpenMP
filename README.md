# TD2-OpenMP
TD 2 de OpenMP, Sema31, Cartographie et réduction de vecteurs de caractères

Le fichier `main.cpp` contient le code pour la question 2.7, en particulier la méthode
`parallelReduce(`.

Pour le compiler, on a utilisé g++ :
`$ g++ -fopenmp -o out main.cpp`

Il en sort le fichier `out` qui est l'exécutable.

Ce programme s'éxecute de la façon suivante : 
`$ out nombre_de_threads_OpenMP nombre_de_lignes_de_la_matrice nombre_de_colonnes_de_la_matrice
nombre_de_lignes_de_chaque_matrice_issue_du_decoupage nombre_de_colonnes_de_chaque_matrice_issue_du_decoupage`

Il donne en sortie : la matrice générée aléatoirement si la ligne 143 a été décommentée, le comptage des occurences de
chaque lettre dans la matrice si la ligne 172 a été décommentée, et le temps d'execution du calcul de comptage par la
méthode de découpage.