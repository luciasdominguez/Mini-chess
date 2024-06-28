#pragma once
#include "casillas.h"
#include "clases.h"
//#include "fichas.h"

class tablero
{
private:
 
    friend class ficha;
    casilla** matriz;  // Matriz de casillas
    int n_filas, n_columnas;

public:
    // Constructor de tablero
    tablero(int filas_, int columnas_);

    int leer_filas() const { return n_filas; }
    int leer_columnas() const { return n_columnas; }
    casilla leer_casilla(int i, int j) const { return matriz[i][j]; }

    ficha* encontrar_rey(const ENUM_COLOR& c) const;

    // Destructor de tablero
    ~tablero();
};