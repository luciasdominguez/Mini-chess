#include "gestor_jaques.h"

bool gestor_jaques::comprobar_mate(const tablero& T) {

	casilla Pos_rey_blanco= T.encontrar_rey(blanca)->leer_posicion();
	casilla Pos_rey_negro = T.encontrar_rey(negra)->leer_posicion();
	Rey Rey_Blanco=Rey(T.encontrar_rey(blanca)->leer_posicion(), T.encontrar_rey(blanca)->leer_color());
	Rey Rey_Negro= Rey(T.encontrar_rey(negra)->leer_posicion(), T.encontrar_rey(negra)->leer_color());
	
	//Pude ser interesante añadir las tablas
	if (Rey_Blanco.en_jaque(Pos_rey_blanco, T)) {
		//Comprobamos mate a las blancas
		if (!comprobar_mov_posibles(T, ENUM_COLOR::blanca)) {
			return true;
		}
	}
	if (Rey_Negro.en_jaque(Pos_rey_negro, T)) {
		//Comprobamo mate a las negras
		if (!comprobar_mov_posibles(T, ENUM_COLOR::negra)) {
			return true;
		}
	}
	return false;
}

//REVISAR Y AÑADIR GRAVEDAD
bool gestor_jaques::comprobar_mov_posibles(const tablero& T, const ENUM_COLOR& color) {
	casilla c_aux;
	ficha f_aux;


	for (int i = 0; i < T.leer_filas(); i++) {
		for (int j = 0; j < T.leer_columnas(); j++) {
			if (c_aux.leer_ocupacion()) {
				f_aux = *c_aux.leer_ocupacion();
				if (f_aux.leer_color() == color) {
					if (f_aux.mover(c_aux, T) == true) {
						//Creamos un tablero nuevo con gravedad para la nueva situación
						tablero tab_con_gravedad2 = T.simular_gravedad();
						Rey rey_aux = (*tab_con_gravedad2.encontrar_rey(color));
						if (!rey_aux.en_jaque(rey_aux.leer_posicion(),tab_con_gravedad2)) {
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}