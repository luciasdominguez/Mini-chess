#pragma once
#include <vector>
#include <string>
#include "ETSIDI.h"

using std::vector;
using std::string;
using ETSIDI::Vector2D;

class T_listado_jugadas
{
	string nm_jugador;
	int n_jugada;
	int n_pieza;
	string nm_pieza;
	string nm_color;
	string nm_fila;
	string nm_columna;
	string linea_print;
	vector<string> lineas_de_la_partida;
	string nombre_partida;

public:
	T_listado_jugadas();
	void imprime_jugadas();
	void set_lineas_partida(vector<string> nombres);
	void set_nombre_partida(string nombre);
};
