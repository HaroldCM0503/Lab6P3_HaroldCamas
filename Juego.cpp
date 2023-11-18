#include "Juego.h"
#include <string>
#include <iostream>
#include <random>
using namespace std;

static char casilla_ocupada1 = '-';
static char casilla_ocupada2 = '-';
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
	Cazador* Ptc1 = &cazador1;
	Cazador* Ptc2 = &cazador2;
	while (continuarJuego)
	{

		if (Ptc1->getMovimientos() != 0 && Ptc1->getVida() != 0)
		{
			CazadorTurno(Ptc1);
			if (casilla_ocupada1 == 'X')
			{
				cout << "El jugador 1 ha alcanzado el tesoro!!!!!";
				continuarJuego = false;
				break;
			}
		}

		if (Ptc2->getMovimientos() != 0 && Ptc2->getVida() != 0)
		{
			if (Ptc2->getVida() == 0)
			{

			}
			else
			{
				CazadorTurno(Ptc2);
				if (casilla_ocupada2 == 'X')
				{
					cout << "El jugador 2 ha alcanzado el tesoro!!!!!";
					continuarJuego = false;
					break;
				}
			}
		}

		if (Ptc1->getMovimientos() != 0 && Ptc2->getMovimientos() != 0)
		{
			cout << "A ambos jugadores se les acabaron los movimientos!!!" << endl;
			cout << "Es un empate";
			break;
		}
	}
	cout << "XD?";
	delete Ptc1;
	delete Ptc2;
}

void Juego::activarTrampa(Cazador *c)
{
	srand(time(NULL));
	int daño = 1 + rand() % 50;
	c->setVida(c->getVida() - daño);
	cout << "La trampa te ha causado " << daño << " de daño!!!";
	cout << endl << "Te queda " << c->getVida() << " de vida" << endl;
}

void Juego::CazadorTurno(Cazador *cazador)
{
	int movimiento;
	cout << endl;
	cout << "Turno del cazador " << (*cazador).getTurno() << "(" << (*cazador).getNombre() << ")";
	cout << endl << "Movimientos: " << (*cazador).getMovimientos();
	cout << endl << "Vida restante: " << (*cazador).getVida();

	//1:Arriba  2:Derecha  3:Abajo  4:Izquierda
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

void Juego::mover(int move, Cazador *c)
{
	int pos_x = c->getX();
	int pos_y = c->getY();
	if (c->getTurno() == 1)
	{
		isla.getMatriz()[pos_x][pos_y] = casilla_ocupada1;
	}
	else
	{
		isla.getMatriz()[pos_x][pos_y] = casilla_ocupada2;
	}
	switch (move)
	{
		case 1:
		{
			pos_x--;
			break;
		}
		case 2:
		{
			pos_y++;
			break;
		}
		case 3:
		{
			pos_x++;
			break;
		}
		case 4:
		{
			pos_y--;
			break;
		}
	}
	if (c->getTurno() == 1)
	{
		cazador1.setX(pos_x);
		cazador1.setY(pos_y);
		casilla_ocupada1 = isla.getMatriz()[pos_x][pos_y];
	}
	else
	{
		cazador2.setX(pos_x);
		cazador2.setY(pos_y);
		casilla_ocupada2 = isla.getMatriz()[pos_x][pos_y];
	}
	isla.getMatriz()[pos_x][pos_y] = c->getNombre().at(0);
	interactuar(c);
	c->setMovimientos(c->getMovimientos() - 1);
}

void Juego::interactuar(Cazador *c)
{
	if (c->getTurno() == 1)
	{
		if (casilla_ocupada1 == '#')
		{
			activarTrampa(c);
		}
	}
	else
	{
		if (casilla_ocupada2 == '#')
		{
			activarTrampa(c);
		}
	}
}

bool Juego::movimientoValido(int move, Cazador *c)
{
	switch (move)
	{
		case 1:
		{
			if (c->getX() - 1 < 0)
				return false;	
			else
				return true;
			break;
		}
		case 2:
		{
			if (c->getY() + 1 >= isla.getDimension())
				return false;
			else
				return true;
			break;
		}
		case 3:
		{
			if (c->getX() + 1 >= isla.getDimension())
				return false;
			else
				return true;
			break;
		}
		case 4:
		{
			if (c->getY() - 1 < 0)
				return false;
			else
				return true;
			break;
		}
		default:
			return false;
	}
}