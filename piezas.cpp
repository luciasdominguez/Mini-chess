#include "piezas.h"
#include "gestor_movimientos.h"
#include <cmath>

//PEON
void peon::mover(casilla& casilla) {
	int mov_f = casilla.leer_fila() - pos_fil, mov_c = casilla.leer_columna() - pos_col;
	colision f_casilla = Gestor_Movimientos::comprobar_ocupacion(*this, casilla);

	//Primer caso posible, esta ocupado por nuestra propia ficha
	if (f_casilla == colision::amigo) {
		//Mensaje error
		return;
	}

	//Desglose de movimientos posibles para los dos colores
	switch (c){
	blanca:
		if (mov_c < -2 || mov_c >=0 || abs(mov_f) > 1  || (mov_f == 0 && f_casilla != colision::vacio) || (mov_c == -2 && (ha_movido == true || mov_f != 0)) || (mov_f !=0 && f_casilla != colision::vacio)) {
			return;
		}
		break;

	negra:
		if (mov_c > 2 || mov_c <= 0 || abs(mov_f) > 1 || (mov_f == 0 && f_casilla != colision::vacio) || (mov_c == 2 && (ha_movido == true || mov_f != 0)) || (mov_f != 0 && f_casilla != colision::vacio)) {
			return;
		}
		break;
	}

	//Si puede realizar el movimiento (es decir, no salimos antes de la funcion)
	Gestor_Movimientos::cambiar_ocupacion(casilla,*this);

}

//TORRE
void torre::mover(casilla& casilla) {
	int mov_f = casilla.leer_fila() - pos_fil, mov_c = casilla.leer_columna() - pos_col;
	colision f_casilla = Gestor_Movimientos::comprobar_ocupacion(*this, casilla);

	//Primer caso posible, esta ocupado por nuestra propia ficha
	if (f_casilla == colision::amigo || (mov_f != 0 && mov_c != 0) || (mov_f == mov_c == 0)) {
		//Mensaje error
		return;
	}
	//NO ESTA COMPLETO, AHORA MISMO ES CAPAZ DE ATRAVESAR PIEZAS
	Gestor_Movimientos::cambiar_ocupacion(casilla, *this);

}

//CABALLO
void caballo::mover(casilla& casilla) {
	int mov_f = abs(casilla.leer_fila() - pos_fil), mov_c = abs(casilla.leer_columna() - pos_col);
	colision f_casilla = Gestor_Movimientos::comprobar_ocupacion(*this, casilla);

	//Primer caso posible, esta ocupado por nuestra propia ficha
	if (f_casilla == colision::amigo || (mov_f == 2 && mov_c != 1) || (mov_f == mov_c == 0)) { //SIN ACABAR
		//Mensaje error
		return;
	}

	Gestor_Movimientos::cambiar_ocupacion(casilla, *this);
	
}

//ALFIL
void alfil::mover(casilla& casilla) {
	int mov_f = casilla.leer_fila() - pos_fil, mov_c = casilla.leer_columna() - pos_col;
	colision f_casilla = Gestor_Movimientos::comprobar_ocupacion(*this, casilla);

	//Primer caso posible, esta ocupado por nuestra propia ficha
	if (f_casilla == colision::amigo || (mov_f != mov_c) || (mov_f == mov_c == 0)) {
		//Mensaje error
		return;
	}
	//NO ESTA COMPLETO, AHORA MISMO ES CAPAZ DE ATRAVESAR PIEZAS
	Gestor_Movimientos::cambiar_ocupacion(casilla, *this);

}

//REINA
void reina::mover(casilla& casilla) {
	int mov_f = casilla.leer_fila() - pos_fil, mov_c = casilla.leer_columna() - pos_col;
	colision f_casilla = Gestor_Movimientos::comprobar_ocupacion(*this, casilla);

	//Primer caso posible, esta ocupado por nuestra propia ficha
	if (f_casilla == colision::amigo || (mov_f != 0 && mov_c != 0 && mov_f != mov_c) || (mov_f == mov_c == 0)) {
		//Mensaje error
		return;
	}
	//NO ESTA COMPLETO, AHORA MISMO ES CAPAZ DE ATRAVESAR PIEZAS
	Gestor_Movimientos::cambiar_ocupacion(casilla, *this);

}

//REY
void rey::mover(casilla& casilla) {
	int mov_f = casilla.leer_fila() - pos_fil, mov_c = casilla.leer_columna() - pos_col;
	colision f_casilla = Gestor_Movimientos::comprobar_ocupacion(*this, casilla);

	//Primer caso posible, esta ocupado por nuestra propia ficha
	if (f_casilla == colision::amigo || abs(mov_f) != 1 || abs(mov_c) != 1 || (mov_f == mov_c == 0)) {
		//Mensaje error
		return;
	}
	
	if (en_jaque(casilla, /*tablero*/) == true) {
		//Mensaje error por jaque
		return;
	}

	Gestor_Movimientos::cambiar_ocupacion(casilla, *this);

}

//Probablemente podriamos acceder a la casilla que queremos desde la casilla de entrada (al estar todas en una matriz)
//Por simpleza, accedemos desde el tablero
//En la función hacemos muchas veces la misma comprobacion, puede ser interesante almacenarla en una funcion
//La funcion podría ser "comprobar jaque", que se limitaría a valorar una casilla suelta
bool rey::en_jaque(const casilla& cas, const tablero& tablero) {

	bool fin = false;
	int fila = cas.leer_fila(), columna = cas.leer_columna(), n_filas = tablero.leer_filas(), n_columnas = tablero.leer_columnas();

	//Comprobación para torres:
	for (int i = fila + 1; i <= n_filas && fin == false; i++) {
		casilla c_aux = tablero.leer_casilla(i, columna);
		ficha* f_aux = c_aux.leer_ocupacion();
		if (f_aux != nullptr) {
			if (c != f_aux->leer_color() && (f_aux->leer_tipo() == tipo::torre || f_aux->leer_tipo() == tipo::reina)) {
				return true;
			}
			else {
				fin = true;
			}
		}
	}

	for (int i = fila - 1; i >= 0 && fin == false; i--) {
		casilla c_aux = tablero.leer_casilla(i, columna);
		ficha* f_aux = c_aux.leer_ocupacion();
		if (f_aux != nullptr) {
			if (c != f_aux->leer_color() && (f_aux->leer_tipo() == tipo::torre || f_aux->leer_tipo() == tipo::reina)) {
				return true;
			}
			else {
				fin = true;
			}
		}
	}

	for (int i = columna + 1; i <= n_columnas && fin == false; i++) {
		casilla c_aux = tablero.leer_casilla(fila, i);
		ficha* f_aux = c_aux.leer_ocupacion();
		if (f_aux != nullptr) {
			if (c != f_aux->leer_color() && (f_aux->leer_tipo() == tipo::torre || f_aux->leer_tipo() == tipo::reina)) {
				return true;
			}
			else {
				fin = true;
			}
		}
	}

	for (int i = columna - 1; i >= 0 && fin == false; i--) {
		casilla c_aux = tablero.leer_casilla(fila, i);
		ficha* f_aux = c_aux.leer_ocupacion();
		if (f_aux != nullptr) {
			if (c != f_aux->leer_color() && (f_aux->leer_tipo() == tipo::torre || f_aux->leer_tipo() == tipo::reina)) {
				return true;
			}
			else {
				fin = true;
			}
		}
	}


	//Comprobación Alfiles
	for (int i = 1; i + fila <= n_filas && i + columna <= n_columnas && fin == false; i++) {
		casilla c_aux = tablero.leer_casilla(fila+i, columna+i);
		ficha* f_aux = c_aux.leer_ocupacion();
		if (f_aux != nullptr) {
			if (c != f_aux->leer_color() && (f_aux->leer_tipo() == tipo::alfil || f_aux->leer_tipo() == tipo::reina)) {
				return true;
			}
			else {
				fin = true;
			}
		}
	}

	for (int i = 1;  fila - i >= 0 && i + columna <= n_columnas && fin == false; i++) {
		casilla c_aux = tablero.leer_casilla(fila - i, columna + i);
		ficha* f_aux = c_aux.leer_ocupacion();
		if (f_aux != nullptr) {
			if (c != f_aux->leer_color() && (f_aux->leer_tipo() == tipo::alfil || f_aux->leer_tipo() == tipo::reina)) {
				return true;
			}
			else {
				fin = true;
			}
		}
	}

	for (int i = 1; fila + i <= n_filas && columna - i >= 0 && fin == false; i++) {
		casilla c_aux = tablero.leer_casilla(fila + i, columna - i);
		ficha* f_aux = c_aux.leer_ocupacion();
		if (f_aux != nullptr) {
			if (c != f_aux->leer_color() && (f_aux->leer_tipo() == tipo::alfil || f_aux->leer_tipo() == tipo::reina)) {
				return true;
			}
			else {
				fin = true;
			}
		}
	}

	for (int i = 1; fila - i >= 0 && columna - i >= 0 && fin == false; i++) {
		casilla c_aux = tablero.leer_casilla(fila - i, columna - i);
		ficha* f_aux = c_aux.leer_ocupacion();
		if (f_aux != nullptr) {
			if (c != f_aux->leer_color() && (f_aux->leer_tipo() == tipo::alfil || f_aux->leer_tipo() == tipo::reina)) {
				return true;
			}
			else {
				fin = true;
			}
		}
	}

	//Comprobación caballos
	casilla c_aux = tablero.leer_casilla(fila + 2, columna + 1);
	ficha* f_aux = c_aux.leer_ocupacion();
	if (f_aux != nullptr) {
		if (c != f_aux->leer_color() && (f_aux->leer_tipo() == tipo::alfil || f_aux->leer_tipo() == tipo::reina)) {
			return true;
		}
		else {
			fin = true;
		}
	}

	casilla c_aux = tablero.leer_casilla(fila + 2, columna - 1);
	ficha* f_aux = c_aux.leer_ocupacion();
	if (f_aux != nullptr) {
		if (c != f_aux->leer_color() && (f_aux->leer_tipo() == tipo::alfil || f_aux->leer_tipo() == tipo::reina)) {
			return true;
		}
		else {
			fin = true;
		}
	}

	casilla c_aux = tablero.leer_casilla(fila - 2, columna + 1);
	ficha* f_aux = c_aux.leer_ocupacion();
	if (f_aux != nullptr) {
		if (c != f_aux->leer_color() && (f_aux->leer_tipo() == tipo::alfil || f_aux->leer_tipo() == tipo::reina)) {
			return true;
		}
		else {
			fin = true;
		}
	}

	casilla c_aux = tablero.leer_casilla(fila - 2, columna - 1);
	ficha* f_aux = c_aux.leer_ocupacion();
	if (f_aux != nullptr) {
		if (c != f_aux->leer_color() && (f_aux->leer_tipo() == tipo::alfil || f_aux->leer_tipo() == tipo::reina)) {
			return true;
		}
		else {
			fin = true;
		}
	}

	casilla c_aux = tablero.leer_casilla(fila + 1, columna + 2);
	ficha* f_aux = c_aux.leer_ocupacion();
	if (f_aux != nullptr) {
		if (c != f_aux->leer_color() && (f_aux->leer_tipo() == tipo::alfil || f_aux->leer_tipo() == tipo::reina)) {
			return true;
		}
		else {
			fin = true;
		}
	}
	
	casilla c_aux = tablero.leer_casilla(fila + 1, columna + 2);
	ficha* f_aux = c_aux.leer_ocupacion();
	if (f_aux != nullptr) {
		if (c != f_aux->leer_color() && (f_aux->leer_tipo() == tipo::alfil || f_aux->leer_tipo() == tipo::reina)) {
			return true;
		}
		else {
			fin = true;
		}
	}

	return false;
}