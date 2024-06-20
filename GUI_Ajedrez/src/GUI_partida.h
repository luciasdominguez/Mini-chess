#pragma once
#include <vector>
#include "GUI_Pieza2.h"
#include "GUI_jugada.h"
class GUI_partida  // es una lista de movimientos y un nombre
{
	string nombre;
	vector<GUI_jugada> lista_jugadas; // una partida es una lista de jugadas.
public:
	GUI_partida();
	string get_nombre();
	vector<GUI_jugada> get_jugadas();

	void vaciar_partida();
	void borrar_jugadas_desde_N(int desde);
	void add_jugada_a_partida(GUI_jugada jug);
	void set_nombre_de_partida(string);
	void set_jugadas_de_partida(vector<GUI_jugada> lista_jugadas);
};

