#pragma once
#include "fichas.h"
//#include "gestor_movimientos.h"
//#include <iostream>
//using namespace std;

class casilla {
private:
	int fila, columna; ///Cada casilla tiene una fila y una columna
	ficha* ocupacion; ///Cada casilla tiene una posible ficha, este sería otro parámetro

public:
	//casilla() { ; } // Constructor predeterminado de casilla
	casilla();

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