#include "gestor_movimientos.h"
#include <cmath>

colision gestor_movimientos::comprobar_ocupacion(ficha* p1, casilla cas) {


	if (cas.ocupacion->leer_tipo() == t_NO) {
		return colision::vacio;
	}
	else {
		if (p1->c == cas.ocupacion->c) {
			return colision::amigo;
		}
		else
			return colision::enemigo;
	}

	return colision::vacio;
}

void gestor_movimientos::cambiar_ocupación(ficha* p1, casilla* cas) {
	p1->posicion = nullptr;

	cas->ocupacion = p1;
	p1->posicion = cas;

}

bool gestor_movimientos::comprobar_colision(const ficha& p1, const casilla& cas, const tablero& T) {
	bool colision = false;
	int cas_f = cas.leer_fila(), cas_c = cas.leer_columna();
	int p1_f = p1.leer_posicion().leer_fila(), p1_c = p1.leer_posicion().leer_columna();
	int dif_f = cas_f - p1_f, dif_c = cas_c - p1_c;
	casilla aux;
	int j = p1_c;
	int i = p1_f;
	int suma_fila, suma_columna;
	if (dif_f < 0) { i--; suma_fila = -1;}
	if (dif_f > 0) { i++; suma_fila = 1;}
	if (dif_c < 0) { j--; suma_columna = -1;}
	if (dif_c > 0) { j++; suma_columna = 1; }

	if (dif_f == 0) {
		for ( i; i < abs(cas_c); i += suma_columna) {
			if (T.leer_casilla(i, j).ocupacion->c == p1.c)
				return true;
			if (i < cas_f && T.leer_casilla(i, j).ocupacion->c != p1.c && T.leer_casilla(i, j).ocupacion->c != color_NO) {
				return true;
			}
		}
	}
	else if (dif_c == 0) {
		for ( j ; j < abs(cas_f);j  += suma_fila ){
			if (T.leer_casilla(i, j).ocupacion->c == p1.c)
				return true;
			if (i < cas_f && T.leer_casilla(i, j).ocupacion->c != p1.c && T.leer_casilla(i, j).ocupacion->c != color_NO) {
				return true;
			}
			
		}
	}
	else {
		
		
		for (i; i <= cas_f; i+= suma_columna, j+= suma_fila) {
			if (T.leer_casilla(i, j).ocupacion->c == p1.c)
				return true;
			if (i < cas_f && T.leer_casilla(i, j).ocupacion->c != p1.c && T.leer_casilla(i, j).ocupacion->c != color_NO) {
				return true;
			}
			aux = T.leer_casilla(i, j);
			colision = aux.leer_ocupacion();
			
			/*for (int i = p1_f; i < abs(cas_f); i + (dif_f / abs(dif_f))) {
				for (int j = p1_c; j < abs(cas_c); j + (dif_c / abs(dif_c))) {
					aux = T.leer_casilla(i, j);
					colision = aux.leer_ocupacion();
				}
			}*/
		}
	}
	return false;
}
