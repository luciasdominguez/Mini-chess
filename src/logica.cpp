#include "logica.h"
#include "GUI_jugada.h"
#include "gestor_jaques.h"

Cl_logica::Cl_logica()
{
	//Tablero_actual_= {// vector de 2 dimesiones de 8x8
	//	{ pz_0,pz_0,pz_0,pz_0,pz_0,pz_0,pz_0,pz_0 },
	//	{ pz_0,pz_0,pz_0,pz_0,pz_0,pz_0,pz_0,pz_0 },
	//	{ pz_0,pz_0,pz_0,pz_0,pz_0,pz_0,pz_0,pz_0 },
	//	{ pz_0,pz_0,pz_0,pz_0,pz_0,pz_0,pz_0,pz_0 },
	//	{ pz_0,pz_0,pz_0,pz_0,pz_0,pz_0,pz_0,pz_0 },
	//	{ pz_0,pz_0,pz_0,pz_0,pz_0,pz_0,pz_0,pz_0 },
	//	{ pz_0,pz_0,pz_0,pz_0,pz_0,pz_0,pz_0,pz_0 },
	//	{ pz_0,pz_0,pz_0,pz_0,pz_0,pz_0,pz_0,pz_0 }
	//};
	//Tablero_temp = Tablero_actual_;
}


int Cl_logica::analiza_jugada(vector<vector<PIEZA_STRU>> _TableroGUI_actual, GUI_jugada& jugada_propia, GUI_jugada& jugada_gravedad, bool jugada_erronea)
{//0 ilegal, 1 valido, 2 jaque
	//temporal
	TableroGUI_actual = _TableroGUI_actual;
	bool jugada_valida;

	auto pieza_actual = jugada_propia.get_lista_piezas_movidas().front();
	auto pieza_antes = busca_posicion_anterior(pieza_actual);
	genera_tablero_temporal(); //en base al TableroGUI_actual

	casilla casilla_destino = tablero_temporal.casillas_tablero.at(pieza_actual.c_columna - 1).at(pieza_actual.c_fila - 1);
	casilla casilla_origen = tablero_temporal.casillas_tablero.at(pieza_antes.c_columna - 1).at(pieza_antes.c_fila - 1);

	jugada_valida = casilla_origen.ocupacion->mover(casilla_destino, tablero_temporal);
	
	//Comprobación de la legalidad de la jugada
	if (jugada_valida == false) {
		return 0;
	}

	//Comprobación de las consecuencias tras la gravedad
	
	tablero tablero_aux = tablero_temporal;

	tablero_aux.casillas_tablero[pieza_actual.c_columna - 1][pieza_actual.c_fila - 1].ocupacion = tablero_temporal.casillas_tablero[pieza_antes.c_columna - 1][pieza_antes.c_fila - 1].ocupacion;
	tablero_aux.casillas_tablero[pieza_antes.c_columna - 1][pieza_antes.c_fila - 1].ocupacion = nullptr;

	tablero tablero_con_gravedad_simulada = tablero_aux.simular_gravedad();
	Rey rey_aux = tablero_con_gravedad_simulada.encontrar_rey(pieza_actual.c_color);
	if (rey_aux.en_jaque(rey_aux.leer_posicion(), tablero_con_gravedad_simulada)) {
		tablero_aux.casillas_tablero[pieza_antes.c_columna - 1][pieza_antes.c_fila - 1].ocupacion = tablero_aux.casillas_tablero[pieza_actual.c_columna - 1][pieza_actual.c_fila - 1].ocupacion;
		tablero_aux.casillas_tablero[pieza_actual.c_columna - 1][pieza_actual.c_fila - 1].ocupacion = nullptr;
		return 0;
	}

	tablero_aux.casillas_tablero[pieza_antes.c_columna - 1][pieza_antes.c_fila - 1].ocupacion = tablero_aux.casillas_tablero[pieza_actual.c_columna - 1][pieza_actual.c_fila - 1].ocupacion;
	tablero_aux.casillas_tablero[pieza_actual.c_columna - 1][pieza_actual.c_fila - 1].ocupacion = nullptr;

	//Ejecutamos el movimiento
	if (casilla_destino.ocupacion != nullptr) // en el destino habia pieza del contrario y se añade como situada en el almacen 
											// poniendola en la lista de piezas movidas
	{
		auto _color = casilla_destino.ocupacion->leer_color();
		auto _pieza = casilla_destino.ocupacion->leer_pieza();
		auto _tipo = casilla_destino.ocupacion->leer_tipo();

		PIEZA_STRU pieza_aux;
		pieza_aux.c_color = _color;
		pieza_aux.c_pieza = _pieza;
		pieza_aux.c_tipo = _tipo;
		pieza_aux.c_fila = f_ND;
		pieza_aux.c_columna = C_ND;
		jugada_propia.add_pieza_a_jugada(pieza_aux);
	}

	vector<vector<PIEZA_STRU>> Tablero_gravedad = _TableroGUI_actual;
	GUI_partida partida_act; 
	
	//Tablero_gravedad.at(pieza_actual.c_fila - 1).at(pieza_actual.c_columna - 1) = pieza_actual;
	//Tablero_gravedad.at(pieza_antes.c_fila - 1).at(pieza_antes.c_columna - 1).c_color = color_NO;
	//Tablero_gravedad.at(pieza_antes.c_fila - 1).at(pieza_antes.c_columna - 1).c_pieza = PZ_NO;
	//Tablero_gravedad.at(pieza_antes.c_fila - 1).at(pieza_antes.c_columna - 1).c_tipo = t_NO;
	//jugada_gravedad_GUI(Tablero_gravedad,_TableroGUI_actual,jugada_gravedad);
	analiza_gravedad(Tablero_gravedad, jugada_propia, jugada_gravedad);

	// Debe ir despues de analizar el efecto de la gravedad

	//JAQUES
	Rey Rey_Blanco = tablero_con_gravedad_simulada.encontrar_rey(blanca);
	Rey Rey_Negro = tablero_con_gravedad_simulada.encontrar_rey(negra);

	if (Rey_Blanco.en_jaque(Rey_Blanco.leer_posicion(), tablero_con_gravedad_simulada)) {
			return 2;
	}
	if (Rey_Negro.en_jaque(Rey_Negro.leer_posicion(), tablero_con_gravedad_simulada)) {
		//Comprobamo mate a las negras
			return 2;
	}

	//MATE
	if (gestor_jaques::comprobar_mate(tablero_con_gravedad_simulada)) {
		return 3;
	}

	return 1;
}

int Cl_logica::analiza_jugada___(vector<vector<PIEZA_STRU>> Tablero, GUI_jugada& jugada_propia, GUI_jugada& jugada_gravedad, bool jugada_erronea)
{
	return 1;
}

PIEZA_STRU Cl_logica::busca_posicion_anterior(PIEZA_STRU pieza_jugada) { //se devuelve la pieza en la posición anterior del tablero

	//// se busca la pieza en el tablero (según estaba antes de modificar el tablero)
	for (int ff = 0; ff < 8; ff++) {
		for (int cc = 0; cc < 8; cc++) {
			auto pp = TableroGUI_actual.at(ff).at(cc);
			if (pp.c_pieza == pieza_jugada.c_pieza && pp.c_color == pieza_jugada.c_color) {
				//localizada la pieza en el tablero
				return pp;
			}
		}
	}// FIN de buscar la posición origen
	return pz_0; // si no se ha encontrado se devuelve pz_0
}

//ESTA PROVOCA DOBLE MOVIMIENTO EN LOS PEONES, NECESITAMOS QUE CUANDO SE VUELVAN A GENERAR ha_movido = true (despues de haber sido movidos)
void Cl_logica::genera_tablero_temporal() {
	
	// se genera el tablero tempora en base al "tableroGUI_actual"
	for (int i = 0; i < tablero_temporal.n_columnas; i++) {
		for (int j = 0; j < tablero_temporal.n_filas; j++) {
			casilla casi = casilla(i, j);
			casilla* cas = &casi;
			const ficha f = ficha(cas, TableroGUI_actual.at(j).at(i).c_color);
			//peon
			

			auto tipo = TableroGUI_actual.at(j).at(i).c_tipo;
			tablero_temporal.casillas_tablero.at(i).at(j).columna = i + 1;//tablero_GUI.at(j).at(i).c_columna;
			tablero_temporal.casillas_tablero.at(i).at(j).fila = j + 1;// tablero_GUI.at(j).at(i).c_fila;
			ficha* ptemp = nullptr;

			switch (tipo) {
			case peon:
				ptemp = new Peon(tablero_temporal.casillas_tablero.at(i).at(j), TableroGUI_actual.at(j).at(i).c_color);
				if (TableroGUI_actual.at(j).at(i).c_color == blanca && j != 1) {
					ptemp->mod_ha_movido();
				}
				if (TableroGUI_actual.at(j).at(i).c_color == negra && j != 6) {
					ptemp->mod_ha_movido();
				}
				break;

			case torre:
				 ptemp = new Torre(tablero_temporal.casillas_tablero.at(i).at(j), TableroGUI_actual.at(j).at(i).c_color);
				break;

			case alfil:
				ptemp = new Alfil(tablero_temporal.casillas_tablero.at(i).at(j), TableroGUI_actual.at(j).at(i).c_color);
				break;

			case caballo:
				ptemp = new Caballo(tablero_temporal.casillas_tablero.at(i).at(j), TableroGUI_actual.at(j).at(i).c_color);
				break;

			case reina:
				ptemp = new Reina(tablero_temporal.casillas_tablero.at(i).at(j), TableroGUI_actual.at(j).at(i).c_color);
				break;

			case rey:
				ptemp = new Rey(tablero_temporal.casillas_tablero.at(i).at(j), TableroGUI_actual.at(j).at(i).c_color);
				break;
			}
			tablero_temporal.casillas_tablero.at(i).at(j).ocupacion = ptemp;
			tablero_temporal.casillas_tablero.at(i).at(j).ocupacion->set_casilla(&tablero_temporal.casillas_tablero.at(i).at(j));
			tablero_temporal.casillas_tablero.at(i).at(j).columna = (j);
			tablero_temporal.casillas_tablero.at(i).at(j).fila = (i);
			auto c_pieza = TableroGUI_actual.at(j).at(i).c_pieza;

			tablero_temporal.casillas_tablero.at(i).at(j).ocupacion->set_pieza(c_pieza);

		}
	}
	int tt;
	
}

// Recorre el tablero e identifica qué fichas tienen libre un hueco debajo pero no las mueve ni indica cuántas posiciones
// se debe mover la ficha para llegar a la posición deseada

// void Cl_logica::jugada_gravedad_GUI(vector<vector<PIEZA_STRU>> Tablero_aux_gravedad, vector<vector<PIEZA_STRU>> Tablero_actual_, GUI_jugada& jugada_gravedad) {
//
//	for (int j = 0; j < 8; j++) {
//		for (int i = 1; i <8; i++) {
//			int posicion = i;
//			while (posicion > 0 && Tablero_aux_gravedad.at(j).at(posicion-1).c_pieza == PZ_NO ) {
//				posicion--;;
//			}
//			if (Tablero_aux_gravedad.at(j).at(posicion).c_pieza == PZ_NO && Tablero_aux_gravedad.at(j).at(i).c_tipo!=PZ_NO) {
//				Tablero_aux_gravedad.at(j).at(posicion).c_pieza = Tablero_aux_gravedad.at(j).at(i).c_pieza;
//				Tablero_aux_gravedad.at(j).at(posicion).c_color = Tablero_aux_gravedad.at(j).at(i).c_color;
//				Tablero_aux_gravedad.at(j).at(posicion).c_columna = Tablero_aux_gravedad.at(j).at(i).c_columna;
//				Tablero_aux_gravedad.at(j).at(posicion).c_fila = Tablero_aux_gravedad.at(j).at(i).c_fila;
//				Tablero_aux_gravedad.at(j).at(posicion).c_tipo = Tablero_aux_gravedad.at(j).at(i).c_tipo;
//				Tablero_aux_gravedad.at(j).at(i).c_pieza = PZ_NO;
//				Tablero_aux_gravedad.at(j).at(i).c_color = color_NO;
//				Tablero_aux_gravedad.at(j).at(i).c_columna = C_ND;
//				Tablero_aux_gravedad.at(j).at(i).c_fila = f_ND;
//				Tablero_aux_gravedad.at(j).at(i).c_tipo = t_NO;
//			}
//		}
//	}
//
//	for (int i = 0; i < tablero_temporal.leer_columnas(); i++) {
//		for (int j = 0; j < tablero_temporal.leer_filas(); j++) {
//			if (Tablero_aux_gravedad.at(i).at(j).c_pieza != Tablero_actual_.at(i).at(j).c_pieza && Tablero_aux_gravedad.at(i).at(j).c_pieza != PZ_NO) {
//				jugada_gravedad.lista_PiezasMovidas.push_back(Tablero_aux_gravedad.at(i).at(j));
//			}
//		}
//	}
//}

void Cl_logica::analiza_gravedad(vector<vector<PIEZA_STRU>> Tablero, GUI_jugada& jugada_propia, GUI_jugada& jugada_gravedad) {

	TableroGUI_actual = Tablero;

	auto pieza_movida = jugada_propia.get_lista_piezas_movidas().at(0);
	auto pieza_origen = busca_posicion_anterior(pieza_movida);


	auto fila_origen = pieza_origen.c_fila;
	auto columna_origen = pieza_origen.c_columna;
	auto fila_destino = pieza_movida.c_fila;
	auto columna_destino = pieza_movida.c_columna;

	jugada_gravedad.vaciar_jugada();
	//efecto sobre la casilla de origen de la jugada
	for (int idx_c = ((int)columna_origen);idx_c < 8;idx_c++)
	{
		auto aux_pz = TableroGUI_actual.at((int)fila_origen - 1).at(idx_c);
		if (aux_pz.c_color != color_NO)  // la pieza que hay encima pasa a la lista de piezas movidas por la gravedad
		{
			auto pz_superior = TableroGUI_actual.at((int)fila_origen - 1).at(idx_c);
			pz_superior.c_columna = (ENUM_COLUMNA)(pz_superior.c_columna - 1);
			jugada_gravedad.add_pieza_a_jugada(pz_superior);
		}
	}

	//efecto sobre la casilla destino de la jugada
	int cuenta_vacias = 0;
	for (int idx_c = ((int)columna_destino) - 1;idx_c >= 1;idx_c--)
	{
		auto aux_pz = TableroGUI_actual.at((int)fila_destino - 1).at(idx_c-1);
		if (aux_pz.c_color == color_NO)
			cuenta_vacias++;
	}
	if ((fila_destino == fila_origen) && ((int)columna_destino>(int)columna_origen)) 
		cuenta_vacias++;
	pieza_movida.c_columna = (ENUM_COLUMNA)(pieza_movida.c_columna - cuenta_vacias);

	jugada_gravedad.add_pieza_a_jugada(pieza_movida);

}