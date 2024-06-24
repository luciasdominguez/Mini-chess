#include "GUI_partida.h"

using namespace std;

GUI_partida::GUI_partida()
{

}

string GUI_partida::get_nombre_partida()
{
	return nombre;
}

vector<GUI_jugada> GUI_partida::get_jugadas()
{
	return lista_jugadas;
}

void GUI_partida::vaciar_partida()
{
	lista_jugadas.erase(lista_jugadas.begin(), lista_jugadas.end());

}

void GUI_partida::borrar_jugadas_desde_N(int desde)
{
	if (desde<lista_jugadas.size())
	lista_jugadas.erase(lista_jugadas.begin()+ desde, lista_jugadas.end());
}

void GUI_partida::add_jugada_a_partida(GUI_jugada jug)
{
	jug.set_numero_en_la_partida(lista_jugadas.size());
	lista_jugadas.push_back(jug);
}

void GUI_partida::set_nombre_de_partida(string n)
{
	nombre = n;
}


void GUI_partida::set_jugadas_de_partida(vector<GUI_jugada> lista_j)
{
	lista_jugadas = lista_j;
}

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
		str_num_jugada=to_string(jugada.get_numero_en_la_partida()-1);
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


