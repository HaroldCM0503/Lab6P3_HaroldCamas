#include "Isla.h"
#include <random>;
#include <iostream>

Isla::Isla(int d, char* m)
{
    this->dimension = d;
    this->matriz = m;
}

void Isla::generarIsla()
{
    int cant_trampas = (dimension * dimension) / 2;
    int x = 0;
    int y = 0;
    srand(time(0));
    for (int i = 0; i <= cant_trampas; i++)
    {
        x = rand() % (dimension);
        y = rand() % (dimension);
        while ((x == 0 && y == 0) || (x == 0 && y == dimension - 1))
        {
            x = rand() % (dimension);
            y = rand() % (dimension);
        }
        matriz[x*dimension + y] = '#';
        x = 0;
        y = 0;
    }

    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            if (!(i == 0 && j == 0) && !(i == 0 && j == dimension - 1) && matriz[i * dimension + j] != '#')
                matriz[i * dimension + j] = '-';
        }
    }

}

void Isla::mostrarIsla()
{
    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            std::cout << matriz[i*dimension + j];
        }
        std::cout << std::endl;
    }
}
