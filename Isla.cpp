#include "Isla.h"
#include <random>;
#include <iostream>

Isla::Isla(int d, char** m)
{
    this->dimension = d;
    this->matriz = m;
}

Isla::Isla()
{
}

Isla::~Isla()
{
}

int Isla::getDimension()
{
    return dimension;
}

char** Isla::getMatriz()
{
    return matriz;
}

void Isla::generarIsla()
{
    
    int x = 0;
    int y = 0;
    srand(time(0));
    int cant_trampas = 1 + rand()% (dimension * dimension) / 2;
    for (int i = 0; i <= cant_trampas; i++)
    {
        x = rand() % (dimension);
        y = rand() % (dimension);
        while ((x == 0 && y == 0) || (x == 0 && y == dimension - 1))
        {
            x = rand() % (dimension);
            y = rand() % (dimension);
        }
        matriz[x][y] = '#';
        x = 0;
        y = 0;
    }

    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            if (!(i == 0 && j == 0) && !(i == 0 && j == dimension - 1) && matriz[i][j] != '#')
                matriz[i][j] = '-';
        }
    }

    int tesoro_x;
    int tesoro_y;
    do
    {
        tesoro_x = rand() % (dimension);
        tesoro_y = rand() % (dimension);
    } while ((tesoro_x == 0 && tesoro_y == 0) || (tesoro_x == 0 && tesoro_y == dimension - 1));

    matriz[tesoro_x][tesoro_y] = 'X';
}

void Isla::mostrarIsla()
{
    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            std::cout << matriz[i][j];
        }
        std::cout << std::endl;
    }
}
