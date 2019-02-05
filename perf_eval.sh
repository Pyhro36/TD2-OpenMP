#!/bin/bash

# realise l'evaluation des performances par la generation de deux CSV, un de passage a l'echelle faible et l'autre de
# passage a l'echelle fort

# Le nombre n d'iterations qu'est lance chaque parametrage du programme
ITERATIONS=7

# La mise a l'echelle maximale en nombre de coeur, pour le passage a l'echelle fort et faible
MAX_SCALING=4

# la nombre de lignes de la matrice de lettres (hauteur) de depart
START_HEIGHT=200

# la nombre de colonnes de la matrice de lettres (largeur) de depart
START_WIDTH=100

# la nombre de lignes des sous-matrices issues du decoupage du probleme (sous-hauteur) de depart
START_UNDER_HEIGHT=20

# la nombre de colonnes de la matrice de lettres (sous-largeur) de depart
START_UNDER_WIDTH=10

# le nom du fichier de resultats du passage à l'échelle fort
STRONG_SCALING_FILE="passage_a_lechelle_fort.csv"

# le nom du fichier de resultats du passage à l'échelle faible
WEAK_SCALING_FILE="passage_a_lechelle_faible.csv"

# l entete des fichiers CSV, avec le nom des colonnes
HEADER="Nombre de coeurs,Hauteur,Largeur,Sous-Hauteur,Sous-Largeur,t1(ms),t2(ms),t3(ms),t4(ms),t5(ms),t6(ms),t7(ms),Moyenne(ms)"

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

# Effectue le passage a l'echelle fort avec une matrice de START_HEIGHT x START_WIDTH et des sous-matrices de
# START_UNDER_HEIGHT x START_UNDER_WIDTH
function strong_scaling {

    for (( strong_scale=1 ; ${MAX_SCALING}>=${strong_scale} ; strong_scale=${strong_scale} * 2 ))
    do
        echo "executions avec ${strong_scale} threads"
        iter_exec "${strong_scale}" "${START_HEIGHT}" "${START_WIDTH}" "${START_UNDER_HEIGHT}" "${START_UNDER_WIDTH}" "${STRONG_SCALING_FILE}"
    done
}

# Effectue le passage a l'echelle faible en commencant par une matrice de START_HEIGHT x START_WIDTH et des
# sous-matrices de START_UNDER_HEIGHT x START_UNDER_WIDTH et en faisant doubler le nombre de threads une dimension puis
# l'autre
function weak_scaling {

    height=${START_HEIGHT}
    width=${START_WIDTH}
    under_height=${START_UNDER_HEIGHT}
    under_width=${START_UNDER_WIDTH}
    height_growth=0

    for (( weak_scale=1 ; ${MAX_SCALING}>=${weak_scale} ; weak_scale=${weak_scale} * 2 ))
    do
        echo "executions avec ${weak_scale} threads"
        iter_exec "${weak_scale}" "${height}" "${width}" "${under_height}" "${under_width}" "${WEAK_SCALING_FILE}"

        if [[ ${height_growth} == 1 ]]
        then
            (( height*=2 ))
            (( under_height*=2 ))
            height_growth=0
        else
            (( width*=2 ))
            (( under_width*=2 ))
            height_growth=1
        fi
    done
}

# script principal
####################################################
echo "passage a l echelle fort"
echo "${HEADER}" > ${STRONG_SCALING_FILE}
strong_scaling

echo "passage a l echelle faible"
echo "${HEADER}" > ${WEAK_SCALING_FILE}
weak_scaling
####################################################