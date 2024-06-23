#include "fichas.h"
#include "casillas.h"
#include <cmath>

ficha::ficha(casilla* _pos, color _color) {
	posicion = _pos;
	c = _color;
}


//PEON
void peon::mover(casilla& casilla) {
	int mov_f = casilla.leer_fila() - pos_fila(), mov_c = casilla.leer_columna() - pos_columna();
	colision f_casilla = gestor_movimientos::comprobar_ocupacion(this, casilla);

	//Primer caso posible, esta ocupado por nuestra propia ficha
	if (f_casilla == colision::amigo) {
		//Mensaje error
		return;
	}

	//Desglose de movimientos posibles para los dos colores
	switch (c) {
	blanca:
		if (mov_c < -2 || mov_c >= 0 || abs(mov_f) > 1 || (mov_f == 0 && f_casilla != colision::vacio) || (mov_c == -2 && (ha_movido == true || mov_f != 0)) || (mov_f != 0 && f_casilla != colision::vacio)) {
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
	gestor_movimientos::cambiar_ocupaci�n(this, &casilla);

}

//TORRE
void torre::mover(casilla& casilla, const tablero& tablero) {
	int mov_f = casilla.leer_fila() - pos_fila(), mov_c = casilla.leer_columna() - pos_columna();
	colision f_casilla = gestor_movimientos::comprobar_ocupacion(this, casilla);

	//Primer caso posible, esta ocupado por nuestra propia ficha
	if (f_casilla == colision::amigo || (mov_f != 0 && mov_c != 0) || (mov_f == mov_c == 0)) {
		//Mensaje error
		return;
	}
	
	if (gestor_movimientos::comprobar_colision(*this, casilla, tablero)) {
		//Mensaje error
		return;
	}

	gestor_movimientos::cambiar_ocupaci�n(this, &casilla);

}

//CABALLO
void caballo::mover(casilla& casilla) {
	int mov_f = abs(casilla.leer_fila() - pos_fila()), mov_c = abs(casilla.leer_columna() - pos_columna());
	colision f_casilla = gestor_movimientos::comprobar_ocupacion(this, casilla);

	//Primer caso posible, esta ocupado por nuestra propia ficha
	if (f_casilla == colision::amigo || (mov_f == 2 && mov_c != 1) || (mov_f == mov_c == 0)) { //SIN ACABAR
		//Mensaje error
		return;
	}

	gestor_movimientos::cambiar_ocupaci�n(this, &casilla);

}

//ALFIL
void alfil::mover(casilla& casilla, const tablero& tablero) {
	int mov_f = casilla.leer_fila() - pos_fila(), mov_c = casilla.leer_columna() - pos_columna();
	colision f_casilla = gestor_movimientos::comprobar_ocupacion(this, casilla);

	//Primer caso posible, esta ocupado por nuestra propia ficha
	if (f_casilla == colision::amigo || (mov_f != mov_c) || (mov_f == mov_c == 0)) {
		//Mensaje error
		return;
	}

	if (gestor_movimientos::comprobar_colision(*this, casilla, tablero)) {
		//Mensaje error
		return;
	}

	gestor_movimientos::cambiar_ocupaci�n(this, &casilla);

}

//REINA
void reina::mover(casilla& casilla, const tablero& tablero) {
	int mov_f = casilla.leer_fila() - pos_fila(), mov_c = casilla.leer_columna() - pos_columna();
	colision f_casilla = gestor_movimientos::comprobar_ocupacion(this, casilla);

	//Primer caso posible, esta ocupado por nuestra propia ficha
	if (f_casilla == colision::amigo || (mov_f != 0 && mov_c != 0 && mov_f != mov_c) || (mov_f == mov_c == 0)) {
		//Mensaje error
		return;
	}

	if (gestor_movimientos::comprobar_colision(*this,casilla,tablero)) {
		//Mensaje error
		return;
	}

	gestor_movimientos::cambiar_ocupaci�n(this, &casilla);

}

//REY
void rey::mover(casilla& casilla, const tablero& tablero) {
	int mov_f = casilla.leer_fila() - pos_fila(), mov_c = casilla.leer_columna() - pos_columna();
	colision f_casilla = gestor_movimientos::comprobar_ocupacion(this, casilla);

	//Primer caso posible, esta ocupado por nuestra propia ficha
	if (f_casilla == colision::amigo || abs(mov_f) != 1 || abs(mov_c) != 1 || (mov_f == mov_c == 0)) {
		//Mensaje error
		return;
	}

	if (en_jaque(casilla, tablero) == true) {
		//Mensaje error por jaque
		return;
	}

	gestor_movimientos::cambiar_ocupaci�n(this, &casilla);

}

//Probablemente podriamos acceder a la casilla que queremos desde la casilla de entrada (al estar todas en una matriz)
//Por simpleza, accedemos desde el tablero
//En la funci�n hacemos muchas veces la misma comprobacion, puede ser interesante almacenarla en una funcion
//La funcion podr�a ser "comprobar jaque", que se limitar�a a valorar una casilla suelta

void rey::comprobar_jaque(bool& fin, bool& jaque, const tablero& tablero, int i, int columna, tipo t) {
	casilla c_aux = tablero.leer_casilla(i, columna);
	ficha* f_aux = c_aux.leer_ocupacion();
	if (f_aux != nullptr) {
		if (c != f_aux->leer_color() && (f_aux->leer_tipo() == t || f_aux->leer_tipo() == tipo::reina)) {
			jaque = true;
		}
		else {
			fin = true;
		}
	}
}

bool rey::en_jaque(const casilla& cas, const tablero& tablero) {

	bool fin = false, jaque = false;
	int fila = cas.leer_fila(), columna = cas.leer_columna(), n_filas = tablero.leer_filas(), n_columnas = tablero.leer_columnas();

	//Comprobaci�n para torres:
	for (int i = fila + 1; i <= n_filas && fin == false; i++) {
		comprobar_jaque(fin, jaque, tablero, i, columna, tipo::torre);
		if (jaque == true) {
			return jaque;
		}
	}
	fin = false;
	jaque = false;

	for (int i = fila - 1; i >= 0 && fin == false; i--) {
		comprobar_jaque(fin, jaque, tablero, i, columna, tipo::torre);
		if (jaque == true) {
			return jaque;
		}
	}
	fin = false;
	jaque = false;

	for (int i = columna + 1; i <= n_columnas && fin == false; i++) {
		comprobar_jaque(fin, jaque, tablero, i, columna, tipo::torre);
		if (jaque == true) {
			return jaque;
		}
	}
	fin = false;
	jaque = false;

	for (int i = columna - 1; i >= 0 && fin == false; i--) {
		comprobar_jaque(fin, jaque, tablero, i, columna, tipo::torre);
		if (jaque == true) {
			return jaque;
		}
	}
	fin = false;
	jaque = false;

	//Comprobaci�n Alfiles
	for (int i = 1; i + fila <= n_filas && i + columna <= n_columnas && fin == false; i++) {
		comprobar_jaque(fin, jaque, tablero, i, columna, tipo::alfil);
		if (jaque == true) {
			return jaque;
		}
	}
	fin = false;
	jaque = false;

	for (int i = 1; fila - i >= 0 && i + columna <= n_columnas && fin == false; i++) {
		comprobar_jaque(fin, jaque, tablero, i, columna, tipo::torre);
		if (jaque == true) {
			return jaque;
		}
	}
	fin = false;
	jaque = false;

	for (int i = 1; fila + i <= n_filas && columna - i >= 0 && fin == false; i++) {
		comprobar_jaque(fin, jaque, tablero, i, columna, tipo::torre);
		if (jaque == true) {
			return jaque;
		}
	}
	fin = false;
	jaque = false;

	for (int i = 1; fila - i >= 0 && columna - i >= 0 && fin == false; i++) {
		comprobar_jaque(fin, jaque, tablero, i, columna, tipo::torre);
		if (jaque == true) {
			return jaque;
		}
	}
	fin = false;
	jaque = false;

	//Comprobaci�n caballos
	casilla c_aux = tablero.leer_casilla(fila + 2, columna + 1);
	ficha* f_aux = c_aux.leer_ocupacion();
	if (f_aux != nullptr) {
		if (c != f_aux->leer_color() && f_aux->leer_tipo() == tipo::caballo) {
			return true;
		}
		else {
			fin = true;
		}
	}
	fin = false;

	casilla c_aux = tablero.leer_casilla(fila + 2, columna - 1);
	ficha* f_aux = c_aux.leer_ocupacion();
	if (f_aux != nullptr) {
		if (c != f_aux->leer_color() && f_aux->leer_tipo() == tipo::caballo) {
			return true;
		}
		else {
			fin = true;
		}
	}
	fin = false;

	casilla c_aux = tablero.leer_casilla(fila - 2, columna + 1);
	ficha* f_aux = c_aux.leer_ocupacion();
	if (f_aux != nullptr) {
		if (c != f_aux->leer_color() && f_aux->leer_tipo() == tipo::caballo) {
			return true;
		}
		else {
			fin = true;
		}
	}
	fin = false;

	casilla c_aux = tablero.leer_casilla(fila - 2, columna - 1);
	ficha* f_aux = c_aux.leer_ocupacion();
	if (f_aux != nullptr) {
		if (c != f_aux->leer_color() && f_aux->leer_tipo() == tipo::caballo) {
			return true;
		}
		else {
			fin = true;
		}
	}
	fin = false;

	casilla c_aux = tablero.leer_casilla(fila + 1, columna + 2);
	ficha* f_aux = c_aux.leer_ocupacion();
	if (f_aux != nullptr) {
		if (c != f_aux->leer_color() && f_aux->leer_tipo() == tipo::caballo) {
			return true;
		}
		else {
			fin = true;
		}
	}
	fin = false;

	casilla c_aux = tablero.leer_casilla(fila - 1, columna + 2);
	ficha* f_aux = c_aux.leer_ocupacion();
	if (f_aux != nullptr) {
		if (c != f_aux->leer_color() && f_aux->leer_tipo() == tipo::caballo) {
			return true;
		}
		else {
			fin = true;
		}
	}
	fin = false;

	casilla c_aux = tablero.leer_casilla(fila + 1, columna - 2);
	ficha* f_aux = c_aux.leer_ocupacion();
	if (f_aux != nullptr) {
		if (c != f_aux->leer_color() && f_aux->leer_tipo() == tipo::caballo) {
			return true;
		}
		else {
			fin = true;
		}
	}
	fin = false;

	casilla c_aux = tablero.leer_casilla(fila - 1, columna - 2);
	ficha* f_aux = c_aux.leer_ocupacion();
	if (f_aux != nullptr) {
		if (c != f_aux->leer_color() && f_aux->leer_tipo() == tipo::caballo) {
			return true;
		}
		else {
			fin = true;
		}
	}
	fin = false;

	return false;
}