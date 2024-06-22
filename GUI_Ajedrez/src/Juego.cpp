#include "Juego.h"
//#include "GUI_Pieza2.h"

Juego::Juego()
{
	generar_listado_datos_piezas_OFF();
	generar_piezas();

	//turno_ = BLANCAS;
	casilla_cursor = new GUI_marcador_cursor(f5, E);
	turno = new GUI_turno;
	gestor_de_partidas = new GUI_gestor_partidas;
	estado_Partidas_Jugadas = new GUI_estado_P_J;
	//casilla_lckd = new GUI_marcador_locked(f_ND, C_ND);
	casilla_lckd = new GUI_marcador_locked(f6, C);
	jugada_ultima.jugador = BLANCAS;  /// quien empieza
	//casilla_destino = new GUI_casilla(OFF, f6, D);
}

void Juego::carga_partida_al_GUI(int destino)
{
	//generar_partida();  // los movimientos de la partida se recogen con esta función
	generar_listado_datos_piezas_OFF(); // se ponen todas las piezas en almacen
	vector<GUI_jugada> lista_jugadas = partida_actual.get_jugadas();
	int size_partida = lista_jugadas.size();

	// para un numero negativo o cero se asume que se cogen todos los movimientos
	if (destino <= 0) destino = size_partida; // para valores menores que cero se carga toda la partida
	if (destino > size_partida) destino = size_partida;
	for (auto it_in = lista_jugadas.begin(); it_in != (lista_jugadas.begin() + destino); ++it_in)
	{
		vector<PIEZA_STRU> Lista_Pz_Mov = (*it_in).get_lista_piezas_movidas();
		for (auto it_in_2 = Lista_Pz_Mov.begin(); it_in_2 != (Lista_Pz_Mov.end()); ++it_in_2)
		{
			listado_datos_piezas___un_movimiento(*it_in_2);
		}
		//turno.dibuja_turno(Movimiento_ahora.jugador);
	};

}

GUI_partida Juego::get_partida_actual()
{
	return partida_actual;
}

void Juego::guarda_partida_actual()
{
	gestor_de_partidas->insert_update_partida(partida_actual.get_nombre(), partida_actual.get_jugadas());
}

void Juego::dibuja_juego()
{
	miTablero.dibuja_tablero();
	turno->dibuja_turno(jugada_ahora.jugador);
	estado_Partidas_Jugadas->dibuja_seleccion_partida();
	actualizar_piezas();
	dibujar_piezas();
	casilla_cursor->dibuja_sprite();
	casilla_lckd->dibuja_sprite();
	listado_partidas.set_nombres_partidas(gestor_de_partidas->get_nombres_partidas());
	listado_partidas.imprime_nombres();
}


ENUM_JUGADOR Juego::get_jugador_actual()
{
	return jugada_ahora.jugador;
}

void Juego::cargar_partida(string nombre)
{  /// si el nombre no se encuentra se genera una partida con ese nombre
	partida_actual = gestor_de_partidas->get_or_new_partida(nombre);


	jugada_ultima = partida_actual.get_jugadas()[partida_actual.get_jugadas().size() - 1];

	//el ultimo movimiento de la partida
	switch (jugada_ultima.jugador)
	{
	case BLANCAS: 		jugada_ahora.jugador = GRAVEDAD_B;	break;
	case GRAVEDAD_B: 	jugada_ahora.jugador = NEGRAS;		break;
	case NEGRAS:		jugada_ahora.jugador = GRAVEDAD_N;	break;
	case GRAVEDAD_N:	jugada_ahora.jugador = BLANCAS;		break;
	default:			jugada_ahora.jugador = GRAVEDAD_N;	break;
	};
	avanza_siguiente_turno();
}

void Juego::cargar_partida_ejemplo()
{
	partida_actual = gestor_de_partidas->get_partida_ejemplo();
	jugada_ultima = partida_actual.get_jugadas()[partida_actual.get_jugadas().size() - 1]; //el ultimo movimiento de la partida
	switch (jugada_ultima.jugador)
	{
	case BLANCAS: 		jugada_ahora.jugador = GRAVEDAD_B;	break;
	case GRAVEDAD_B: 	jugada_ahora.jugador = NEGRAS;		break;
	case NEGRAS:		jugada_ahora.jugador = GRAVEDAD_N;	break;
	case GRAVEDAD_N:	jugada_ahora.jugador = BLANCAS;		break;
	default:			jugada_ahora.jugador = GRAVEDAD_N;	break;
	};
	avanza_siguiente_turno();
}

GUI_partida Juego::get_partida()
{
	return partida_actual;
}

void Juego::check_pieza_movible()
{  // verifica si la casilla del cursor tiene una pieza movible
	//Si es así, se almacena que pieza tiene y la casilla podra ser Locked

	if (casilla_lckd != nullptr)
	{
		if (casilla_lckd->get_estado_locked() == ROJO)
		{ // ya hay una casilla locked (EN ROJO). Nada que hacer
		}
		else
		{
			for (auto it_in = todas_piezas_GUI.begin(); it_in != todas_piezas_GUI.end(); ++it_in)
			{
				if ((*it_in)._datos_pieza.c_fila == casilla_cursor->fila &&
					(*it_in)._datos_pieza.c_columna == casilla_cursor->columna)
				{
					if (casilla_lckd->get_estado() == ROJO) { // ya hay una casilla locked (EN ROJO)
						break;
					}
					else if // no hay casilla EN ROJO, pero estamos en una casilla elegible
						(((*it_in)._datos_pieza.c_color == blanca && jugada_ahora.jugador == BLANCAS) ||
							(*it_in)._datos_pieza.c_color == negra && jugada_ahora.jugador == NEGRAS)
					{   // se ha encontrado una pieza en la posción de la casilla y del color del turno
						casilla_lckd->set_Can_Lock(false);
						auto position = it_in - todas_piezas_GUI.begin();
						cual_pieza_locked = &todas_piezas_GUI.at(position);  // La pieza en cuestion que se ha encontrado y es movible
						casilla_lckd->set_posicion(casilla_cursor->fila, casilla_cursor->columna);
						casilla_lckd->set_Can_Lock(true); // se puede hacer Lock a la casilla
						casilla_lckd->set_estado_locked(NARANJA, cual_pieza_locked);
					}
					else // no se ha encontrado y NO habia pieza locked
						casilla_lckd->set_estado_locked(TRANS, nullptr);
					break; // Si encuentro la casilla con una pieza salgo
				}
				else {
					// 
					casilla_lckd->set_Can_Lock(false);
					casilla_lckd->set_estado_locked(TRANS, nullptr);
				}
			}
		}
	}
}

GUI_marcador_cursor* Juego::get_casilla_cursor()
{
	return casilla_cursor;
}

void Juego::reset_pieza_locked()
{
	cual_pieza_locked = nullptr;
}

ESTADO_GENERAL Juego::get_selector_partidas_jugadas()
{
	return estado_Partidas_Jugadas->get_partidas_o_jugadas();
}

void Juego::cambia_selector_partidas_jugadas()
{
	auto s = estado_Partidas_Jugadas->get_partidas_o_jugadas();
	if (s == en_seleccion_partida)
		estado_Partidas_Jugadas->set_partidas_o_jugadas(en_jugadas);
	else
		estado_Partidas_Jugadas->set_partidas_o_jugadas(en_seleccion_partida);

}

T_listado_partidas Juego::get_listado_partidas()
{
	return listado_partidas;
}

GUI_gestor_partidas Juego::get_almacen_partidas()
{
	return (*gestor_de_partidas);
}

void Juego::avanza_siguiente_turno()
{
	switch (jugada_ahora.jugador) //BLANCAS=0, NEGRAS, GRAVEDAD_N, GRAVEDA_B
	{
	case NEGRAS:		jugada_ahora.jugador = GRAVEDAD_N;	break;
	case GRAVEDAD_N:	jugada_ahora.jugador = BLANCAS;		break;
	case BLANCAS:		jugada_ahora.jugador = GRAVEDAD_B;	break;
	case GRAVEDAD_B:	jugada_ahora.jugador = NEGRAS;	break;
	default:			jugada_ahora.jugador = GRAVEDAD_N;	break;
	};
}

void Juego::turno_()
{
	switch (jugada_ahora.jugador) //BLANCAS=0, NEGRAS, GRAVEDAD_N, GRAVEDA_B
	{
	case NEGRAS:		jugada_ahora.jugador = NEGRAS;	break;
	case GRAVEDAD_N:	jugada_ahora.jugador = GRAVEDAD_N;		break;
	case BLANCAS:		jugada_ahora.jugador = BLANCAS;	break;
	case GRAVEDAD_B:	jugada_ahora.jugador = BLANCAS;	break;
	default:			jugada_ahora.jugador = GRAVEDAD_N;	break;
	};
}

void Juego::dibuja_lista_partidas()
{
	gestor_de_partidas;
}


void Juego::generar_piezas()
{
	// Aqui pondremos un bucle para generar el vector de GUI_pieza (solo se ejecuta al principio)
	for (int i = 0; i < todas_piezas_LISTA.size(); i++)
	{
		PIEZA_STRU datos_pz = todas_piezas_LISTA[i];
		Pieza_GUI pz(datos_pz);
		todas_piezas_GUI.push_back(pz);
	}
}

void Juego::actualizar_piezas()
// se actualizarán los valores de las piezas en base a la lista_datos_de_piezas
{
	for (int i = 0; i < todas_piezas_LISTA.size(); i++)
	{
		PIEZA_STRU datos_pz = todas_piezas_LISTA[i];
		//GUI_Pieza pz(datos_pz);
	}

	PIEZA_STRU pieza{};

	for (auto it_in = todas_piezas_LISTA.begin(); it_in != todas_piezas_LISTA.end(); ++it_in)
	{
		auto tipo_in = (*it_in).c_tipo;
		auto sub_tipo_in = (*it_in).c_pieza;
		auto color_in = (*it_in).c_color;
		auto fila_in = (*it_in).c_fila;
		auto columna_in = (*it_in).c_columna;

		for (auto it_pz = todas_piezas_GUI.begin(); it_pz != todas_piezas_GUI.end(); ++it_pz)
		{
			if (tipo_in == (*it_pz)._datos_pieza.c_tipo && sub_tipo_in == (*it_pz)._datos_pieza.c_pieza && color_in == (*it_pz)._datos_pieza.c_color)
				// si el elemnto del listado coincide con las características 
				// del objeto se le asigna la posición del listado
			{
				(*it_pz)._datos_pieza.c_fila = fila_in;
				(*it_pz)._datos_pieza.c_columna = columna_in;
			}
		};
	}
}
void Juego::dibujar_piezas()
// Aqui ponemos un bucle para dibujar todas las piezas
{
	for (int i = 0; i < todas_piezas_GUI.size(); i++)
	{
		todas_piezas_GUI[i].dibuja_pieza();
	}
}

void Juego::incrementa_cursor(int inc_f, int inc_c)
{
	get_casilla_cursor()->incrementa_posicion(inc_f, inc_c);
}


void Juego::mueve_pieza_locked(int n_posicion_movimiento) // se debe mover a la posición que marca Casilla
{
	jugada_ahora.vaciar_jugada();
	if (cual_pieza_locked != nullptr) {
		Pieza_GUI aux = (*cual_pieza_locked); // pieza que queremos mover
		auto cas = get_casilla_cursor();
		aux._datos_pieza.c_fila = cas->fila; aux._datos_pieza.c_columna = cas->columna;
		jugada_ahora.add_pieza_a_jugada(aux._datos_pieza);
		if (n_posicion_movimiento > partida_actual.get_jugadas().size()) n_posicion_movimiento = partida_actual.get_jugadas().size();
		if (n_posicion_movimiento < 0) n_posicion_movimiento = 0;
		partida_actual.borrar_jugadas_desde_N(n_posicion_movimiento);
		partida_actual.add_jugada_a_partida(jugada_ahora);
		avanza_siguiente_turno();
	}
}

Pieza_GUI* Juego::get_pieza_locked()
{
	return cual_pieza_locked;
}

GUI_marcador_locked* Juego::get_casilla_locked()
{
	return casilla_lckd;
}

void Juego::generar_listado_datos_piezas_OFF()
// Se ejecuta para tener relleno lista_datos_de_piezas con todas las piezas 
// fuera del tablero. Solo se ejecuta al principio del programa
{
	PIEZA_STRU pieza{};

	pieza.c_columna = C_ND;
	pieza.c_fila = f_ND;
	pieza.c_color = negra;

	/////// BLANCAS //////////////
	pieza.c_tipo = peon; /////////--- PEONES-----/////////
	pieza.c_pieza = PZ_peon_torre_reina;		todas_piezas_LISTA.push_back(pieza);
	pieza.c_pieza = PZ_peon_caballo_reina;		todas_piezas_LISTA.push_back(pieza);
	pieza.c_pieza = PZ_peon_alfil_reina;		todas_piezas_LISTA.push_back(pieza);
	pieza.c_pieza = PZ_peon_reina;				todas_piezas_LISTA.push_back(pieza);
	pieza.c_pieza = PZ_peon_rey;				todas_piezas_LISTA.push_back(pieza);
	pieza.c_pieza = PZ_peon_alfil_rey;			todas_piezas_LISTA.push_back(pieza);
	pieza.c_pieza = PZ_peon_caballo_rey;		todas_piezas_LISTA.push_back(pieza);
	pieza.c_pieza = PZ_peon_torre_rey;			todas_piezas_LISTA.push_back(pieza);
	pieza.c_tipo = torre; //////////////////
	pieza.c_pieza = PZ_torre_reina;				todas_piezas_LISTA.push_back(pieza);
	pieza.c_pieza = PZ_torre_rey; 				todas_piezas_LISTA.push_back(pieza);
	pieza.c_tipo = caballo; //////////////////
	pieza.c_pieza = PZ_caballo_reina; 			todas_piezas_LISTA.push_back(pieza);
	pieza.c_pieza = PZ_caballo_rey; 			todas_piezas_LISTA.push_back(pieza);
	pieza.c_tipo = alfil; //////////////////
	pieza.c_pieza = PZ_alfil_reina; 			todas_piezas_LISTA.push_back(pieza);
	pieza.c_pieza = PZ_alfil_rey; 				todas_piezas_LISTA.push_back(pieza);
	pieza.c_tipo = reina; //////////////////
	pieza.c_pieza = PZ_reina; 					todas_piezas_LISTA.push_back(pieza);
	pieza.c_tipo = rey; //////////////////
	pieza.c_pieza = PZ_rey; 					todas_piezas_LISTA.push_back(pieza);

	/////// NEGRAS //////////////
	pieza.c_color = blanca;
	pieza.c_tipo = peon; /////////--- PEONES-----/////////
	pieza.c_pieza = PZ_peon_torre_reina;		todas_piezas_LISTA.push_back(pieza);
	pieza.c_pieza = PZ_peon_caballo_reina;		todas_piezas_LISTA.push_back(pieza);
	pieza.c_pieza = PZ_peon_alfil_reina;		todas_piezas_LISTA.push_back(pieza);
	pieza.c_pieza = PZ_peon_reina;				todas_piezas_LISTA.push_back(pieza);
	pieza.c_pieza = PZ_peon_rey;				todas_piezas_LISTA.push_back(pieza);
	pieza.c_pieza = PZ_peon_alfil_rey;			todas_piezas_LISTA.push_back(pieza);
	pieza.c_pieza = PZ_peon_caballo_rey;		todas_piezas_LISTA.push_back(pieza);
	pieza.c_pieza = PZ_peon_torre_rey;			todas_piezas_LISTA.push_back(pieza);
	pieza.c_tipo = torre; //////////////////
	pieza.c_pieza = PZ_torre_reina;				todas_piezas_LISTA.push_back(pieza);
	pieza.c_pieza = PZ_torre_rey; 				todas_piezas_LISTA.push_back(pieza);
	pieza.c_tipo = caballo; //////////////////
	pieza.c_pieza = PZ_caballo_reina; 			todas_piezas_LISTA.push_back(pieza);
	pieza.c_pieza = PZ_caballo_rey; 			todas_piezas_LISTA.push_back(pieza);
	pieza.c_tipo = alfil; //////////////////
	pieza.c_pieza = PZ_alfil_reina; 			todas_piezas_LISTA.push_back(pieza);
	pieza.c_pieza = PZ_alfil_rey; 				todas_piezas_LISTA.push_back(pieza);
	pieza.c_tipo = reina; //////////////////
	pieza.c_pieza = PZ_reina; 					todas_piezas_LISTA.push_back(pieza);
	pieza.c_tipo = rey; //////////////////
	pieza.c_pieza = PZ_rey; 					todas_piezas_LISTA.push_back(pieza);
}

void Juego::listado_datos_piezas___un_movimiento(PIEZA_STRU pieza_a_mover)
{
	PIEZA_STRU pieza{};
	int contador = 0;

	for (auto it = todas_piezas_LISTA.begin(); it != todas_piezas_LISTA.end(); ++it)
	{
		contador++;
		auto tip = (*it).c_tipo; auto pz_pieza = (*it).c_pieza; auto col = (*it).c_color;

		if (pz_pieza == pieza_a_mover.c_pieza && col == pieza_a_mover.c_color)
		{
			(*it).c_columna = pieza_a_mover.c_columna;
			(*it).c_fila = pieza_a_mover.c_fila;
		}
	}
}

bool Juego::comprobar_movimiento() {
	if (cual_pieza_locked != nullptr) {
		bool movimiento;
		casilla cas;
		cas.set_fila (get_casilla_cursor()->get_fila());
		cas.set_columna(get_casilla_cursor()->get_columna());
		int col = cual_pieza_locked->_datos_pieza.c_columna;
		int fila = cual_pieza_locked->_datos_pieza.c_fila;
		switch (cual_pieza_locked->_datos_pieza.c_tipo) {
		case peon:
			Peon pieza_aux;
			pieza_aux.set_fila(fila);
			pieza_aux.set_columna(col);
			movimiento = pieza_aux.mover(cas);
			break;

		case torre:
			Torre pieza_aux;
			pieza_aux.set_fila(fila);
			pieza_aux.set_columna(col);
			movimiento = pieza_aux.mover(cas);
			break;
		case caballo:
			Caballo pieza_aux;
			pieza_aux.set_fila(fila);
			pieza_aux.set_columna(col);
			movimiento = pieza_aux.mover(cas);
			break;

		case alfil:
			Alfil pieza_aux;
			pieza_aux.set_fila(fila);
			pieza_aux.set_columna(col);
			movimiento = pieza_aux.mover(cas);
			break;

		case reina:
			Reina pieza_aux;
			pieza_aux.set_fila(fila);
			pieza_aux.set_columna(col);
			movimiento = pieza_aux.mover(cas);
			break;

		case rey:
			Rey pieza_aux;
			pieza_aux.set_fila(fila);
			pieza_aux.set_columna(col);
			movimiento = pieza_aux.mover(cas);
			break;
		default: 
			return false;
		}
		return movimiento;
		
	}

}
