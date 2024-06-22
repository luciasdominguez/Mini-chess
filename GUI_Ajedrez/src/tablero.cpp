#include "tablero.h"

tablero::tablero(const int filas_, const int columnas_)// : n_filas(filas_), n_columnas(columnas_)
{
    n_filas = filas_;
    n_columnas = columnas_;

    // crear el tablero
    matriz = new casilla * [filas_];
    for (int i = 0; i < filas_; i++) {
        matriz[i] = new casilla[columnas_];
    }
}

tablero::~tablero() {
    // Liberar la memoria del tablero
    for (int i = 0; i < n_filas; ++i)
    {
        delete[] matriz[i];
    }
    delete[] matriz;
}