#pragma once
#include <vector>
#include "GUI_Pieza2.h"
#include "GUI_movimiento.h"
class GUI_partida  // es una lista de movimientos y un nombre
{
	string nombre;
	vector<GUI_movimiento> partida; // una partida es una lista de movimientos.
public:
	GUI_partida();
	string get_nombre();
	vector<GUI_movimiento> get_movimientos();

	void vaciar_partida();
	void add_movimiento_a_partida(GUI_movimiento mv);
	void set_nombre(string);
	void set_partida(vector<GUI_movimiento> lista_movis);
};

