#pragma once

#include "casillas.h"
#include "fichas.h"

class gestor_movimientos
{
public:
	static colision comprobar_ocupacion(ficha* p1, casilla cas);
	static void cambiar_ocupaci�n(ficha* p1, casilla* cas);
};

