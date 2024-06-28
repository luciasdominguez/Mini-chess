#include "gestor_movimientos.h"
#include <cmath>

colision gestor_movimientos::comprobar_ocupacion(ficha* p1, casilla cas) {


	if (cas.comprobar_ocupacion() == nullptr) {
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

bool gestor_movimientos:: comprobar_colision(const ficha& p1, const casilla& cas, const tablero& T) {
	bool colision = false;
	int cas_f = cas.leer_fila(), cas_c = cas.leer_columna();
	int p1_f = p1.leer_posicion().leer_fila(), p1_c = p1.leer_posicion().leer_columna();
	int dif_f = cas_f - p1_f, dif_c = cas_c - p1_c;
	casilla aux;

	if (dif_f == 0) {
		for (int i = p1_c; i < abs(cas_c); i + (dif_c / abs(dif_c))) {
			aux = T.leer_casilla(p1_f, i);
			colision = aux.leer_ocupacion();
		}
	}
	else if (dif_c == 0) {
		for (int i = p1_f; i < abs(cas_f); i + (dif_f / abs(dif_f))) {
			aux = T.leer_casilla(i, p1_c);
			colision = aux.leer_ocupacion();
		}
	}
	else {
		for (int i = p1_f; i < abs(cas_f); i + (dif_f / abs(dif_f))) {
			for (int j = p1_c; j < abs(cas_c); j + (dif_c / abs(dif_c))) {
				aux = T.leer_casilla(i, j);
				colision = aux.leer_ocupacion();
			}
		}
	}
	return colision;
}
