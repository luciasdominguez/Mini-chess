#pragma once
#include "GUI_pieza.h"

class GUI_Casilla
{
	enum class color { blanca, negra };
	int pos_fila, pos_columna;
	GUI_pieza pieza;
	bool ocupada;

public:
	void dibuja_casilla();
};