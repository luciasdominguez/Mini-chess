#pragma once
#include <vector>
#include "GUI_Pieza2.h"

using std::vector;

enum ENUM_JUGADOR { BLANCAS=0, NEGRAS, GRAVEDAD_N, GRAVEDAD_B};


class GUI_movimiento   // es una lista de piezas que se han movido y quien las movió
{
	int numero_en_la_partida = 1;
public:
	GUI_movimiento();
	ENUM_JUGADOR jugador = GRAVEDAD_N;
	vector<PIEZA_STRU> lista_PiezasMovidas; // los valores se actualizarán en la parte de logica

	GUI_movimiento(const vector<PIEZA_STRU>& lista_datos_de_piezas)
		: lista_PiezasMovidas(lista_datos_de_piezas)
	{
	}

	void set_jugador(ENUM_JUGADOR);
	int get_numero_en_la_partida();
	void vaciar_movimiento();
	void nuevo_movimiento();

	void add_pieza_a_movimiento(PIEZA_STRU pz);
	void inicio_partida(); // genera un movimiento que es la lista de todos las piezas a posicion inicial
	void ejemplo_movi_01(); // añade una la pieza peon torre reina a lista de piezas movidas
	void ejemplo_movi_02();
	void ejemplo_movi_03();
	void ejemplo_movi_04();

};

