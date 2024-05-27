#pragma once
#include "GUI_Fila.h"
#include "ETSIDI.h"
#include "vector2D.h"
#include <vector>

using std::vector;

class GUI_Tablero
{
	vector<GUI_Fila*> lista_filas; // Filas del tablero
	int n_filas;
	const Vector2D tamaño_pantalla{ 34.0, 25.2 };
	const Vector2D tamaño_tablero{ 20.0,20.0 };
	const Vector2D posicion_tablero{ -3.0, 0.2 };	// Posición esquina izq abajo

public:
	void dibuja_tablero();
};

