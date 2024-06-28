#pragma once
#include <vector>
#include <string>
#include "ETSIDI.h"

using std::vector;
using std::string;
using ETSIDI::Vector2D;

class T_listado_partidas
{
	vector<string> nombres_partidas;
public:
	T_listado_partidas();
	void imprime_nombres();
	void set_nombres_partidas(vector<string> nombres);
	vector<string> get_nombres_partidas();

};
