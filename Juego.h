#pragma once
#include "Isla.h"
#include "Cazador.h"
class Juego
{
	Cazador cazador1;
	Cazador cazador2;
	Isla isla;
public:
	void iniciarJuego();
	void activarTrampa();
	void CazadorTurno();
	void mover();
	void interactuar();
};

