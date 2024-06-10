#include "GUI_partida.h"

GUI_partida::GUI_partida()
{

}

string GUI_partida::get_nombre()
{
	return nombre;
}

vector<GUI_movimiento> GUI_partida::get_movimientos()
{
	return partida;
}

void GUI_partida::vaciar_partida()
{
	partida.erase(partida.begin(), partida.end());

}

void GUI_partida::add_movimiento_a_partida(GUI_movimiento mv)
{
	partida.push_back(mv);
}

void GUI_partida::set_nombre(string n)
{
	nombre = n;
}

void GUI_partida::set_partida(vector<GUI_movimiento> lista_movis)
{
	partida = lista_movis;
}


