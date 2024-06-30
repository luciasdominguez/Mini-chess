#pragma once
#include "casillas.h"
#include "clases.h"
//#include "fichas.h"

class tablero
{
private:
    friend class Cl_logica;
    friend class ficha;
    friend class Rey;

    casilla** matriz;  // Matriz de casillas
    int n_filas = 8, n_columnas = 8;

public:
    tablero() = default;
    // Constructor de tablero
    tablero(int filas_, int columnas_);
    void cambiar_casilla(casilla cas, ficha* f) { matriz[cas.columna][cas.fila].ocupacion = f; };
    void cambiar_casilla(casilla* cas, ficha* f) { matriz[cas->columna][cas->fila].ocupacion = f; };

    int leer_filas() const { return n_filas; }
    int leer_columnas() const { return n_columnas; }
    casilla leer_casilla(int i, int j) const { return matriz[i][j]; }

    ficha* encontrar_rey(const ENUM_COLOR& c) const;

    // Destructor de tablero
    ~tablero();
};