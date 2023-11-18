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
	void activarTrampa(Cazador *c);
	void CazadorTurno(Cazador *cazador);
	void mover(int move, Cazador *c);
	void interactuar(Cazador *c);

	bool movimientoValido(int move, Cazador *c);
};

