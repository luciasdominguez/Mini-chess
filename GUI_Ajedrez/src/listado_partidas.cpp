#include "listado_partidas.h"
using namespace std::string_literals; // enables s-suffix for std::string literals

T_listado_partidas::T_listado_partidas() {

	Vector2D primera_linea{ -16.5 ,19 };
	float salto_linea = 1.0;
}

void T_listado_partidas::imprime_nombres()
{
	//ETSIDI::setFont("fuentes/Bitwise.ttf", 12);  // la primera
	//ETSIDI::setFont("fuentes/Paintingwithchocolate.ttf", 12);
	//ETSIDI::setFont("fuentes/AaahSpeed.ttf", 12);
	//ETSIDI::setFont("fuentes/AtoZ.ttf", 12);
	ETSIDI::setFont("fuentes/SwanseaBold.ttf", 12);  //esta va bien

	//----------------------
	ETSIDI::setTextColor(0, 1, 0);
	float Pos_partida_1 = 18;
	int offset_linea = 0;
	ETSIDI::printxy("LISTA DE PARTIDAS (N > nueva)", -16.5, Pos_partida_1 + 1.0);

	ETSIDI::setTextColor(1, 1, 1);

	for (auto it_lineas = nombres_partidas.begin(); it_lineas != (nombres_partidas.end()); ++it_lineas)
	{
		auto str = nombres_partidas.begin() + offset_linea;
		(*str) = std::to_string(offset_linea + 1) + ": " + (*str);
		ETSIDI::printxy((*str).c_str(), -16.5, Pos_partida_1 - (float)offset_linea);
		offset_linea++;
	}
}

void T_listado_partidas::set_nombres_partidas(vector<string> nombres)
{
	nombres_partidas.clear();
	for (auto it_nombres = nombres.begin(); it_nombres != (nombres.end()); ++it_nombres)
	{
		nombres_partidas.push_back((*it_nombres));
	}

}

vector<string> T_listado_partidas::get_nombres_partidas()
{
	return nombres_partidas;
}
