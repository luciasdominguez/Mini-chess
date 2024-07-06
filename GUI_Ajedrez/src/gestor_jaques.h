#pragma once
#include "tablero.h"
#include "casillas.h"
#include "fichas.h"


class gestor_jaques
{	
public:
	static bool comprobar_mate(const tablero& T);
	static bool comprobar_mov_posibles(const tablero& T, const ENUM_COLOR& color);

};

