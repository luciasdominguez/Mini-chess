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
	casilla c_aux, c_mov;
	ficha* f_aux;
	tablero T_aux = T;

	for (int i = 0; i < T.leer_filas(); i++) {
		for (int j = 0; j < T.leer_columnas(); j++) {
			c_aux = T.leer_casilla(i, j);
			if (c_aux.leer_ocupacion()) {
				f_aux = c_aux.leer_ocupacion();
				if (f_aux->leer_color() == color) {
					for (int m = 0; m < T.leer_filas(); m++) {
						for (int n = 0; n < T.leer_columnas(); n++) {
							c_mov = T.leer_casilla(m, n); //Se podría enfocar de forma más rapida si no comprobasemos movimientos que ya sabemos son ilegales
							if (f_aux->mover(c_mov, T) == true) {
								//Simulamos el movimiento
								T_aux.cambiar_casilla(c_mov,f_aux);
								T_aux.cambiar_casilla(c_aux,nullptr);
								//Creamos un tablero nuevo con gravedad para la nueva situación
								tablero tab_con_gravedad2 = T_aux.simular_gravedad();
								Rey rey_aux = (tab_con_gravedad2.encontrar_rey(color));
								if (!rey_aux.en_jaque(rey_aux.leer_posicion(), tab_con_gravedad2)) {
									return true;
								}
								//Deshacemos nuestro movimiento para no cmbiar las codiciones iniciales la siguiente iteración
								T_aux.cambiar_casilla(c_aux, f_aux);
								T_aux.cambiar_casilla(c_mov, nullptr);
							}
						}
					}
				}
			}
		}
	}
	return false;
}