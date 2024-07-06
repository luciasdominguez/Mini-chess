#pragma once
#include "casillas.h"
#include "clases.h"
#include "vector"
//#include "fichas.h"
using std::vector;

class tablero
{
private:
    friend class Cl_logica;
    friend class ficha;
    friend class Rey;
    std::vector<vector<casilla>> casillas_tablero;

    //casilla** matriz;  // Matriz de casillas
    int n_filas = 8, n_columnas = 8;

public:
    tablero() = default;
    // Constructor de tablero
    tablero(int filas_, int columnas_);
    void cambiar_casilla(casilla cas, ficha* f) { casillas_tablero[cas.fila][cas.columna].ocupacion = f; };
    void cambiar_casilla(casilla* cas, ficha* f) { casillas_tablero[cas->fila][cas->columna].ocupacion = f; };

    int leer_filas() const { return n_filas; }
    int leer_columnas() const { return n_columnas; }
    casilla leer_casilla(int i, int j) const { return casillas_tablero.at(i).at(j); }
    void gravedad();
    tablero simular_gravedad() const; //Devuelve un tablero con la gravedad aplicada a todas las piezas
    ficha* encontrar_rey(const ENUM_COLOR& c) const;

    // Destructor de tablero
    ~tablero();
};