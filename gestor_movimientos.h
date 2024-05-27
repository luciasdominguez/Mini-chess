#pragma once
#include "clases.h"
#include "piezas.h"

enum class colision{vacio, enemigo, amigo};

class Gestor_Movimientos{
public:
	static bool comprobar_colision(const ficha& pieza, const casilla& casilla);
	static colision comprobar_ocupacion(const ficha& pieza, const casilla& casilla);
	static void cambiar_ocupacion(casilla& casilla, ficha& pieza);
	friend class casilla;
};

