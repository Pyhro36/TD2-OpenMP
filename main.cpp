#include <iostream>
#include <random>
#include <functional>
#include <chrono>

#define LETTER_NB 26

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
 * @param result le tableau de taille 26, chaque case contient en sortie le nombre d'occurences de chaque lettre
 * correspondante dans l'alphabet (0 -> a, 1 -> b ...), il doit être préalablement correctement initialise
 */
void letterCount(char** mat, int height, int width, int* result);

/**
 * Affiche un comptage d'occurence de lettre de l'alphabet
 * @param letterCounts le tableau de taille 26, chaque case contient le nombre d'occurences de chaque lettre
 * correspondante dans l'alphabet (0 -> a, 1 -> b ...)
 */
void displayLetterCount(int* letterCounts);

int main(int argc, char** argv)
{
    int height = 5;
    int width = 8;

    // instanciation de la matrice
    auto mat = new char*[height];

    for (int i = 0; i < height; i++)
    {
        mat[i] = new char[width];
    }

    // remplissage de la matrice
    initLetterMat(mat, height, width);

    // affichage de la matrice
    displayMat(mat, height, width);

    // comptage des lettres
    auto letterCounts = new int[LETTER_NB] {};

    letterCount(mat, height, width, letterCounts);
    displayLetterCount(letterCounts);

    // desinstanciation
    delete[] letterCounts;

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
            result[(int)(mat[i][j] - 'a')]++;
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