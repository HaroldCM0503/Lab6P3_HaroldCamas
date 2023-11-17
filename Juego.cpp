#include "Juego.h"
#include <string>
#include <iostream>
#include <random>
using namespace std;

Juego::Juego()
{
}

Juego::~Juego()
{
}

void Juego::iniciarJuego()
{
	string nombre1;
	string nombre2;
	int dimension;
	
	cout << "Ingrese el nombre del jugador 1: ";
	getline(cin, nombre1);

	cout << endl << "Ingrese el nombre del jugador 2: ";
	getline(cin, nombre2);

	do
	{
		cout << endl << "Ingrese el tamaño de la isla: ";
		cin >> dimension;
	} while (dimension < 10);

	char* m = new char[dimension * dimension];
	srand(time(NULL));
	int empieza = 1 + rand()%2;
	cout << empieza << endl;
	if (empieza%2 == 0)
	{
		int movimientos1 = 5 + rand() % (5 - 1);
		cazador1 = Cazador(nombre1, 0, 0, 100, movimientos1, 1);

		int movimientos2 = 5 + rand() % (5 - 1);
		cazador2 = Cazador(nombre2, 0, dimension - 1, 100, movimientos2, 2);

		m[0] = nombre1.at(0);
		m[dimension - 1] = nombre2.at(0);
	}
	else
	{
		int movimientos1 = 5 + rand() % (5 - 1);
		cazador1 = Cazador(nombre2, 0, 0, 100, movimientos1, 1);

		int movimientos2 = 5 + rand() % (5 - 1);
		cazador2 = Cazador(nombre1, 0, dimension - 1, 100, movimientos1, 2);

		m[0] = nombre2.at(0);
		m[dimension - 1] = nombre1.at(0);
	}

	Isla i(dimension, m);
	isla = i;
	isla.generarIsla();
	isla.mostrarIsla();
}

void Juego::CazadorTurno(Cazador cazador)
{

}
