#pragma once
//#include "casillas.h"
#include "fichas.h"

class gestor_movimientos
{
	
public:
	static colision comprobar_ocupacion(ficha* p1, casilla cas);
	static void cambiar_ocupación(ficha* p1, casilla* cas);
	static bool comprobar_colision(const ficha& p1, const casilla& cas, const tablero& T);

};