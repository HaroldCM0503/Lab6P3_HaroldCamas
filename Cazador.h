#pragma once
#include <string>
class Cazador
{
private:
	std::string nombre;
	int posicion_x;
	int posicion_y;
	int vida;
	int movimientos;
	int turno;

public:
	Cazador();
	Cazador(std::string nombre, int x, int y, int vida, int movimientos, int turno);
	~Cazador();

	std::string getNombre();
	int getX();
	int getY();
	int getVida();
	int getMovimientos();
	int getTurno();

	void setX(int x);
	void setY(int y);
	void setVida(int vida);
	void setMovimientos(int movimientos);
};

