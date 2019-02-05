# TD2-OpenMP
TD 2 de OpenMP, Sema31, Cartographie et réduction de vecteurs de caractères

Le fichier `main.cpp` contient le code pour la question 2.7, en particulier la méthode
`parallelReduce(int** letterCounts, int n, int* result)`.

Pour le compiler, on a utilisé g++ :
`$ g++ -fopenmp -o out main.cpp`
sauf dans le cas ou l'on veut un code non parallelisé où dans ce cas on a compilé sans l'option `-fopenmp`

Il en sort le fichier `out` qui est l'exécutable.

Ce programme s'éxecute de la façon suivante : 
`$ out nombre_de_threads_OpenMP nombre_de_lignes_de_la_matrice nombre_de_colonnes_de_la_matrice
nombre_de_lignes_de_chaque_matrice_issue_du_decoupage nombre_de_colonnes_de_chaque_matrice_issue_du_decoupage`

Il donne en sortie : la matrice générée aléatoirement si la ligne 143 a été décommentée, le comptage des occurences de
chaque lettre dans la matrice si la ligne 172 a été décommentée, et le temps d'execution en nanosecondes du calcul de 
comptage par la méthode de découpage.

Pour faire l'évaluation des performances, on a utilisé les scripts `perf_eval.sh` et `perf_eval_non_parallelise.sh`.

`perf_eval.sh` utilise le programme `out` parallelisé pour faire un passage à l'échelle fort et faible.
Il enregistre les résulats dans deux fichiers CSV `passage_a_lechelle_fort.csv` et `passage_a_lechelle_faible.csv` de
format 
`Nombre de coeurs,Hauteur,Largeur,Sous-Hauteur,Sous-Largeur,t1(ms),t2(ms),t3(ms),t4(ms),t5(ms),t6(ms),t7(ms),Moyenne(ms)`
où les colonnes jusqu'à `Sous-Largeur` correspondent au parametre d'exécution, `t1(ms)` à `t7(ms)` sont les temps en ms
des 7 exécutions avec les mêmes paramètres et `Moyenne(ms)` la moyenne de ces temps.

`perf_eval_non_parallelise` utilise le programme `out` non parallelise pour ajouter une série de temps de l'application
non parallelisée aux résultats de passage à l'échelle fort dans `passage_a_lechelle_fort.csv`. Cette série est indiquée
par un nombre de thread égal à 0, pour le distinguer du cas à 1 thread parallelisé.

le fichier `graphes.ods` réunit les résultats pour en tracer les graphes de passage à l'échelle fort et faible.

les fichiers `Rapport-TD1-OpenMP-pllefebvre.{odt|pdf}` sont le rapport final détaillant les explications des choix
d'optimisation, le résumé le l'évaluation des performances et les conclusions associées.