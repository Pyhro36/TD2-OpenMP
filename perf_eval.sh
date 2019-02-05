#!/bin/bash

# realise l'evaluation des performances par la generation de deux CSV, un de passage a l'echelle faible et l'autre de
# passage a l'echelle fort

# Le nombre n d'iterations qu'est lance chaque parametrage du programme
ITERATIONS=4

# Lance n fois le programme out faisant le comptage des lettres dans une matrice avec les parametres indiquees et
# enregistre dans un CSV les resultats des temps d'execution et la moyenne
# $1 : le nombre de coeurs OpenMP
# $2 : le nombre de lignes de la matrice de lettres (hauteur)
# $3 : le nombre de colonnes de la matrice de lettres (largeur)
# $4 : le nombre de lignes des sous-matrices issues du decoupage du probleme (sous-hauteur)
# $5 : le nombre de colonnes des sous-matrices issues du decoupage du probleme (sous-largeur)
# $6 : le nom du fichier CSV constenant les resultats, le format des lignes doit etre "Nombre de coeurs,Hauteur,Largeur,
# Sous-Hauteur,Sous-Largeur,t1(ms),t2(ms),...,tn(ms),Moyenne(ms)"
function iter_exec {

    CORES=$1
    HEIGHT=$2
    WIDTH=$3
    UNDER_HEIGHT=$4
    UNDER_WIDTH=$5
    FILE=$6

    sum=0

    printf "${CORES},${HEIGHT},${WIDTH},${UNDER_HEIGHT},${UNDER_WIDTH}," >> ${FILE}

    for ((i=0 ; $ITERATIONS - $i ; i++))
    do
        time=$(./out ${CORES} ${HEIGHT} ${WIDTH} ${UNDER_HEIGHT} ${UNDER_WIDTH})

        let "sum=$sum + $time"
        printf "${time}," >> ${FILE}
    done

    echo "scale=3;$sum/$ITERATIONS/1000" | bc >> ${FILE}
}

iter_exec 4 10 10 2 5 "test.csv"