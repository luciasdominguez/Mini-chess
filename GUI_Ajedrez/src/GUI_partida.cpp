#include "GUI_partida.h"

using namespace std;

GUI_partida::GUI_partida()
{
	//jaque_mate = false;
	Tablero_actual_ = {// vector de 2 dimesiones de 8x8
		{ pz_0,pz_0,pz_0,pz_0,pz_0,pz_0,pz_0,pz_0 },
		{ pz_0,pz_0,pz_0,pz_0,pz_0,pz_0,pz_0,pz_0 },
		{ pz_0,pz_0,pz_0,pz_0,pz_0,pz_0,pz_0,pz_0 },
		{ pz_0,pz_0,pz_0,pz_0,pz_0,pz_0,pz_0,pz_0 },
		{ pz_0,pz_0,pz_0,pz_0,pz_0,pz_0,pz_0,pz_0 },
		{ pz_0,pz_0,pz_0,pz_0,pz_0,pz_0,pz_0,pz_0 },
		{ pz_0,pz_0,pz_0,pz_0,pz_0,pz_0,pz_0,pz_0 },
		{ pz_0,pz_0,pz_0,pz_0,pz_0,pz_0,pz_0,pz_0 }
	};
	Tablero_temp = Tablero_actual_;
}

string GUI_partida::get_nombre_partida()
{
	return nombre_partida;
}

vector<GUI_jugada> GUI_partida::get_jugadas()
{
	return lista_jugadas;
}

void GUI_partida::vaciar_partida()
{
	lista_jugadas.erase(lista_jugadas.begin(), lista_jugadas.end());
	GUI_partida();
}

void GUI_partida::borrar_jugadas_desde_N(int desde)
{
	if (desde<lista_jugadas.size())
	lista_jugadas.erase(lista_jugadas.begin()+ desde, lista_jugadas.end());
}


void  GUI_partida::borrar_jugada_ultima() {
	lista_jugadas.pop_back();
}



void GUI_partida::add_jugada_a_partida(GUI_jugada jug)
{
	jug.set_numero_en_la_partida(lista_jugadas.size());
	lista_jugadas.push_back(jug);
}

void GUI_partida::set_nombre_de_partida(string n)
{
	nombre_partida = n;
}

//void GUI_partida::set_jaque_mate(bool mate)
//{
//	jaque_mate = mate;
//}


void GUI_partida::set_jugadas_de_partida(vector<GUI_jugada> lista_j)
{
	lista_jugadas = lista_j;
}

//bool GUI_partida::get_jaque_mate()
//{
//	return jaque_mate;
//}

vector<string> GUI_partida::get_lista_movimientos()
{
	vector<GUI_jugada> jugadas= get_jugadas();
	GUI_jugada jugada;
	string str_num_jugada;
	string str_num_pieza;
	string str_jugador;
	string str_color;
	string str_fila;
	string str_columna;	
	string str_pieza;


	string str_print_fila;
	vector <string> str_print_filas;

	str_print_fila.clear();
	for (auto it_jug = jugadas.begin(); it_jug != jugadas.end(); ++it_jug)
	{
		jugada = (*it_jug);
		str_num_jugada=to_string(jugada.get_numero_en_la_partida());
		str_jugador=Jugador_a_String(jugada.jugador);
		int num_pieza = 0;
		for (auto it = jugada.lista_PiezasMovidas.begin(); it != jugada.lista_PiezasMovidas.end(); ++it)
		{
			num_pieza++;
			str_num_pieza=to_string(num_pieza);
			str_fila.clear();
			auto pieza = (*it);
			str_color = Color_a_String(pieza.c_color);
			str_fila = Fila_a_String(pieza.c_fila);
			str_columna = Columna_a_String(pieza.c_columna);
			str_pieza = Pieza_a_String(pieza.c_pieza);
			//str_print_fila =  "jugada:"+ str_num_jugada+
			//	"; jugador:"+ str_jugador +
			//	"; num_pieza:" + str_num_pieza +
			//	"; nomb_pieza:" + str_pieza + 
			//	"; color:" + str_color + 
			//	"; posicion:" + str_columna + str_fila;
			str_print_fila =  ""+ str_num_jugada+
				"." + str_num_pieza +
				": "+ str_jugador +
				"; " + str_pieza + 
				" " + str_color + 
				" a " + str_columna + str_fila;
			bool no_imprimir;
		
			if (!(str_num_jugada == "0" && str_jugador == "jugador GrNg"))
			str_print_filas.push_back(str_print_fila);
		}
	}
	return str_print_filas;
}

void GUI_partida::actualiza_tablero()
{
	auto jugadas = lista_jugadas;
	//auto jugadas = _partida_in.get_jugadas();
	for (auto it_jug = jugadas.begin(); it_jug != jugadas.end(); ++it_jug)
	{ //lista de jugadas
		jugada_i = (*it_jug); // jugada 

		auto piezas = jugada_i.get_lista_piezas_movidas();
		for (auto it_pz = piezas.begin(); it_pz != piezas.end(); ++it_pz)
		{// lista de piezas
			Tablero_temp = Tablero_actual_;
			PIEZA_STRU pz = (*it_pz);
			PIEZA_STRU pz_anterior;
			auto f = pz.c_fila;  // fila destino
			auto c = pz.c_columna; //columna destino

			//// primero se busca en el tablero_temp (según estaba antes de modificar el tablero)
			for (int ff = 0;ff < 8;ff++) {
				for (int cc = 0;cc < 8;cc++) {
					auto pp = Tablero_temp.at(ff).at(cc);
					if (pp.c_pieza == pz.c_pieza && pp.c_color == pz.c_color) {
						//localizada la pieza en el tablero
						pz_anterior = pp;
						break;
					}
				}
			}// FIN de buscar la posición origen

			//Se vacía la casilla donde estaba la pieza encontrada (si estaba en el tablero)
			if (pz_anterior.c_fila != f_ND && pz_anterior.c_columna != C_ND) {
				auto fff = (int)(pz_anterior.c_fila) - 1;
				auto ccc = (int)(pz_anterior.c_columna) - 1;
				Tablero_actual_.at(fff).at(ccc) = pz_0;
			}

			// Se asigna la pieza movida a la casilla que tiene como destino
			if (f != f_ND && c != C_ND)
				Tablero_actual_.at(((int)f) - 1).at(((int)c) - 1) = pz;

		}

	}
}

vector<vector<PIEZA_STRU>> GUI_partida::get_tablero()
{
	return Tablero_actual_;
}


