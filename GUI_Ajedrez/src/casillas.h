#pragma once

class casilla {
private:
	friend class ficha;
	friend class tablero;
	friend class Cl_logica;
	friend class gestor_movimientos;

	ficha* ocupacion = nullptr; ///Cada casilla tiene una posible ficha, este sería otro parámetro
	
	int fila = 0, columna = 0; ///Cada casilla tiene una fila y una columna

public:
	casilla();

	casilla(int f, int colm):
		fila(f),
		columna(colm),
		ocupacion(nullptr)
	{}

	void set_fila(int f) { fila = f; }
	void set_columna(int c) { columna = c; }


	ficha* comprobar_ocupacion() { return ocupacion; }

	int leer_fila() const { return fila; }
	int leer_columna() const { return columna; }
	ficha* leer_ocupacion() const { return ocupacion; }


	
};