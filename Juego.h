#pragma once
#include "Isla.h"
#include "Cazador.h"
class Juego
{
	Cazador cazador1;
	Cazador cazador2;
	Isla isla;
public:
	Juego();
	~Juego();
	void iniciarJuego();
	void activarTrampa();
	void CazadorTurno(Cazador cazador);
	void mover(int move, Cazador c);
	void interactuar();

	bool movimientoValido(int move, Cazador c);
};

