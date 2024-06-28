#pragma once

enum class color { blanca, negra };
class ficha {
private:
	int pos_fil; ///Fila en la que está la ficha
	int pos_col; ///Columna en la que está la ficha
	color c;

public:
	ficha(int fila, int columna, color color_ficha);
	//void mover();
};

class casilla {
private:
	int fila, columna; ///Cada casilla tiene una fila y una columna
	ficha* ocupacion; ///Cada casilla tiene una posible ficha, este sería otro parámetro

public:
	casilla(); // Constructor predeterminado de casilla
    casilla(int _fila, int _columna, ficha* _ficha);
	void leer_casilla();
	void asignar_casilla();
	//void cambiar_ocupacion();
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

    // Destructor de tablero
	~tablero();
};





