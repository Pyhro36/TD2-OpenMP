# TD2-OpenMP
TD 2 de OpenMP, Sema31, Cartographie et réduction de vecteurs de caractères

Le fichier `main.cpp` contient le code pour la question 2.3, en particulier les méthodes
`letterCount(char** mat, int height, int width, int* result)` et `displayLetterCount(int* letterCounts)`.


Pour le compiler, on a utilisé g++ :
`$ g++ -o out main.cpp`

Il en sort le fichier `out` qui est l'exécutable.

Ce programme s'éxecute de la façon suivante : 
`$ out`

Il affiche en sortie la matrice générée aléatoirement et le comptage du nombre d'occurences de chaque lettre dans
la matrice.