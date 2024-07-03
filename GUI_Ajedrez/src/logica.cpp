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
	//auto pieza_actual = jugada_propia.lista_PiezasMovidas.at(jugada_propia.lista_PiezasMovidas.size());
	//jugada_propia.get_lista_piezas_movidas().back();
	auto pieza_antes = busca_posicion_anterior(pieza_actual);
	genera_tablero_temporal(); //en base al TableroGUI_actual
	//pruebas
	//p->set_casilla(&tablero_temporal.casillas_tablero.at(6).at(5));
	//p->mover(tab_aux.tab.at(pieza_actual.c_columna).at(pieza_actual.c_columna), tab_aux);
	//t->mover(tab_aux.tab.at(pieza_actual.c_columna).at(pieza_actual.c_columna), tab_aux);

	casilla casilla_destino = tablero_temporal.casillas_tablero.at(pieza_actual.c_columna - 1).at(pieza_actual.c_fila - 1);
	casilla casilla_origen = tablero_temporal.casillas_tablero.at(pieza_antes.c_columna - 1).at(pieza_antes.c_fila - 1);

	


	jugada_valida = casilla_origen.ocupacion->mover(casilla_destino, tablero_temporal);
	
	if (jugada_valida == false) {
		return 0;
	}

	if (casilla_destino.ocupacion != nullptr) // en el destino habia pieza del contrario y se añade como situada en el almacen 
											// poniendola en la lista de piezas movidas
	{
		auto _color = casilla_destino.ocupacion->leer_color();
		auto _pieza = casilla_destino.ocupacion->leer_pieza();
		auto _tipo = casilla_destino.ocupacion->leer_tipo();
		//auto _fila = casilla_destino.ocupacion->leer_posicion().leer_fila()+1;
		//auto _columna = casilla_destino.ocupacion->leer_posicion().leer_columna()+1;

		PIEZA_STRU pieza_aux;
		pieza_aux.c_color = _color;
		pieza_aux.c_pieza = _pieza;
		pieza_aux.c_tipo = _tipo;
		pieza_aux.c_fila = f_ND;
		pieza_aux.c_columna = C_ND;
		jugada_propia.add_pieza_a_jugada(pieza_aux);
	}



	

	// Debe ir despues de analizar el efecto de la gravedad
	gestor_jaques g;
	if (g.Mod_estado(tablero_temporal)) {
		return 2;
	}
	/////////////////////

	vector<vector<PIEZA_STRU>> Tablero_gravedad = _TableroGUI_actual;
	GUI_partida partida_act; 
	
	Tablero_gravedad.at(pieza_actual.c_fila - 1).at(pieza_actual.c_columna - 1) = pieza_actual;
	Tablero_gravedad.at(pieza_antes.c_fila - 1).at(pieza_antes.c_columna - 1).c_color = color_NO;
	Tablero_gravedad.at(pieza_antes.c_fila - 1).at(pieza_antes.c_columna - 1).c_pieza = PZ_NO;
	Tablero_gravedad.at(pieza_antes.c_fila - 1).at(pieza_antes.c_columna - 1).c_tipo = t_NO;
	jugada_gravedad_GUI(Tablero_gravedad,_TableroGUI_actual,jugada_gravedad);
	return 1;

	//int r = analiza_jugada___(Tablero_actual_, jugada_propia, jugada_gravedad, jugada_erronea);
	//return r;


	//// Se analiza si la "jugada_propia" es correcta en base a lo que contiene "Tablero_actual_" . Si no fuese correcta se devuelve 0

	//auto t1 = Tablero_actual_;

	////.......................................
	////..............................

	////int control_test=partida_in.get_jugadas().size();
	//int control_test = (rand() % 3) + 1;  // 

	///// control del test
	//if (jugada_erronea)
	//	return 0;  // el parametro para testear jugada_erronea


	//// ..........................



	////TEST "jugada_propia"
	//jugada_propia = jugada_propia; // la jugada no tiene más piezas implicadas


	////TEST "jugada_gravedad"
	//jugada_gravedad.vaciar_jugada();
	//switch (control_test) {
	//case 1:
	//	pz.c_color = negra; pz.c_tipo = caballo; pz.c_pieza = PZ_caballo_rey; pz.c_columna = B; pz.c_fila = f6;
	//	jugada_gravedad.add_pieza_a_jugada(pz);
	//	pz.c_color = blanca; pz.c_tipo = alfil; pz.c_pieza = PZ_alfil_rey; pz.c_columna = G; pz.c_fila = f4;
	//	jugada_gravedad.add_pieza_a_jugada(pz);
	//	break;
	//case 2:
	//	pz.c_color = negra; pz.c_tipo = alfil; pz.c_pieza = PZ_alfil_rey; pz.c_columna = C; pz.c_fila = f6;
	//	jugada_gravedad.add_pieza_a_jugada(pz);
	//	pz.c_color = negra; pz.c_tipo = torre; pz.c_pieza = PZ_torre_rey; pz.c_columna = C; pz.c_fila = f_ND;
	//	jugada_gravedad.add_pieza_a_jugada(pz);
	//	break;
	//case 3:
	//	pz.c_color = negra; pz.c_tipo = reina; pz.c_pieza = PZ_reina; pz.c_columna = H; pz.c_fila = f5;
	//	jugada_gravedad.jaque_mate = false;
	//	jugada_gravedad.add_pieza_a_jugada(pz);
	//	break;

	//default:
	//	jugada_gravedad.jaque_mate = true;
	//	return 2;
	//}

	////FIN TEST "jugada_gravedad"
	////return 2;
	//return 1;

}

int Cl_logica::analiza_jugada___(vector<vector<PIEZA_STRU>> Tablero, GUI_jugada& jugada_propia, GUI_jugada& jugada_gravedad, bool jugada_erronea)
{
	/*
	tablero tab;
	bool jugada_valida;
	auto pieza_actual =jugada_propia.lista_PiezasMovidas.at(jugada_propia.lista_PiezasMovidas.size());
	auto pieza_antes = busca_posicion_anterior(pieza_actual);
	tab = tab_auxiliar(Tablero);
	jugada_valida=tab.matriz[pieza_antes.c_columna][pieza_antes.c_fila].ocupacion->mover(tab.matriz[pieza_actual.c_columna][pieza_actual.c_fila], tab);
	*/
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
			//tab_aux.matriz[i][j].columna = tablero_GUI.at(i).at(j).c_columna;
			//tab_aux.matriz[i][j].fila = tablero_GUI.at(i).at(j).c_fila;
			ficha* ptemp = nullptr;

			switch (tipo) {
			case peon:
				//tab_aux.matriz[i][j].ocupacion = &p;
				ptemp = new Peon(tablero_temporal.casillas_tablero.at(i).at(j), TableroGUI_actual.at(j).at(i).c_color);

				//tab_aux.tab.at(i).at(j).ocupacion.set_tipo(peon_);
				break;
			case torre:
				//tab_aux.matriz[i][j].ocupacion = &t;
				 ptemp = new Torre(tablero_temporal.casillas_tablero.at(i).at(j), TableroGUI_actual.at(j).at(i).c_color);
				
				break;
			case alfil:
				ptemp = new Alfil(tablero_temporal.casillas_tablero.at(i).at(j), TableroGUI_actual.at(j).at(i).c_color);

				//tab_aux.matriz[i][j].ocupacion = &a;
				break;
			case caballo:
				
				ptemp = new Caballo(tablero_temporal.casillas_tablero.at(i).at(j), TableroGUI_actual.at(j).at(i).c_color);

				//tab_aux.matriz[i][j].ocupacion = &c;
				break;
			case reina:
				//tab_aux.matriz[i][j].ocupacion = &r;
				ptemp = new Reina(tablero_temporal.casillas_tablero.at(i).at(j), TableroGUI_actual.at(j).at(i).c_color);

				break;
			case rey:
				ptemp = new Rey(tablero_temporal.casillas_tablero.at(i).at(j), TableroGUI_actual.at(j).at(i).c_color);

				//tab_aux.matriz[i][j].ocupacion = &rey_;
				break;
			/*default:
				ptemp = new Vacia(tab_aux.tab.at(i).at(j), tablero_GUI.at(j).at(i).c_color);

				ptemp->set_tipo(t_NO);*/
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

void Cl_logica::jugada_gravedad_GUI(vector<vector<PIEZA_STRU>> Tablero_aux, vector<vector<PIEZA_STRU>> Tablero_actual_, GUI_jugada& jugada_gravedad) {

	for (int j = 0; j < 8; j++) {
		for (int i = 1; i <8; i++) {
			int posicion = i;
			while (posicion > 0 && Tablero_aux.at(j).at(posicion-1).c_pieza == PZ_NO ) {
				posicion--;;
			}
			if (Tablero_aux.at(j).at(posicion).c_pieza == PZ_NO && Tablero_aux.at(j).at(i).c_tipo!=PZ_NO) {
				Tablero_aux.at(j).at(posicion).c_pieza = Tablero_aux.at(j).at(i).c_pieza;
				Tablero_aux.at(j).at(posicion).c_color = Tablero_aux.at(j).at(i).c_color;
				Tablero_aux.at(j).at(posicion).c_columna = Tablero_aux.at(j).at(i).c_columna;
				Tablero_aux.at(j).at(posicion).c_fila = Tablero_aux.at(j).at(i).c_fila;
				Tablero_aux.at(j).at(posicion).c_tipo = Tablero_aux.at(j).at(i).c_tipo;
				Tablero_aux.at(j).at(i).c_pieza = PZ_NO;
				Tablero_aux.at(j).at(i).c_color = color_NO;
				Tablero_aux.at(j).at(i).c_columna = C_ND;
				Tablero_aux.at(j).at(i).c_fila = f_ND;
				Tablero_aux.at(j).at(i).c_tipo = t_NO;
			}
		}
	}

	for (int i = 0; i < tablero_temporal.leer_columnas(); i++) {
		for (int j = 0; j < tablero_temporal.leer_filas(); j++) {
			if (Tablero_aux.at(i).at(j).c_pieza != Tablero_actual_.at(i).at(j).c_pieza && Tablero_aux.at(i).at(j).c_pieza != PZ_NO) {
				jugada_gravedad.lista_PiezasMovidas.push_back(Tablero_aux.at(i).at(j));
			}
		}
	}

}