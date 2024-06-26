#include "gestor_jaques.h"

void gestor_jaques::Mod_estado(const tablero& T) {

	rey Rey_Blanco(*(T.encontrar_rey(color::blanca)));
	rey Rey_Negro(*(T.encontrar_rey(color::negra)));

	switch (estado)
	{

	case estado_J::NORMAL:
		if (Rey_Blanco.en_jaque(Rey_Blanco.leer_posicion(), T)) {
			estado = estado_J::JAQUE_A_BLANCAS;

		}
		if (Rey_Negro.en_jaque(Rey_Negro.leer_posicion(), T)) {
			estado = estado_J::JAQUE_A_NEGRAS;

		}
		if (!comprobar_mov_posibles(T, color::blanca) || !comprobar_mov_posibles(T, color::negra)) {
			estado = estado_J::TABLAS;
		}

	case estado_J::JAQUE_A_BLANCAS:
		if (!Rey_Blanco.en_jaque(Rey_Blanco.leer_posicion(), T)) {
			estado = estado_J::NORMAL;
		}
		if (!comprobar_mov_posibles(T, color::blanca)) {
			estado = estado_J::MATE_A_BLANCAS;
		}
		break;

	case estado_J::JAQUE_A_NEGRAS:
		if (!Rey_Blanco.en_jaque(Rey_Negro.leer_posicion(), T)) {
			estado = estado_J::NORMAL;
		}
		if (!comprobar_mov_posibles(T, color::negra)) {
			estado = estado_J::MATE_A_NEGRAS;
		}
		break;

	case estado_J::MATE_A_BLANCAS:
		//Por definir
		break;

	case estado_J::MATE_A_NEGRAS:
		//Por definir
		break;

	case estado_J::TABLAS:
		//Por definir
		break;
	}
}

bool comprobar_mov_posibles(const tablero& T, const color& color) {
	casilla c_aux;
	ficha f_aux;

	for (int i = 0; i < T.leer_filas(); i++) {
		for (int j = 0; j < T.leer_columnas(); j++) {
			if (c_aux.leer_ocupacion()) {
				f_aux = *c_aux.leer_ocupacion();
				if (f_aux.leer_color() == color) {
					if (f_aux.mover(c_aux,T)) {
						return true;
					}
				}
			}
		}
	}
	return false;
}