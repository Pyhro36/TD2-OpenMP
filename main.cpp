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

    // desinstanciation de la matrice
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