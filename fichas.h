#pragma once
//#include "casillas.h"
#include "clases.h"
//#include "tablero.h"

class ficha
{
private:
	friend class casilla;
	casilla* posicion;
	color c;
public:
	ficha(casilla* _pos, color _color);
	color comprobar_color() { return c; }

	friend class gestor_movimientos;
};