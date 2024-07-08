#include "gestor_movimientos.h"
#include <cmath>

colision gestor_movimientos::comprobar_ocupacion(ficha* p1, casilla cas) {

	if (cas.ocupacion) {
		if (cas.ocupacion->leer_tipo() == t_NO) {
			return colision::vacio;
		}
		else {
			if (p1->campo_color == cas.ocupacion->campo_color) {
				return colision::amigo;
			}
			else
				return colision::enemigo;
		}
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

	int signo_dif_f, signo_dif_c;

	casilla aux;
	
	
	if (dif_f == 0) {
		signo_dif_c = (dif_c / abs(dif_c));

		for (int i = signo_dif_c; abs(i) < abs(dif_c) && colision != true; i += signo_dif_c) {
			aux = T.leer_casilla(p1_f,i + p1_c);
			//auto a = aux.leer_ocupacion();
			colision = aux.leer_ocupacion();
		}
	}
	else if (dif_c == 0) {
		signo_dif_f = (dif_f / abs(dif_f));

		for (int i = signo_dif_f; abs(i) < abs(dif_f) && colision != true; i += signo_dif_f) {
			aux = T.leer_casilla(i + p1_f, p1_c);
			colision = aux.leer_ocupacion();
		}
	}
	else{
		signo_dif_f = (dif_f / abs(dif_f));
		signo_dif_c = (dif_c / abs(dif_c));

		for (int i = signo_dif_f; abs(i) < abs(dif_f) && colision != true; i = abs(dif_f)) {
			for (int j = signo_dif_c; abs(j) < abs(dif_f); j += signo_dif_c, i += signo_dif_f) {
				aux = T.leer_casilla(i + p1_f, j + p1_c);
				colision = aux.leer_ocupacion();
			}
		}
	}
	return colision;
}
