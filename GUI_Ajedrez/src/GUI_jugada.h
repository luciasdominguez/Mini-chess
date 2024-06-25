#pragma once
#include <vector>
#include "GUI_Pieza2.h"
#include <map> 


using std::vector;

enum ENUM_JUGADOR { BLANCAS=0, NEGRAS, GRAVEDAD_N, GRAVEDAD_B};


class GUI_jugada   // es una lista de piezas que se han movido y quien las movió
{
	int numero_en_la_partida = 0;


public:
	bool jaque_mate = false;
	ENUM_JUGADOR jugador = GRAVEDAD_N;  // porque por defecto despues les toca a las blancas
	ENUM_JUGADOR jugador_siguiente = BLANCAS;  // porque por defecto despues les toca a las blancas
	vector<PIEZA_STRU> lista_PiezasMovidas; // los valores se actualizarán en la parte de logica
	//----------------
	GUI_jugada();
	GUI_jugada(const vector<PIEZA_STRU>& lista_datos_de_piezas)
		: lista_PiezasMovidas(lista_datos_de_piezas)
	{
	}

	void set_jugador(ENUM_JUGADOR);
	void set_numero_en_la_partida(int num);
	int get_numero_en_la_partida();
	vector<PIEZA_STRU> get_lista_piezas_movidas();
	void vaciar_jugada();
	void nueva_jugada();

	void add_pieza_a_jugada(PIEZA_STRU pz);
	void inicio_partida(); // genera un movimiento que es la lista de todos las piezas a posicion inicial
	void ejemplo_jugada_01(); // añade una la pieza peon torre reina a lista de piezas movidas
	void ejemplo_jugada_02();
	void ejemplo_jugada_03();
	void ejemplo_jugada_04();
};

