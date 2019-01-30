#include <iostream>
#include <random>
#include <functional>
#include <chrono>

/**
 * Initialise une matrice avec des lettre aleatoires
 * @param mat la matrice correctement instanciee
 * @param height le nombre de lignes de la matrice
 * @param width le nombre de colonnes de la matrice
 */
void initLetterMat(char** mat, int height, int width);

/**
 * Affiche la matrice de lettres sur la sortie principale
 * @param mat la matrice de lettres
 * @param height le nombre de lignes de la matrice
 * @param width le nombre de colonnes de la matrice
 */
void displayMat(char** mat, int height, int width);

/**
 * Compte le nombre de chaque lettre dans une matrice
 * @param mat la matrice de lettres
 * @param height le nombre de ligne de la matrice
 * @param width le nombre de colonnes de la matrice
 * @param result le tableau de taille 26, chaque case contient en sortie le nombre d'occurence de chaque lettre
 * correspondante dans l'alphabet (0 -> a, 1 -> b ...)
 */
void letterCount(char** mat, int height, int width, int* result);

int main(int argc, char** argv)
{
    int height = 5;
    int width = 8;

    char** mat = new char*[height];

    for (int i = 0; i < height; i++)
    {
        mat[i] = new char[width];
    }

    initLetterMat(mat, height, width);
    displayMat(mat, height, width);

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

void letterCount(char** mat, int height, int width, int* result)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if ()
        }
    }
}