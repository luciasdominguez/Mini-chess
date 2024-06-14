#pragma once
#include "ETSIDI.h"
#include <string>
#include "GUI_movimiento.h"
using namespace ETSIDI;

class GUI_Tablero
{
	//vector<GUI_Fila*> lista_filas; // Filas del tablero
	int n_filas;
	float pos_x{}, pos_y{}; /// posición según escala del sprite

	Vector2D tamaño_pantalla{ 34.0, 25.2 };
	Vector2D tamaño_tablero { 20.0, 20.0 };
	Vector2D posicion_tablero { -3.0, 0.2 };	// Posición esquina izq abajo


public:
	GUI_Tablero();
	void dibuja_tablero();


	friend class Juego;
};

