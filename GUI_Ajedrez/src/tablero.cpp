#include "tablero.h"
#include "fichas.h"

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

ficha* tablero::encontrar_rey(const ENUM_COLOR& c) const {
    ficha* aux = nullptr;

    for (int i = 0; i < n_filas; i++) {
        for (int j = 0; j < n_columnas; j++) {
            aux = matriz[i][j].leer_ocupacion();
            if (aux)
                if (aux->leer_color() == c && aux->leer_tipo() == tipo::rey) {
                    return aux;
                }
        }
    }
}