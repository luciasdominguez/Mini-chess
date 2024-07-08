#include "fichas.h"
#include "gestor_movimientos.h"
#include <cmath>

ficha::ficha(casilla* _pos, ENUM_COLOR _color) {
	posicion = _pos;
	campo_color = _color;
}


//PEON
bool Peon::mover(casilla& Casilla, const tablero& Tablero) {
	int mov_f = Casilla.leer_fila() - pos_fila(), mov_c = Casilla.leer_columna() - pos_columna();
	colision f_casilla = gestor_movimientos::comprobar_ocupacion(this, Casilla);

	Rey R = Rey(Tablero.encontrar_rey(this->campo_color)->leer_posicion(), Tablero.encontrar_rey(this->campo_color)->leer_color());
	if (mov_f == 0 && mov_c == 0) {
		return false;
	}
	//Primer caso posible, esta ocupado por nuestra propia ficha
	if (f_casilla == colision::amigo) {
		//Mensaje error
		return false;
	}

	//Desglose de movimientos posibles para los dos colores
	switch (campo_color) {
	case blanca:
		if(mov_c > 2 
			|| mov_c <= 0 
			|| abs(mov_f) > 1 
			|| (mov_f == 0 && f_casilla != colision::vacio) 
			|| (mov_c == 2 && (ha_movido == true || mov_f != 0)) 
			|| (mov_f != 0 && f_casilla == colision::vacio)) {
			return false;
		}
		break;
		
	case negra:
		if (mov_c < -2 
			|| mov_c >= 0 
			|| abs(mov_f) > 1 
			|| (mov_f == 0 && f_casilla != colision::vacio) 
			|| (mov_c == -2 && (ha_movido == true 
				|| mov_f != 0)) 
			|| (mov_f != 0 && f_casilla == colision::vacio)) {
			return false;
		}
		break;
	}

	this->ha_movido = true;

	return true;
}

//TORRE
bool Torre::mover(casilla& Casilla, const tablero& Tablero) {
	int mov_f = Casilla.leer_fila() - pos_fila(), mov_c = Casilla.leer_columna() - pos_columna();
	colision f_casilla = gestor_movimientos::comprobar_ocupacion(this, Casilla);
	Rey R = Rey(Tablero.encontrar_rey(this->campo_color)->leer_posicion(), Tablero.encontrar_rey(this->campo_color)->leer_color());

	//Primer caso posible, esta ocupado por nuestra propia ficha
	bool aux = (mov_f != 0 && mov_c != 0);
	bool aux_2 = (mov_f == mov_c == 0);

	if (f_casilla == colision::amigo || (mov_f != 0 && mov_c != 0) || ((mov_f == 0) && (mov_c == 0))) {
		//Mensaje error
		return false;
	}

	if (gestor_movimientos::comprobar_colision(*this, Casilla, Tablero)) {
		//Mensaje error
		return false;
	}


	return true;
}

//CABALLO
bool Caballo::mover(casilla& Casilla, const tablero& Tablero) {
	int mov_f = abs(Casilla.leer_fila() - pos_fila()), mov_c = abs(Casilla.leer_columna() - pos_columna());
	colision f_casilla = gestor_movimientos::comprobar_ocupacion(this, Casilla);
	Rey R = Rey(Tablero.encontrar_rey(this->campo_color)->leer_posicion(), Tablero.encontrar_rey(this->campo_color)->leer_color());

	//Primer caso, numero de casiilas movidas ilegal
	if (mov_f != 2 && mov_c != 2) {
		return false;
	}

	if (f_casilla == colision::amigo || (mov_f == 2 && mov_c != 1) || (mov_c == 2 && mov_f != 1) || (mov_f == 0 && mov_c == 0)) { 
		//Mensaje error
		return false;
	}

	


	return true;
}

//ALFIL
bool Alfil::mover(casilla& Casilla, const tablero& Tablero) {
	int mov_f = Casilla.leer_fila() - pos_fila(), mov_c = Casilla.leer_columna() - pos_columna();
	colision f_casilla = gestor_movimientos::comprobar_ocupacion(this, Casilla);
	Rey R = Rey(Tablero.encontrar_rey(this->campo_color)->leer_posicion(), Tablero.encontrar_rey(this->campo_color)->leer_color());

	//Primer caso posible, esta ocupado por nuestra propia ficha
	if (f_casilla == colision::amigo || (abs(mov_f) != abs(mov_c)) || (mov_f == 0 &&  mov_c == 0)) {
		//Mensaje error
		return false;
	}

	if (gestor_movimientos::comprobar_colision(*this, Casilla, Tablero)) {
		//Mensaje error
		return false;
	}

	


	return true;
}

//REINA
bool Reina::mover(casilla& Casilla, const tablero& Tablero) {
	int mov_f = Casilla.leer_fila() - pos_fila(), mov_c = Casilla.leer_columna() - pos_columna();
	colision f_casilla = gestor_movimientos::comprobar_ocupacion(this, Casilla);
	Rey R = Rey(Tablero.encontrar_rey(this->campo_color)->leer_posicion(), Tablero.encontrar_rey(this->campo_color)->leer_color());

	//Primer caso posible, esta ocupado por nuestra propia ficha
	if (f_casilla == colision::amigo || (mov_f != 0 && mov_c != 0 && abs(mov_f) != abs(mov_c)) || mov_f == 0 && mov_c == 0) {
		//Mensaje error
		return false;
	}

	if (gestor_movimientos::comprobar_colision(*this, Casilla, Tablero)) {
		//Mensaje error
		return false;
	}

	

	return true;
}

//REY
bool Rey::mover(casilla& casilla, const tablero& tablero) {
	int mov_f = casilla.leer_fila() - pos_fila(), mov_c = casilla.leer_columna() - pos_columna();
	colision f_casilla = gestor_movimientos::comprobar_ocupacion(this, casilla);


	//Primer caso posible, esta ocupado por nuestra propia ficha
	if (f_casilla == colision::amigo || (abs(mov_f) != 1 && abs(mov_c) != 1) || (mov_f == 0) && (mov_c == 0)) {
		//Mensaje error
		return false;
	}

	//////if (en_jaque(casilla, tablero) == true) {
	//////	//Mensaje error por jaque
	//////	return false;
	//////}

	return true;
}



//Probablemente podriamos acceder a la casilla que queremos desde la casilla de entrada (al estar todas en una matriz)
//Por simpleza, accedemos desde el tablero
//En la función hacemos muchas veces la misma comprobacion, puede ser interesante almacenarla en una funcion
//La funcion podría ser "comprobar jaque", que se limitaría a valorar una casilla suelta

void Rey::comprobar_jaque(bool& fin, bool& jaque, const tablero& tablero, int i, int columna, ENUM_TIPO t) {
	
	casilla c_aux = tablero.leer_casilla(i, columna);
	ficha* f_aux = c_aux.leer_ocupacion();
	if (f_aux) {
			if (campo_color != f_aux->leer_color() && (f_aux->leer_tipo() == t || f_aux->leer_tipo() == reina)) {
				jaque = true;
			}
			else if (campo_color == f_aux->leer_color()) {
				fin = true;
			}
	}
}


bool Rey::en_jaque(const casilla& cas, const tablero& tablero) {

	bool fin = false, jaque = false;
	int fila = cas.leer_fila(), columna = cas.leer_columna(), n_filas = tablero.leer_filas(), n_columnas = tablero.leer_columnas();
	
	//Comprobación para torres:
	for (int i = fila + 1; i < n_filas && fin == false; i++) {
		comprobar_jaque(fin, jaque, tablero, i, columna,torre);
		if (jaque == true) {
			return jaque;
		}
	}
	fin = false;
	jaque = false;

	for (int i = fila - 1; i >= 0 && fin == false; i--) {
		comprobar_jaque(fin, jaque, tablero, i, columna, torre);
		if (jaque == true) {
			return jaque;
		}
	}
	fin = false;
	jaque = false;

	for (int i = columna + 1; i < n_columnas && fin == false; i++) {
		comprobar_jaque(fin, jaque, tablero, fila, i, torre);
		if (jaque == true) {
			return jaque;
		}
	}
	fin = false;
	jaque = false;

	for (int i = columna - 1; i >= 0 && fin == false; i--) {
		comprobar_jaque(fin, jaque, tablero, fila, i,torre);
		if (jaque == true) {
			return jaque;
		}
	}
	fin = false;
	jaque = false;

	//Comprobación Alfiles
	for (int i = 1; i + fila < n_filas && i + columna < n_columnas && fin == false; i++) {
		comprobar_jaque(fin, jaque, tablero, fila + i, columna + i,alfil);
		if (jaque == true) {
			return jaque;
		}
	}
	fin = false;
	jaque = false;

	for (int i = 1; fila - i >= 0 && i + columna < n_columnas && fin == false; i++) {
		comprobar_jaque(fin, jaque, tablero, fila - i, columna + i, alfil);
		if (jaque == true) {
			return jaque;
		}
	}
	fin = false;
	jaque = false;

	for (int i = 1; fila + i < n_filas && columna - i >= 0 && fin == false; i++) {
		comprobar_jaque(fin, jaque, tablero, fila + i, columna - i, alfil);
		if (jaque == true) {
			return jaque;
		}
	}
	fin = false;
	jaque = false;

	for (int i = 1; fila - i >= 0 && columna - i >= 0 && fin == false; i++) {
		comprobar_jaque(fin, jaque, tablero, fila - i, columna - i, alfil);
		if (jaque == true) {
			return jaque;
		}
	}
	fin = false;
	jaque = false;

	//Comprobación caballos
	casilla c_aux;
	ficha* f_aux;
		
		if (fila < 6 && columna < 7) {
			c_aux = tablero.leer_casilla(fila + 2, columna + 1);
			f_aux = c_aux.leer_ocupacion();
			if (f_aux) {
				if (f_aux->leer_tipo() != t_NO) {
					if (campo_color != f_aux->leer_color() && f_aux->leer_tipo() == caballo) {
						return true;
					}
					else {
						fin = true;
					}
				}
			}
		}
	fin = false;
	if (fila<6&&columna > 0) {
		c_aux = tablero.leer_casilla(fila + 2, columna - 1);
		f_aux = c_aux.leer_ocupacion();
		if (f_aux) {
			if (f_aux->leer_tipo() != t_NO) {
				if (campo_color != f_aux->leer_color() && f_aux->leer_tipo() == caballo) {
					return true;
				}
				else {
					fin = true;
				}
			}
		}
	}
	fin = false;
	if (fila > 1&&columna<7) {
		c_aux = tablero.leer_casilla(fila - 2, columna + 1);
		f_aux = c_aux.leer_ocupacion();
		if (f_aux) {
			if (f_aux->leer_tipo() != t_NO) {
				if (campo_color != f_aux->leer_color() && f_aux->leer_tipo() == caballo) {
					return true;
				}
				else {
					fin = true;
				}
			}
		}
		fin = false;
	}
	if (fila > 1 && columna > 0) {
		c_aux = tablero.leer_casilla(fila - 2, columna - 1);
		f_aux = c_aux.leer_ocupacion();
		if (f_aux) {
			if (f_aux->leer_tipo() != t_NO) {
				if (campo_color != f_aux->leer_color() && f_aux->leer_tipo() == caballo) {
					return true;
				}
				else {
					fin = true;
				}
			}
		}
		fin = false;
	}
	if (fila < 7 && columna < 6) {
		c_aux = tablero.leer_casilla(fila + 1, columna + 2);
		f_aux = c_aux.leer_ocupacion();
		if (f_aux) {
			if (f_aux->leer_tipo() != t_NO) {
				if (campo_color != f_aux->leer_color() && f_aux->leer_tipo() == caballo) {
					return true;
				}
				else {
					fin = true;
				}
			}
		}
	}
	fin = false;
	if (fila > 0 && columna < 6) {
		c_aux = tablero.leer_casilla(fila - 1, columna + 2);
		f_aux = c_aux.leer_ocupacion();
		if (f_aux) {
				if (campo_color != f_aux->leer_color() && f_aux->leer_tipo() == caballo) {
					return true;
				}
				else {
					fin = true;
				}
		}
	}
	fin = false;
	if (fila < 7 && columna > 1) {
		c_aux = tablero.leer_casilla(fila + 1, columna - 2);
		f_aux = c_aux.leer_ocupacion();
		if (f_aux) {
			if (f_aux->leer_tipo() != t_NO) {
				if (campo_color != f_aux->leer_color() && f_aux->leer_tipo() == caballo) {
					return true;
				}
				else {
					fin = true;
				}
			}
		}
	}
	fin = false;
	if (fila > 0 && columna > 1) {
		c_aux = tablero.leer_casilla(fila - 1, columna - 2);
		f_aux = c_aux.leer_ocupacion();
		if (f_aux) {
			if (f_aux->leer_tipo() != t_NO) {
				if (campo_color != f_aux->leer_color() && f_aux->leer_tipo() == caballo) {
					return true;
				}
				else {
					fin = true;
				}
			}
		}
	}
	fin = false;


	
	//Comprobacion peones
	if (this->campo_color == blanca) {
		c_aux = tablero.leer_casilla(fila + 1, columna +1);
		f_aux = c_aux.leer_ocupacion();
		
		if (f_aux) {
			if (f_aux->leer_tipo() != t_NO) {
			
				if (f_aux->leer_tipo() == peon && f_aux->leer_color() == negra)
					return true;
			}
		}
		c_aux = tablero.leer_casilla(fila - 1, columna + 1);
		f_aux = c_aux.leer_ocupacion();
		if (f_aux) {
			if (f_aux->leer_tipo() != t_NO) {
				if (f_aux->leer_tipo() == peon && f_aux->leer_color() == negra)
					return true;
				}
			}
	}
	if (this->campo_color == negra) {
		c_aux = tablero.leer_casilla(fila - 1, columna - 1);
		f_aux = c_aux.leer_ocupacion();
		if (f_aux) {
			if (f_aux->leer_tipo() == peon && f_aux->leer_color() == blanca)
				return true;
		}
		c_aux = tablero.leer_casilla(fila + 1, columna - 1);
		f_aux = c_aux.leer_ocupacion();
		if (f_aux) {
			if (f_aux->leer_tipo() == peon && f_aux->leer_color() == blanca)
				return true;
		}

	}
	

	return false;
}

bool Rey::en_jaque_mate(const casilla& c, const tablero& t) {

	if (this->en_jaque(c, t) == false) {
		return false;
	}


}