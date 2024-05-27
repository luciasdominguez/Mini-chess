#pragma once
#include "piezas.h"
#include "gestor_movimientos.h"


class casilla {
private:
	int fila, columna; ///Cada casilla tiene una fila y una columna
	ficha* ocupacion; ///Cada casilla tiene una posible ficha, este sería otro parámetro

public:
	casilla(); // Constructor predeterminado de casilla
    casilla(int _fila, int _columna, ficha* _ficha);
	
	void leer_casilla();
	ficha* leer_ocupacion() const { return ocupacion; };

	int leer_fila() const { return fila; };
	int leer_columna() const { return columna; };

	friend class Gestor_Movimientos;
};

class tablero
{
private:
    casilla** filas;  // Matriz de casillas
	casilla* casillas = new casilla [n_filas * n_columnas];
    int n_filas, n_columnas;

public:
    // Constructor de tablero
    tablero(int filas_, int columnas_);
	int leer_filas() const { return n_filas; };
	int leer_columnas() const { return n_columnas; };
	casilla leer_casilla(int fila, int columna) const { return filas[fila][columna]; };

    // Destructor de tablero
	~tablero();
};





