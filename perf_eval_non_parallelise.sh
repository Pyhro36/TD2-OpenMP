#!/bin/bash

# realise l'evaluation des performances du code non parallelise en completant le CSV de passage a l'echelle fort

# Le nombre n d'iterations qu'est lance chaque parametrage du programme
ITERATIONS=7

# La mise a l'echelle maximale en nombre de coeur, pour le passage a l'echelle fort et faible
MAX_SCALING=16

# la nombre de lignes de la matrice de lettres (hauteur) de depart
START_HEIGHT=100

# la nombre de colonnes de la matrice de lettres (largeur) de depart
START_WIDTH=100000

# la nombre de lignes des sous-matrices issues du decoupage du probleme (sous-hauteur) de depart
START_UNDER_HEIGHT=10

# la nombre de colonnes de la matrice de lettres (sous-largeur) de depart
START_UNDER_WIDTH=1000

# le nom du fichier de resultats du passage à l'échelle fort
STRONG_SCALING_FILE="passage_a_lechelle_fort.csv"

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

    for ((exec=0 ; $ITERATIONS - $exec ; exec++))
    do
        echo "execution ${exec} de : ./out ${CORES} ${HEIGHT} ${WIDTH} ${UNDER_HEIGHT} ${UNDER_WIDTH}"
        time=$(./out ${CORES} ${HEIGHT} ${WIDTH} ${UNDER_HEIGHT} ${UNDER_WIDTH})
        time=$(echo "scale=3;$time/1000" | bc | tr -d "\n")
        sum=$(echo "scale=3;$time + $sum" | bc | tr -d "\n")
        printf "${time}," >> ${FILE}
    done

    echo "scale=3;$sum/$ITERATIONS" | bc >> ${FILE}
}


# script principal
####################################################
echo "executions avec 1 thread et non parallelise"
iter_exec "0" "${START_HEIGHT}" "${START_WIDTH}" "${START_UNDER_HEIGHT}" "${START_UNDER_WIDTH}" "${STRONG_SCALING_FILE}"
####################################################