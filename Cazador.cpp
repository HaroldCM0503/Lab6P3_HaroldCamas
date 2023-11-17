#include "Cazador.h"

Cazador::Cazador()
{
}

Cazador::Cazador(std::string nombre, int x, int y, int vida, int movimientos, int turno)
{
	this->nombre = nombre;
	this->posicion_x = x;
	this->posicion_y = y;
	this->vida = vida;
	this->movimientos = movimientos;
	this->turno = turno;
}

Cazador::~Cazador()
{
}

std::string Cazador::getNombre()
{
	return nombre;
}

int Cazador::getX()
{
	return posicion_x;
}

int Cazador::getY()
{
	return posicion_y;
}

int Cazador::getVida()
{
	return vida;
}

int Cazador::getMovimientos()
{
	return movimientos;
}

int Cazador::getTurno()
{
	return turno;
}

void Cazador::setY(int y)
{
	this->posicion_y = y;
}

void Cazador::setVida(int vida)
{
	this->vida = vida;
}

void Cazador::setMovimientos(int movimientos)
{
	this->movimientos = movimientos;
}

void Cazador::setX(int x)
{
	this->posicion_x = x;
}
