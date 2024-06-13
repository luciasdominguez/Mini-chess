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

    int leer_filas() const { return n_filas; }
    int leer_columnas() const { return n_columnas; }
    casilla leer_casilla(int i, int j) const { return matriz[i][j]; }

    // Destructor de tablero
    ~tablero();
};