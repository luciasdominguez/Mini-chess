#pragma once
#include <vector>
#include "GUI_partida.h"

//enum ENUM_ANALISIS {  = 0, NEGRAS, GRAVEDAD_N, GRAVEDAD_B };

class Cl_logica
{
	GUI_partida partida_in;
	

public:
	bool analiza_jugada(GUI_partida partida_in, GUI_jugada &jugada_propia, GUI_jugada &jugada_gravedad, int caso);  // Si la ultima jugada en valida devuelve true;

	
};

