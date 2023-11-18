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
	
	//Le pide los datos necesarios al usuario.
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

	//Crea la matriz y asigna que jugador le toca ser el cazador 1 y a cual el 2.
	srand(time(NULL));
	int empieza = 1 + rand()%2;
	//Si el radn es 1 les toca de forma respectiva.
	if (empieza == 1)
	{
		int movimientos1 = 5 + rand() % (dimension * dimension);
		cazador1 = Cazador(nombre1, 0, 0, 100, movimientos1, 1);

		int movimientos2 = 5 + rand() % (dimension * dimension);
		cazador2 = Cazador(nombre2, 0, dimension - 1, 100, movimientos2, 2);

		m[0][0] = nombre1.at(0);
		m[0][dimension - 1] = nombre2.at(0);
	}
	//Si sale 2 se intercambian.
	else
	{
		int movimientos1 = 5 + rand() % (dimension * dimension);
		cazador1 = Cazador(nombre2, 0, 0, 100, movimientos1, 1);

		int movimientos2 = 5 + rand() % (dimension * dimension);
		cazador2 = Cazador(nombre1, 0, dimension - 1, 100, movimientos1, 2);

		m[0][0] = nombre2.at(0);
		m[0][dimension - 1] = nombre1.at(0);
	}

	Isla i(dimension, m);
	isla = i;
	isla.generarIsla();
	isla.mostrarIsla();

	//Empieza el bucle del juego
	Cazador* Ptc1 = &cazador1;
	Cazador* Ptc2 = &cazador2;
	while ((Ptc1->getMovimientos() > 0 || Ptc2->getMovimientos() > 0) && (Ptc1->getVida() > 0 || Ptc2->getVida() > 0))
	{
		//Evalua las situaciones del jugador 2
		if (Ptc1->getMovimientos() != 0 && Ptc1->getVida() != 0)
		{
			if (Ptc1->getVida() > 0)
			{
				CazadorTurno(Ptc1);
				if (casilla_ocupada1 == 'X')
				{
					cout << "El jugador 1 ha alcanzado el tesoro!!!!!";
					break;
				}
				if (Ptc1->getVida() <= 0)
				{
					cout << "El jugador 1 ha muerto!";
				}
				if (Ptc1->getMovimientos() == 0)
				{
					cout << "El jugador 1 se quedo sin movimientos!";
				}
			}
			
		}

		//Evalua las situaciones del jugador 2
		if (Ptc2->getMovimientos() != 0 && Ptc2->getVida() != 0)
		{
			if(Ptc2->getVida() > 0)
			{
				CazadorTurno(Ptc2);
				if (casilla_ocupada2 == 'X')
				{
					cout << "El jugador 2 ha alcanzado el tesoro!!!!!";
					break;
				}
				if (Ptc2->getVida() <= 0)
				{
					cout << "El jugador 2 ha muerto!";
				}
				if (Ptc2->getMovimientos() == 0)
				{
					cout << "El jugador 2 se quedo sin movimientos!";
				}
			}
		}
	}//Fin while

	//Evalua si hay empate.
	if (Ptc1->getMovimientos() == 0 && Ptc2->getMovimientos() == 0)
	{
		cout << endl << "A ambos jugadores se les acabaron los movimientos!!!" << endl;
		cout << "Es un empate";
	}
	if (Ptc1->getVida() <= 0 && Ptc2->getVida() <= 0)
	{
		cout << endl << "A ambos jugadores murieron antes de alcanzar el tesoro!!!" << endl;
		cout << "Es un empate";
	}
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
	cout << endl << endl;
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
		//Pide el movimiento de nuevo si se sale de las opciones o es invalido.
	} while ((movimiento < 1 || movimiento > 4) || !isValid);

	mover(movimiento, cazador);
	cout << endl << endl << endl;
	isla.mostrarIsla();

}

void Juego::mover(int move, Cazador *c)
{
	//Guarda la posicion donde estaba.
	int pos_x = c->getX();
	int pos_y = c->getY();
	//Reemplaza donde estaba por el tipo de casilla original de donde estaba
	if (c->getTurno() == 1)
	{
		isla.getMatriz()[pos_x][pos_y] = casilla_ocupada1;
	}
	else
	{
		isla.getMatriz()[pos_x][pos_y] = casilla_ocupada2;
	}
	//Dependiendo del movimiento elegido traslada 1 casilla en la direccion elegida.
	switch (move)
	{
		//Arriba
		case 1:
		{
			pos_x--;
			break;
		}
		//Derecha
		case 2:
		{
			pos_y++;
			break;
		}
		//Abajo
		case 3:
		{
			pos_x++;
			break;
		}
		//Izquierda
		case 4:
		{
			pos_y--;
			break;
		}
	}
	//Guarda el caracter a donde se paro el jugador para despues cambiarla y no perder el simbolo.
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
	//Mueve al jugador y evalua si es una trampa para bajar vida. Luego le quita un movimiento.
	isla.getMatriz()[pos_x][pos_y] = c->getNombre().at(0);
	interactuar(c);
	c->setMovimientos(c->getMovimientos() - 1);
}

void Juego::interactuar(Cazador *c)
{
	//Evalua si donde esta es una trampa.
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
	//Evalua si el movimiento respectivo hace que se salga de la matriz. Retorna falso si se sale.
	switch (move)
	{
		//Arriba
		case 1:
		{
			if (c->getX() - 1 < 0 )
				return false;	
			else
				return true;
			break;
		}
		//Derecha
		case 2:
		{
			if (c->getY() + 1 >= isla.getDimension())
				return false;
			else
				return true;
			break;
		}
		//Abajo
		case 3:
		{
			if (c->getX() + 1 >= isla.getDimension())
				return false;
			else
				return true;
			break;
		}
		//Izquierda
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