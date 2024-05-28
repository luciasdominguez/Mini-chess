#pragma once
#include "casillas.h"

class tablero
{
private:
    casilla** matriz;  // Matriz de casillas
    int n_filas, n_columnas;

public:
    // Constructor de tablero
    tablero(int filas_, int columnas_);

    // Destructor de tablero
    ~tablero();
};