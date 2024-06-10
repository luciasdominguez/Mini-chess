#pragma once
//#include <vector>
#include "ETSIDI.h"

using ETSIDI::Vector2D;

class GUI_Tablero
{
	//vector<GUI_Fila*> lista_filas; // Filas del tablero
	int n_filas;

	Vector2D tamaño_pantalla{ 34.0, 25.2 };
	Vector2D tamaño_tablero { 20.0, 20.0 };
	Vector2D posicion_tablero { -3.0, 0.2 };	// Posición esquina izq abajo

public:
	GUI_Tablero()=default;
	void dibuja_tablero();
	//void get_tamaño_tablero(Vector2D& t) { t = tamaño_tablero; };
	//friend class GUI_pieza;

	friend class Juego;
};

