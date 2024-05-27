#pragma once
#include "GUI_Casilla.h"
#include <vector>

using std::vector;

class GUI_Fila
{
	vector<GUI_Casilla*> fila_casillas; // Casillas que hay en cada fila
	int n_columnas;
};

