#include "Juego.h"
//#include "GUI_Pieza2.h"

Juego::Juego()
{
	generar_listado_datos_piezas_OFF();
	generar_piezas();

	//turno_ = BLANCAS;
	casilla_cursor = new GUI_marcador_cursor(f5, E);
	turno = new GUI_turno;
	Mns_jaque_mate = new GUI_jaque_mate;
	gestor_de_partidas = new GUI_gestor_partidas;
	estado_Partidas_Jugadas = new GUI_estado_P_J;
	//casilla_lckd = new GUI_marcador_locked(f_ND, C_ND);
	casilla_lckd = new GUI_marcador_locked(f6, C);
	quien_mueve_ahora = BLANCAS;
	jugada_ultima.jugador = BLANCAS;  /// quien empieza
	jugada_actual.jugador = GRAVEDAD_N;
	//casilla_destino = new GUI_casilla(OFF, f6, D);
}

void Juego::carga_partida_al_GUI(int jugada_destino, bool en_la_ultima)
{
	//generar_partida();  // los movimientos de la partida se recogen con esta funci�n
	generar_listado_datos_piezas_OFF(); // se ponen todas las piezas en almacen
	vector<GUI_jugada> lista_jugadas = partida_actual.get_jugadas();
	int size_partida = lista_jugadas.size();

	if (en_la_ultima)
		jugada_destino = size_partida - 1;
	else
	{
		if (jugada_destino < 0) jugada_destino = size_partida - 1;
	}

	// para un numero negativo se asume que se cogen todos los movimientos
	auto jj = lista_jugadas.at(jugada_destino);

	int cont1 = 0;
	for (int idx_jj = 0; idx_jj <= jugada_destino; ++idx_jj)
	{
		auto jug = lista_jugadas.at(idx_jj);
		quien_mueve_ahora = jug.jugador;

		if (!en_la_ultima) {// quiere decir que hay al menos una jugada posterior
			auto jug_sig = lista_jugadas.at(idx_jj + 1);
			quien_mueve_ahora = jug_sig.jugador; // el jugador siguiente es quien dice la siguiente jugada
		}
		else
			//calcula_siguiente_turno()
			;  // el jugador siguiente es quien marcan las reglas

		vector<PIEZA_STRU> Lista_Pz_Mov = jug.get_lista_piezas_movidas();
		for (auto it_in_2 = Lista_Pz_Mov.begin(); it_in_2 != (Lista_Pz_Mov.end()); ++it_in_2)
		{
			listado_datos_piezas___un_movimiento(*it_in_2);
		}
		jugada_actual = jug;
		cont1++;
	}
	get_msg_jaque_mate()->set_ver_jaque_mate(jj.jaque_mate);
	if (en_la_ultima)
		avanza_turno();
}


void Juego::guarda_partida_actual()
{
	auto aux = partida_actual;
	//bbb auto jq = aux.get_jaque_mate();
	//gestor_de_partidas->insert_update_partida(aux.get_nombre_partida(), aux.get_jugadas(), aux.get_jaque_mate());
	gestor_de_partidas->insert_update_partida(aux.get_nombre_partida(), aux.get_jugadas());
}

void Juego::dibuja_juego()
{
	miTablero.dibuja_tablero();
	//turno->dibuja_turno(jugada_actual.jugador);
	//turno->dibuja_turno(turno_para_);
	turno->dibuja_turno(quien_mueve_ahora);
	auto parti = get_partida_actual();
	Mns_jaque_mate->dibuja_jaque_mate();
	estado_Partidas_Jugadas->dibuja_seleccion_partida();
	actualizar_piezas();
	dibujar_piezas();
	casilla_cursor->dibuja_sprite();
	casilla_lckd->dibuja_sprite();
	listado_partidas.set_nombres_partidas(gestor_de_partidas->get_nombres_partidas());
	listado_partidas.imprime_nombres();

	listado_jugadas.set_lineas_partida(partida_actual.get_lista_movimientos());
	listado_jugadas.set_nombre_partida(partida_actual.get_nombre_partida());
	listado_jugadas.imprime_jugadas();
}


ENUM_JUGADOR Juego::get_jugador_actual()
{
	//jugada_actual.jugador = quien_mueve_ahora;
	return quien_mueve_ahora;
	//return jugada_actual.jugador;
}

void Juego::cargar_partida(string nombre)
{  /// si el nombre no se encuentra se genera una partida con ese nombre
	partida_actual = gestor_de_partidas->get_or_new_partida(nombre);
	jugada_ultima = partida_actual.get_jugadas().back();

}

void Juego::cargar_partida_ejemplo()
{
	partida_actual = gestor_de_partidas->get_partida_ejemplo();
	jugada_ultima = partida_actual.get_jugadas().back(); //el ultimo movimiento de la partida

}

GUI_partida* Juego::get_partida_actual()
{
	return &partida_actual;
}

void Juego::check_pieza_movible()
{  // verifica si la casilla del cursor tiene una pieza movible
	//Si es as�, se almacena que pieza tiene y la casilla podra ser Locked

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
						(((*it_in)._datos_pieza.c_color == blanca && quien_mueve_ahora == BLANCAS) ||
							(*it_in)._datos_pieza.c_color == negra && quien_mueve_ahora == NEGRAS)
					{   // se ha encontrado una pieza en la posci�n de la casilla y del color del turno
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
	if (s == modo_seleccion_partida)
		estado_Partidas_Jugadas->set_partidas_o_jugadas(modo_juego);
	else
		estado_Partidas_Jugadas->set_partidas_o_jugadas(modo_seleccion_partida);

}

T_listado_partidas Juego::get_listado_partidas()
{
	return listado_partidas;
}

T_listado_jugadas Juego::get_listado_jugadas()
{
	auto jugadas = partida_actual.get_jugadas();
	for (auto it_jugada = jugadas.begin(); it_jugada != (jugadas.end()); ++it_jugada)
	{
		auto piezas = (*it_jugada).get_lista_piezas_movidas();
		for (auto it_pz = piezas.begin(); it_pz != (piezas.end()); ++it_pz)
		{
			(*it_pz).c_color;
		}
	}
	return listado_jugadas;
}

GUI_gestor_partidas Juego::get_almacen_partidas()
{
	return (*gestor_de_partidas);
}

int Juego::get_N_jugadas_partida_actual()
{
	return get_partida_actual()->get_jugadas().size();
}

GUI_jaque_mate* Juego::get_msg_jaque_mate()
{
	return Mns_jaque_mate;
}

////////void Juego::jaque_mate_partida_actual(bool jaque)
////////{
////////	partida_actual.set_jaque_mate(jaque);
////////}

void Juego::avanza_turno()
{
	calcula_siguiente_turno();
	quien_mueve_ahora = turno_para_;
	calcula_siguiente_turno();
}

void Juego::calcula_siguiente_turno()
{
	switch (quien_mueve_ahora) //BLANCAS=0, NEGRAS, GRAVEDAD_N, GRAVEDA_B
	{
	case NEGRAS:		turno_para_ = GRAVEDAD_N;	break;
	case GRAVEDAD_N:	turno_para_ = BLANCAS;		break;
	case BLANCAS:		turno_para_ = GRAVEDAD_B;	break;
	case GRAVEDAD_B:	turno_para_ = NEGRAS;		break;
	default:			turno_para_ = GRAVEDAD_N;	break;
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
// se actualizar�n los valores de las piezas en base a la lista_datos_de_piezas
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
				// si el elemento del listado coincide con las caracter�sticas 
				// del objeto se le asigna la posici�n del listado
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


void Juego::mueve_pieza_locked(int n_posicion_jugada) // se debe a�adir la pieza marcada a la partida
{ // Este funci�n solamente a�ade la pieza marcada sin atender a ninguna regla del juego
  // Es la l�gica del juego la que validar� esta jugada, anulando la jugada o a�adiendo m�s piezas porque
  // se ha hecho un enroque o se ha comido una pieza del otro jugador
  // Para hacer a�adir jugadas de la logica o de la gravedad est�n las funciones siguientes
	//primero verificamos que la 

	jugada_actual.vaciar_jugada();
	jugada_actual.jugador = quien_mueve_ahora;
	if (cual_pieza_locked != nullptr) {
		Pieza_GUI pz_lck = (*cual_pieza_locked); // pieza que queremos mover
		auto casilla = get_casilla_cursor();
		if ( // hay que verificar que origen y destino no sean iguales
			(pz_lck._datos_pieza.c_fila != casilla->fila) ||
			(pz_lck._datos_pieza.c_columna != casilla->columna))
		{
			pz_lck._datos_pieza.c_fila = casilla->fila;
			pz_lck._datos_pieza.c_columna = casilla->columna;
			jugada_actual.add_pieza_a_jugada(pz_lck._datos_pieza);
			if (n_posicion_jugada > partida_actual.get_jugadas().size())
				n_posicion_jugada = partida_actual.get_jugadas().size();
			if (n_posicion_jugada < 0)
				n_posicion_jugada = 0;
			partida_actual.borrar_jugadas_desde_N(n_posicion_jugada + 1); // no hay que borrar la primera (pieza a posicion inicial)
			partida_actual.add_jugada_a_partida(jugada_actual);
			//avanza_siguiente_turno();
			//avanza_turno();			
		};
	}
}

void Juego::add_jugada_libre(int n_posicion_jugada, vector<PIEZA_STRU> lista_Piezas, bool jaque) {
	jugada_actual.vaciar_jugada();
	jugada_actual.jugador = quien_mueve_ahora;
	jugada_actual.jaque_mate = jaque;
	for (auto it = lista_Piezas.begin(); it != lista_Piezas.end(); ++it)
	{
		jugada_actual.add_pieza_a_jugada(*it);
	}
	if (n_posicion_jugada > partida_actual.get_jugadas().size())
		n_posicion_jugada = partida_actual.get_jugadas().size();
	if (n_posicion_jugada < 0)
		n_posicion_jugada = 0;
	partida_actual.borrar_jugadas_desde_N(n_posicion_jugada);
	partida_actual.add_jugada_a_partida(jugada_actual);

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
