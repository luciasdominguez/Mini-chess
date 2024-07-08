#include "T_listado_jugadas.h"

using namespace std;

T_listado_jugadas::T_listado_jugadas()
{
}

void T_listado_jugadas::imprime_jugadas()
{
	ETSIDI::setFont("fuentes/SwanseaBold.ttf", 11);  

	float Pos_jugada_1 = 6.8;
	int offset_linea = 0;

	ETSIDI::setTextColor(1, 1, 0);
	string s = "Jugadas partida: " + nombre_partida;
	ETSIDI::printxy(s.c_str(), -16.5, Pos_jugada_1);
	ETSIDI::setTextColor(1, 1, 1);

	int corrige = 0;
	int tam_partida = lineas_de_la_partida.size();
	int tam_print;
	if (tam_partida > 10) tam_print = 10; else tam_print = tam_partida;
	for (auto it_lineas = lineas_de_la_partida.end() - tam_print; it_lineas != (lineas_de_la_partida.end()); ++it_lineas)
	{
		auto str = (*it_lineas);
		ETSIDI::printxy((str).c_str(), -16.5, Pos_jugada_1 - (float)(offset_linea + 1 + corrige));
		offset_linea++;
		if (offset_linea > 5) corrige = 1;
	}
}

void T_listado_jugadas::set_lineas_partida(vector<string> nombres)
{
	lineas_de_la_partida.clear();
	for (auto it_nombres = nombres.begin(); it_nombres != (nombres.end()); ++it_nombres)
	{
		lineas_de_la_partida.push_back((*it_nombres));
	}
}

void T_listado_jugadas::set_nombre_partida(string nombre)
{
	nombre_partida = nombre;
}
