#pragma once

//	ficha* ocupacion; ///Cada casilla tiene una posible ficha, este sería otro parámetro
//#include "fichas.h"
//#include "gestor_movimientos.h"
//#include <iostream>
//using namespace std;

class casilla {
private:
	friend class ficha;
	ficha* ocupacion; ///Cada casilla tiene una posible ficha, este sería otro parámetro

	int fila, columna; ///Cada casilla tiene una fila y una columna

public:
	//casilla() { ; } // Constructor predeterminado de casilla
	casilla();
	void set_fila(int f) { fila = f; }
	void set_columna(int c) { columna = c; }
	//casilla(int _fila, int _columna, fichas* _ficha);


	//void leer_casilla();
	//void asignar_casilla();


	ficha* comprobar_ocupacion() { return ocupacion; }

	int leer_fila() const { return fila; }
	int leer_columna() const { return columna; }
	ficha* leer_ocupacion() const { return ocupacion; }
	//void cambiar_ocupacion();

	friend class gestor_movimientos;
	//friend class ficha;
	//friend class tablero;
};