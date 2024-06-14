#include "Juego.h"
//#include "GUI_Pieza2.h"

Juego::Juego()
{
	generar_listado_datos_piezas_OFF();
	generar_piezas();

	//turno_ = BLANCAS;
	casilla_cursor = new GUI_marcador_cursor(f5, E);
	turno = new GUI_turno;
	//casilla_lckd = new GUI_marcador_locked(f_ND, C_ND);
	casilla_lckd = new GUI_marcador_locked(f6, C);
	Movimiento_ultimo.jugador = BLANCAS;  /// quien empieza
	//casilla_destino = new GUI_casilla(OFF, f6, D);
}

void Juego::carga_partida_al_GUI(int destino)
{
	//generar_partida();  // los movimientos de la partida se recogen con esta función
	generar_listado_datos_piezas_OFF(); // se ponen todas las piezas en almacen
	int size_partida = partida_actual.size();
	// para un numero negativo o cero se asume que se cogen todos los movimientos
	if (destino <= 0) destino = partida_actual.size(); // para valores menores que cero se carga toda la partida
	if (destino > size_partida) destino = size_partida;
	for (auto it_in = partida_actual.begin(); it_in != (partida_actual.begin() + destino); ++it_in)
	{
		vector<PIEZA_STRU> Lista_Pz_Mov = (*it_in).lista_PiezasMovidas;
		for (auto it_in_2 = Lista_Pz_Mov.begin(); it_in_2 != (Lista_Pz_Mov.end()); ++it_in_2)
		{
			listado_datos_piezas___un_movimiento(*it_in_2);
		}
		//turno.dibuja_turno(Movimiento_ahora.jugador);
	};

}

void Juego::dibuja_juego()
{
	miTablero.dibuja_tablero();
	turno->dibuja_turno(Movimiento_ahora.jugador);
	actualizar_piezas();
	dibujar_piezas();
	casilla_cursor->dibuja_sprite();
	casilla_lckd->dibuja_sprite();
}


ENUM_JUGADOR Juego::get_jugador_actual()
{
	return Movimiento_ahora.jugador;
}

void Juego::cargar_partida(string nombre)
{  /// si el nombre no se encuentra se genera una partida con ese nombre
	partida_actual= almacen_de_partidas.get_or_new_partida(nombre);
	Movimiento_ultimo = partida_actual[partida_actual.size() - 1]; //el ultimo movimiento de la partida
	switch (Movimiento_ultimo.jugador)
	{
		case BLANCAS: 		Movimiento_ahora.jugador = GRAVEDAD_B;	break;
		case GRAVEDAD_B: 	Movimiento_ahora.jugador = NEGRAS;		break;
		case NEGRAS:		Movimiento_ahora.jugador = GRAVEDAD_N;	break;
		case GRAVEDAD_N:	Movimiento_ahora.jugador = BLANCAS;		break;
		default:			Movimiento_ahora.jugador = GRAVEDAD_N;	break;
	};
	avanza_siguiente_turno();
}

void Juego::cargar_partida_ejemplo()
{
	partida_actual = almacen_de_partidas.get_partida_ejemplo();
	Movimiento_ultimo=partida_actual[partida_actual.size()-1]; //el ultimo movimiento de la partida
	switch (Movimiento_ultimo.jugador)
	{
		case BLANCAS: 		Movimiento_ahora.jugador = GRAVEDAD_B;	break;
		case GRAVEDAD_B: 	Movimiento_ahora.jugador = NEGRAS;		break;
		case NEGRAS:		Movimiento_ahora.jugador = GRAVEDAD_N;	break;
		case GRAVEDAD_N:	Movimiento_ahora.jugador = BLANCAS;		break;
		default:			Movimiento_ahora.jugador = GRAVEDAD_N;	break;
	};
	avanza_siguiente_turno();
}

vector<GUI_movimiento> Juego::get_partida()
{
	return partida_actual;
}

void Juego::check_pieza_movible()
{  // verifica si la casilla del cursor tiene una pieza movible
	//Si es así, se almacena que pieza tiene y la casilla podra ser Locked

	if (casilla_lckd != nullptr)
	{
		if (casilla_lckd->get_estado_locked()==ROJO)
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
						(((*it_in)._datos_pieza.c_color == blanca && Movimiento_ahora.jugador == BLANCAS) ||
						(*it_in)._datos_pieza.c_color == negra && Movimiento_ahora.jugador == NEGRAS)
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

void Juego::avanza_siguiente_turno() 
{
	switch (Movimiento_ahora.jugador) //BLANCAS=0, NEGRAS, GRAVEDAD_N, GRAVEDA_B
	{
		case NEGRAS:		Movimiento_ahora.jugador = GRAVEDAD_N;	break;
		case GRAVEDAD_N:	Movimiento_ahora.jugador = BLANCAS;		break;
		case BLANCAS:		Movimiento_ahora.jugador = GRAVEDAD_B;	break;
		case GRAVEDAD_B:	Movimiento_ahora.jugador = NEGRAS;	break;
		default:			Movimiento_ahora.jugador = GRAVEDAD_N;	break;
	};

}

void Juego::turno_()
{
	switch (Movimiento_ahora.jugador) //BLANCAS=0, NEGRAS, GRAVEDAD_N, GRAVEDA_B
	{
	case NEGRAS:		Movimiento_ahora.jugador = NEGRAS;	break;
	case GRAVEDAD_N:	Movimiento_ahora.jugador = GRAVEDAD_N;		break;
	case BLANCAS:		Movimiento_ahora.jugador = BLANCAS;	break;
	case GRAVEDAD_B:	Movimiento_ahora.jugador = BLANCAS;	break;
	default:			Movimiento_ahora.jugador = GRAVEDAD_N;	break;
	};
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
	Movimiento_ahora.vaciar_movimiento();
	if (cual_pieza_locked != nullptr) {
		Pieza_GUI aux = (*cual_pieza_locked); // pieza que queremos mover
		auto cas = get_casilla_cursor();
		aux._datos_pieza.c_fila = cas->fila; aux._datos_pieza.c_columna = cas->columna;
		Movimiento_ahora.add_pieza_a_movimiento(aux._datos_pieza);
		if (n_posicion_movimiento > partida_actual.size()) n_posicion_movimiento = partida_actual.size();
		if (n_posicion_movimiento <0) n_posicion_movimiento = 0;
		partida_actual.erase(partida_actual.begin()+ n_posicion_movimiento, partida_actual.end());
		partida_actual.push_back(Movimiento_ahora);
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
