#include "gestor_movimientos.h"

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

