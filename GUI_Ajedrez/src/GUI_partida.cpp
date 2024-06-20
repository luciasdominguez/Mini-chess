#include "GUI_partida.h"

GUI_partida::GUI_partida()
{

}

string GUI_partida::get_nombre()
{
	return nombre;
}

vector<GUI_jugada> GUI_partida::get_jugadas()
{
	return lista_jugadas;
}

void GUI_partida::vaciar_partida()
{
	lista_jugadas.erase(lista_jugadas.begin(), lista_jugadas.end());

}

void GUI_partida::borrar_jugadas_desde_N(int desde)
{
	if (desde<=lista_jugadas.size())
	lista_jugadas.erase(lista_jugadas.begin()+ desde, lista_jugadas.end());
}

void GUI_partida::add_jugada_a_partida(GUI_jugada jug)
{
	lista_jugadas.push_back(jug);
}

void GUI_partida::set_nombre_de_partida(string n)
{
	nombre = n;
}

void GUI_partida::set_jugadas_de_partida(vector<GUI_jugada> lista_movis)
{
	lista_jugadas = lista_movis;
}


