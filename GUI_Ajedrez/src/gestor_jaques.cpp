#include "gestor_jaques.h"

bool gestor_jaques::Mod_estado(const tablero& T) {

	casilla Pos_rey_blanco= T.encontrar_rey(blanca)->leer_posicion();
	casilla Pos_rey_negro = T.encontrar_rey(negra)->leer_posicion();
	Rey Rey_Blanco=Rey(T.encontrar_rey(blanca)->leer_posicion(), T.encontrar_rey(blanca)->leer_color());
	Rey Rey_Negro= Rey(T.encontrar_rey(negra)->leer_posicion(), T.encontrar_rey(blanca)->leer_color());
	
	estado = estado_J::NORMAL;
	if (Rey_Blanco.en_jaque(Pos_rey_blanco, T)) {
		estado = estado_J::JAQUE_A_BLANCAS;

	}
	if (Rey_Negro.en_jaque(Pos_rey_negro, T)) {
		estado = estado_J::JAQUE_A_NEGRAS;

	}
	/*if (!comprobar_mov_posibles(T, ENUM_COLOR::blanca) || !comprobar_mov_posibles(T, ENUM_COLOR::negra)) {
		estado = estado_J::TABLAS;
	}*/
	switch (estado)
	{

	case estado_J::NORMAL:
		if (Rey_Blanco.en_jaque(Rey_Blanco.leer_posicion(), T)) {
			estado = estado_J::JAQUE_A_BLANCAS;

		}
		if (Rey_Negro.en_jaque(Rey_Negro.leer_posicion(), T)) {
			estado = estado_J::JAQUE_A_NEGRAS;

		}
		/*if (!comprobar_mov_posibles(T, ENUM_COLOR::blanca) || !comprobar_mov_posibles(T, ENUM_COLOR::negra)) {
			estado = estado_J::TABLAS;
		}*/
		return false;

	case estado_J::JAQUE_A_BLANCAS:
		if (!Rey_Blanco.en_jaque(Rey_Blanco.leer_posicion(), T)) {
			estado = estado_J::NORMAL;
			return false;
		}
		if (!comprobar_mov_posibles(T, ENUM_COLOR::blanca)) {
			estado = estado_J::MATE_A_BLANCAS;
			return true;
		}
		break;

	case estado_J::JAQUE_A_NEGRAS:
		if (!Rey_Blanco.en_jaque(Rey_Negro.leer_posicion(), T)) {
			estado = estado_J::NORMAL;
			return false;
		}
		if (!comprobar_mov_posibles(T, ENUM_COLOR::negra)) {
			estado = estado_J::MATE_A_NEGRAS;
			return true;
		}
		break;

	case estado_J::MATE_A_BLANCAS:
		//Por definir
		return true;
		break;

	case estado_J::MATE_A_NEGRAS:
		//Por definir
		return true;
		break;

	case estado_J::TABLAS:
		//Por definir
		break;
	}
}

bool gestor_jaques::comprobar_mov_posibles(const tablero& T, const ENUM_COLOR& color) {
	casilla c_aux;
	ficha f_aux;


	for (int i = 0; i < T.leer_filas(); i++) {
		for (int j = 0; j < T.leer_columnas(); j++) {
			if (c_aux.leer_ocupacion()) {
				f_aux = *c_aux.leer_ocupacion();
				if (f_aux.leer_color() == color) {
					if (f_aux.mover(c_aux, T) == true) {
						return true;
					}
				}
			}
		}
	}
	return false;
}