#pragma once
#include <vector>
#include "GUI_Pieza2.h"
#include "GUI_jugada.h"

class GUI_partida  // es una lista de movimientos y un nombre
{
	string nombre_partida;
	vector<GUI_jugada> lista_jugadas; // una partida es una lista de jugadas.

	//T_tablero
	vector<vector<PIEZA_STRU>> Tablero_actual_;
	vector<vector<PIEZA_STRU>> Tablero_temp;
	PIEZA_STRU pz_0; //pieza vacia
	GUI_jugada jugada_i;

	/////////// Mapea el enum ENUM_JUGADOR a su correspondiente string ------------
	map<ENUM_JUGADOR, string> map_Jugador_a_String = { { BLANCAS, "jugador Bl" },
													   { NEGRAS, "jugador Ng" },
														{ GRAVEDAD_N, "jugador GrNg" },
														{ GRAVEDAD_B, "jugador GrBl" } };

	string Jugador_a_String(ENUM_JUGADOR enu_jugador)
	{
		return map_Jugador_a_String[enu_jugador];
	}

	///////////// Mapea el enum ENUM_COLOR a su correspondiente string -------------
	map<ENUM_COLOR, string> map_Color_a_String = { { blanca, "Bl" },
													 { negra, "Ng" } };

	string Color_a_String(ENUM_COLOR enu_color)
	{
		return map_Color_a_String[enu_color];
	}

	map<ENUM_PIEZA, string> map_Pieza_a_String = {
				{ PZ_peon_rey,				"P.Ry" },
				{ PZ_rey,					"Rey" },
				{ PZ_reina,					"Reina" },
				{ PZ_peon_reina,			"P.Ra" },
				{ PZ_peon_torre_rey,		"P.Tor.Ry" },
				{ PZ_peon_torre_reina,		"P.Tor.Ra" },
				{ PZ_peon_caballo_rey,		"P.Cab.Ry" },	
				{ PZ_peon_caballo_reina,	"P.Cab.Ra" },
				{ PZ_peon_alfil_rey,		"P.Alf.Ry" },
				{ PZ_peon_alfil_reina,		"P.Alf.Ra" },
				{ PZ_caballo_rey,			"Cab.Ry" },	
				{ PZ_caballo_reina,			"Cab.Ra" },
				{ PZ_alfil_rey,				"Alf.Ry" },
				{ PZ_alfil_reina,			"Alf.Ra" },
				{ PZ_torre_rey,				"Tor.Ry" },	
				{ PZ_torre_reina,			"Tor.Ra" }
				};
							
	string Pieza_a_String(ENUM_PIEZA enu_pieza)
	{
		return map_Pieza_a_String[enu_pieza];
	}
	////////////////////////////////
	//enum ENUM_FILA { f1 = 1, f2, f3, f4, f5, f6, f7, f8, f_ND = 0 };
	map<ENUM_FILA, string> map_fila_a_String = {
			{ f1,	"1" },
			{ f2,	"2" },
			{ f3,	"3" },
			{ f4,	"4" },
			{ f5,	"5" },
			{ f6,	"6" },
			{ f7,	"7" },
			{ f8,	"8" },
			{ f_ND,	"_" }
	};

	string Fila_a_String(ENUM_FILA enu_fila)
	{
		return map_fila_a_String[enu_fila];
	}

	//////////////////////////////////////////////
	//enum ENUM_COLUMNA { A = 1, B, C, D, E, F, G, H, C_ND = 0 };

	map<ENUM_COLUMNA, string> map_columna_a_String = {
			{ A,	"A" },
			{ B,	"B" },
			{ C,	"C" },
			{ D,	"D" },
			{ E,	"E" },
			{ F,	"F" },
			{ G,	"G" },
			{ H,	"H" },
			{ C_ND,	"_" }
	};

	string Columna_a_String(ENUM_COLUMNA enu_columna)
	{
		return map_columna_a_String[enu_columna];
	}



public:
	GUI_partida();
	string get_nombre_partida();
	vector<GUI_jugada> get_jugadas();



	void vaciar_partida();
	void borrar_jugadas_desde_N(int desde);
	void borrar_jugada_ultima();
	void add_jugada_a_partida(GUI_jugada jug);
	void set_nombre_de_partida(string);

	void set_jugadas_de_partida(vector<GUI_jugada> lista_jugadas);
	vector<string> get_lista_movimientos(); //todas las jugadas con las piezas de cada una.
	void actualiza_tablero();  // genera un tablero virtual (matriz de 8x8) con las piezas que tiene situadas
	vector<vector<PIEZA_STRU>> get_tablero();
};

