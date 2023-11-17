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

	char** m = new char*[dimension];
	for (int i = 0; i < dimension; ++i)
		m[i] = new char[dimension];

	srand(time(NULL));
	int empieza = 1 + rand()%2;
	if (empieza == 1)
	{
		int movimientos1 = 5 + rand() % (5 - 1);
		cazador1 = Cazador(nombre1, 0, 0, 100, movimientos1, 1);

		int movimientos2 = 5 + rand() % (5 - 1);
		cazador2 = Cazador(nombre2, 0, dimension - 1, 100, movimientos2, 2);

		m[0][0] = nombre1.at(0);
		m[0][dimension - 1] = nombre2.at(0);
	}
	else
	{
		int movimientos1 = 5 + rand() % (5 - 1);
		cazador1 = Cazador(nombre2, 0, 0, 100, movimientos1, 1);

		int movimientos2 = 5 + rand() % (5 - 1);
		cazador2 = Cazador(nombre1, 0, dimension - 1, 100, movimientos1, 2);

		m[0][0] = nombre2.at(0);
		m[0][dimension - 1] = nombre1.at(0);
	}

	Isla i(dimension, m);
	isla = i;
	isla.generarIsla();
	isla.mostrarIsla();

	bool continuarJuego = true;
	while (continuarJuego)
	{
		CazadorTurno(cazador1);
		CazadorTurno(cazador2);
	}
}

void Juego::CazadorTurno(Cazador cazador)
{
	int movimiento;
	cout << endl;
	cout << "Turno del cazador " << cazador.getTurno() << "(" << cazador.getNombre() << ")";
	cout << endl << "Movimientos: " << cazador.getMovimientos();
	cout << endl << "Vida restante: " << cazador.getVida();

	bool isValid;
	do
	{
		cout << endl << "Elija su movimiento: ";
		cin >> movimiento;
		isValid = movimientoValido(movimiento, cazador);
	} while ((movimiento < 1 || movimiento > 4) || !isValid);

	mover(movimiento, cazador);
	cout << endl << endl << endl;
	isla.mostrarIsla();
}

void Juego::mover(int move, Cazador c)
{
	int pos_x = c.getX();
	int pos_y = c.getY();
	isla.getMatriz()[pos_x][pos_y] = '-';
	switch (move)
	{
		case 1:
		{
			pos_y--;
			break;
		}
		case 2:
		{
			pos_x++;
			break;
		}
		case 3:
		{
			pos_y++;
			break;
		}
		case 4:
		{
			pos_x--;
			break;
		}
	}

	c.setX(pos_x);
	c.setY(pos_y);
	isla.getMatriz()[pos_x][pos_y] = c.getNombre().at(0);
}

bool Juego::movimientoValido(int move, Cazador c)
{
	switch (move)
	{
		case 1:
		{
			if (c.getY() - 1 < 0)
				return false;	
			else
				return true;
			break;
		}
		case 2:
		{
			if (c.getX() + 1 >= isla.getDimension())
				return false;
			else
				return true;
			break;
		}
		case 3:
		{
			if (c.getY() + 1 >= isla.getDimension())
				return false;
			else
				return true;
			break;
		}
		case 4:
		{
			if (c.getX() - 1 < 0)
				return false;
			else
				return true;
			break;
		}
		default:
			return false;
	}
}