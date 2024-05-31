#pragma once
#include "GUI_Tablero.h"
#include "GUI_Fila.h"
#include "GUI_Casilla.h"
#include <vector>
#include "GUI_Pieza2.h"

using std::vector;
using ETSIDI::Vector2D;




class Juego
{
 
	//std::vector<Objeto> elementos;
	//elementos.emplace(elementos.end());
	//vector<GUI_pieza*> lista_piezas;
	//vector<GUI_pieza*> lista;
	//STRU_PIEZA d;
	
	//GUI_Pieza2 pieza1(d);
	//GUI_Pieza2 pieza1;
	//GUI_Pieza2 pieza2;
	GUI_Tablero miTablero;

	//lista_piezas[]


	//vector<GUI_pieza*> lista_piezas;

	

	//enum color { blanca = 0, negra } color{};
	//enum tipo { peon = 0, torre, caballo, alfil, reina, rey, vacio } tipo{};
	//enum fila { f1 = 1, f2, f3, f4, f5, f6, f7, f8 } fila{};
	//enum columa { A = 1, B, C, D, E, F, G, H } columna{};

public:

	Juego();
	void dibuja_juego();
	Vector2D calculo_posicion_pieza(Vector2D tam_tablero, Vector2D pos_tablero, enum fila fila, enum columna columna);
	void leer_listado_piezas();

	//GUI_Tablero miTablero;

};

