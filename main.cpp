#include <iostream>
#include <random>
#include <functional>
#include <chrono>

#include <omp.h>

#define LETTER_NB 26

/**
 * Initialise une matrice avec des lettres aleatoires
 * @param mat la matrice correctement instanciee
 * @param height le nombre de lignes de la matrice
 * @param width le nombre de colonnes de la matrice
 */
void initLetterMat(char** mat, int height, int width);

/**
 * Initialise une matrice avec des lettres aleatoires de maniere parallelise avec OpenMP
 * @param mat la matrice correctement instanciee
 * @param height le nombre de lignes de la matrice
 * @param width le nombre de colonnes de la matrice
 */
void parallelInitLetterMat(char** mat, int height, int width);

/**
 * Affiche la matrice de lettres sur la sortie principale
 * @param mat la matrice de lettres
 * @param height le nombre de lignes de la matrice
 * @param width le nombre de colonnes de la matrice
 */
void displayMat(char** mat, int height, int width);

/**
 * Affiche les matrices de lettres sur la sortie principale
 * @param mats le tableau de matrices de lettres [n][height][width]
 * @param n le nombre de matrices
 * @param height le nombre de ligne des matrices
 * @param width le nombre de colonnes des matrices
 */
void displayMats(char*** mats, int n, int height, int width);

/**
 * Compte le nombre de chaque lettre dans une matrice
 * @param mat la matrice de lettres
 * @param height le nombre de ligne de la matrice
 * @param width le nombre de colonnes de la matrice
 * @param result le tableau de taille 26, chaque case contient en sortie le nombre d'occurences de chaque lettre
 * correspondante dans l'alphabet (0 -> a, 1 -> b ...), il doit être préalablement correctement instancie
 */
void letterCount(char** mat, int height, int width, int* result);

/**
 * Compte le nombre de chaque lettre dans une matrice en utilisant la parallelisation OpenMP
 * @param mat la matrice de lettres
 * @param height le nombre de lignes de la matrice
 * @param width le nombre de colonnes de la matrice
 * @param result le tableau de taille 26, chaque case contient en sortie le nombre d'occurences de chaque lettre
 * correspondante dans l'alphabet (0 -> a, 1 -> b ...), il doit être préalablement correctement instancie
 */
void parallelLetterCount(char** mat, int height, int width, int* result);

/**
 * Decoupe une matrice en tableau de sous-matrices en utilisant la parallelisation OpenMP
 * @param mat la matrice a decouper
 * @param height le nombre de lignes de la matrice a decouper
 * @param width le nombre de colonnes de la matrice a decouper
 * @param resultHeight la hauteur des matrices resultantes, doit etre un diviseur de height
 * @param resultWidth la largueur des matrices resultantes, doit etre un diviseur de width
 * @param result le tableau des matrices resultantes, doit etre instancie correctement selon ces dimensions :
 * [height/resultHeight * width/resultWidth][resultHeight][resultWidth]
 */
void parallelMap(char** mat, int height, int width, int resultHeight, int resultWidth, char*** result);

/**
 * Compte le nombre de chaque lettre dans chaque matrice en utilisant la parallelisation OpenMP
 * @param mats les matrices de lettres
 * @param n le nombre de matrices de lettres
 * @param height le nombre de lignes de chaque matrice
 * @param width le nombre de colonnes de chaque matrice
 * @param results les tableaux de taille 26, chaque case contient en sortie le nombre d'occurences de chaque lettre
 * correspondante dans l'alphabet (0 -> a, 1 -> b ...), il doit être préalablement correctement instancie de taille
 * [n][26]
 */
void underParallelLetterCount(char*** mats, int n, int height, int width, int** results);

/**
 * Somme les résultats de comptages en un seul tableau de résultatq
 * @param letterCounts le tableau de sous-resultats de taille 26, chaque case contient le nombre d'occurences de chaque
 * lettre correspondante dans l'alphabet (0 -> a, 1 -> b ...)
 * @param n le nombre de sous-resultats
 * @param result le tableau de taille 26, chaque case contient en sortie le nombre d'occurences final de chaque lettre
 * correspondante dans l'alphabet (0 -> a, 1 -> b ...), il doit être préalablement correctement instancie
 */
void parallelReduce(int** letterCounts, int n, int* result);

/**
 * Affiche un comptage d'occurence de lettre de l'alphabet
 * @param letterCounts le tableau de taille 26, chaque case contient le nombre d'occurences de chaque lettre
 * correspondante dans l'alphabet (0 -> a, 1 -> b ...)
 */
void displayLetterCount(int* letterCounts);

/**
 * Affiche les comptages d'occurences de lettre de l'alphabet
 * @param letterCounts le tableau de tableaux de taille 26, chaque case contient le nombre d'occurences de chaque lettre
 * correspondante dans l'alphabet (0 -> a, 1 -> b ...)
 * @param n le nombre de tableaux à afficher
 */
void displayLetterCounts(int** letterCounts, int n);

int main(int argc, char** argv)
{
    int coresNb, height, width, underHeight, underWidth;

    if (argc < 6)
    {
        std::cout << argc << std::endl;
        std::cout << "usage : app_name number_of_cores height width under_height under_width" << std::endl;
        return 0;
    }

    coresNb = std::stoi(argv[1]);
    height = std::stoi(argv[2]);
    width = std::stoi(argv[3]);
    underHeight = std::stoi(argv[4]);
    underWidth = std::stoi(argv[5]);

    omp_set_num_threads(coresNb);

    // instanciation de la matrice
    auto mat = new char*[height];

    for (int i = 0; i < height; i++)
    {
        mat[i] = new char[width];
    }

    // remplissage de la matrice
    parallelInitLetterMat(mat, height, width);

    // affichage de la matrice
    // displayMat(mat, height, width);

    // instanciation des sous-matrices et des sous-résultats
    int mapSize = (height / underHeight) * (width / underWidth);
    auto map = new char**[mapSize];
    auto underResults = new int*[mapSize];

    for (int n = 0; n < mapSize; n++)
    {
        map[n] = new char*[underHeight];
        underResults[n] = new int[LETTER_NB];

        for (int i = 0; i < underHeight; i++)
        {
            map[n][i] = new char[underWidth];
        }
    }

    // comptage des lettres
    auto letterCounts = new int[LETTER_NB];
    auto start = std::chrono::high_resolution_clock::now();
    // decoupage du probleme en sous problemes
    parallelMap(mat, height, width, underHeight, underWidth, map);
    // comptage dans chaque sous matrice
    underParallelLetterCount(map, mapSize, underHeight, underWidth, underResults);
    // reduction des sous-resultats
    parallelReduce(underResults, mapSize, letterCounts);
    auto end = std::chrono::high_resolution_clock::now();
    auto timeDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    // displayLetterCount(letterCounts);
    std::cout << "temps : " << timeDuration.count() << std::endl;

    // desinstanciation
    delete[] letterCounts;

    for (int n = 0; n < mapSize; n++)
    {
        for (int i = 0; i < underHeight; i++)
        {
            delete[] map[n][i];
        }

        delete[] underResults[n];
        delete[] map[n];
    }

    delete[] underResults;
    delete[] map;

    for (int i = 0; i < height; i++)
    {
        delete[] mat[i];
    }

    delete[] mat;

    return 0;
}

void initLetterMat(char** mat, int height, int width)
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<char> distribution('a', 'z');
    auto draw = std::bind(distribution, generator);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            mat[i][j] = draw();
        }
    }
}

void parallelInitLetterMat(char** mat, int height, int width)
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<char> distribution('a', 'z');
    auto draw = std::bind(distribution, generator);

    #pragma omp parallel for collapse(2)
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            mat[i][j] = draw();
        }
    }
}

void displayMat(char** mat, int height, int width)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            std::cout << mat[i][j] << " ";
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;
}

void displayMats(char*** mats, int n, int height, int width)
{
    for (int i = 0; i < n; i++)
    {
        displayMat(mats[i], height, width);
    }
}

void letterCount(char** mat, int height, int width, int* result)
{
    for (int i = 0; i < LETTER_NB; i++)
    {
        result[i] = 0;
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            result[(int)(mat[i][j] - 'a')]++;
        }
    }
}

void parallelLetterCount(char** mat, int height, int width, int* result)
{
    #pragma omp parallel
    {
        #pragma omp for
        for (int i = 0; i < LETTER_NB; i++)
        {
            result[i] = 0;
        }

        // reduction sur l'ensemble du tableau de resultats, fonctionne grace a la norme OpenMP 4.5
        #pragma omp for collapse(2) reduction(+:result[0:LETTER_NB])
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                result[(int)(mat[i][j] - 'a')]++;
            }
        }
    }
}

void parallelMap(char** mat, int height, int width, int resultHeight, int resultWidth, char*** result)
{
    // cas interessant ou l'on decoupe le probleme le plus possible
    if ((resultHeight == 1) && (resultWidth == 1))
    {
        #pragma parallel for collapse(2)
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                result[(i * width) + j][0][0] = mat[i][j];
            }
        }
    }
    else
    {
        #pragma parallel for collapse(2)
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                int h = ((i / resultHeight) * (width / resultWidth)) + (j / resultWidth);
                result[h][i % resultHeight][j % resultWidth] = mat[i][j];
            }
        }
    }
}

void underParallelLetterCount(char*** mats, int n, int height, int width, int** results)
{
    // si le decoupage est maximal, plus besoin de paralleliser le comptage devenu unitaire pour chaque sous-matrice
    if (n == height * width)
    {
        #pragma omp parallel
        {
            #pragma omp for collapse(2)
            for (int k = 0; k < n; ++k)
            {
                for (int i = 0; i < LETTER_NB; i++)
                {
                    results[k][i] = 0;
                }
            }

            #pragma omp for
            for (int l = 0; l < n; ++l)
            {
                results[l][(int) (mats[l][0][0] - 'a')]++;
            }
        }
    }
    else
    {
        #pragma omp parallel
        {
            #pragma omp for collapse(2)
            for (int k = 0; k < n; ++k)
            {
                for (int i = 0; i < LETTER_NB; i++)
                {
                    results[k][i] = 0;
                }
            }

            // reduction sur l'ensemble du tableau de resultats, fonctionne grace a la norme OpenMP 4.5
            #pragma omp for
            for (int l = 0; l < n; ++l)
            {
                int* result = results[l];

                // ce pragma est inutile si on découpe prealablement la matrice en matrices de 1 sur 1 (decoupage maximum)
                // reduction sur l'ensemble du tableau de resultats de chaque sous-matrice, fonctionne grace a la norme
                // OpenMP 4.5
                #pragma omp parallel for collapse(2) reduction(+:result[0:LETTER_NB])
                for (int i = 0; i < height; i++)
                {
                    for (int j = 0; j < width; j++)
                    {
                        result[(int)(mats[l][i][j] - 'a')]++;
                    }
                }
            }
        }
    }
}

void parallelReduce(int** letterCounts, int n, int* result)
{
    #pragma omp parallel
    {
        #pragma omp for
        for (int i = 0; i < LETTER_NB; ++i)
        {
            result[i] = 0;
        }

        #pragma omp for reduction(+:result[0:LETTER_NB])
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < LETTER_NB; ++j)
            {
                result[j] += letterCounts[i][j];
            }
        }
    }
}

void displayLetterCount(int* letterCounts)
{
    for (int i = 0; i < LETTER_NB; i++)
    {
        std::cout << (char)('a' + i) << " : " << letterCounts[i] << std::endl;
    }

    std::cout << std::endl;
}

void displayLetterCounts(int** letterCounts, int n)
{
    for (int i = 0; i < n; ++i)
    {
        displayLetterCount(letterCounts[i]);
    }
}