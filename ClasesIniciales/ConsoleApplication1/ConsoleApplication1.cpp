
#include "clases.h"
#include <iostream>

//Constructores
casilla::casilla() : fila(0), columna(0), ocupacion(nullptr) {}  // Constructor predeterminado (si no envio parametros) de casilla
casilla::casilla(int _fila, int _columna, ficha* _ficha = nullptr): fila(_fila), columna(_columna), ocupacion(_ficha) {}
ficha::ficha(int fila, int columna, color color_ficha) : pos_fil(fila), pos_col(columna), c(color_ficha) {}

tablero::tablero(int filas_, int columnas_) : n_filas(filas_), n_columnas(columnas_)
{
    // Crear las filas
    filas = new casilla * [filas_];
    for (int i = 0; i < filas_; i++)
        for (int j = 0; j < filas_; j++)
            filas[i] = new casilla [columnas_];

    int k = 0;
    casillas = new casilla[filas_ * columnas_];
    for (int i = 0; i < filas_; i++)
    {
        for (int j = 0; j < filas_; j++)
        {
            filas[i][j] = casillas[k];
            k++;
        }
    }
}

//Destructores
tablero::~tablero() {
    // Liberar la memoria de las filas
    for (int i = 0; i < n_filas; ++i)
    {
        delete[] filas[i];
    }
    delete[] filas;
}

void casilla::leer_casilla() { std::cout << fila << " " << columna << std::endl; }

int main()
{

}
