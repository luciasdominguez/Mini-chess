#pragma once

//	ficha* ocupacion; ///Cada casilla tiene una posible ficha, este ser�a otro par�metro
//#include "fichas.h"
//#include "gestor_movimientos.h"
//#include <iostream>
//using namespace std;

class casilla {
private:
	friend class ficha;
	friend class tablero;
	friend class Cl_logica;

	ficha* ocupacion = nullptr; ///Cada casilla tiene una posible ficha, este ser�a otro par�metro
	
	int fila = 0, columna = 0; ///Cada casilla tiene una fila y una columna

public:
	//casilla() { ; } // Constructor predeterminado de casilla
	casilla();

	casilla(int f, int colm):
		fila(f),
		columna(colm),
		ocupacion(nullptr)
	{}

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