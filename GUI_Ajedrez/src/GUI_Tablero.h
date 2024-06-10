#pragma once
//#include <vector>
#include "ETSIDI.h"

using ETSIDI::Vector2D;

class GUI_Tablero
{
	//vector<GUI_Fila*> lista_filas; // Filas del tablero
	int n_filas;

	Vector2D tama�o_pantalla{ 34.0, 25.2 };
	Vector2D tama�o_tablero { 20.0, 20.0 };
	Vector2D posicion_tablero { -3.0, 0.2 };	// Posici�n esquina izq abajo

public:
	GUI_Tablero()=default;
	void dibuja_tablero();
	//void get_tama�o_tablero(Vector2D& t) { t = tama�o_tablero; };
	//friend class GUI_pieza;

	friend class Juego;
};

