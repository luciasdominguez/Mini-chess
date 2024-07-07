#pragma once
#include <vector>
#include "GUI_partida.h"
#include "GUI_pieza.h"
#include "fichas.h"
#include "gestor_jaques.h"

//enum ENUM_ANALISIS {  = 0, NEGRAS, GRAVEDAD_N, GRAVEDAD_B };
enum ENUM_TRAYECTO { TR_torre = 0, TR_alfil = 1, TR_caballo = 2, TR_otro = -1 };

class Cl_logica
{
	tablero tablero_temporal = tablero(8, 8);;
	GUI_partida _partida_in;
	GUI_jugada jug;
	bool jaque_mate = false;
	PIEZA_STRU pz;
	PIEZA_STRU pz_0;

	ficha *p =new Peon;
	

	//torre
	ficha *t = new Torre;

	//alfil
	ficha* a = new Alfil;

	//caballo
	ficha* c = new Caballo;

	//reina
	ficha* r = new Reina;

	//rey
	ficha* rey_ = new Rey;

	////vacia
	//ficha* vacio = new Vacia;

	//T_tablero
	vector<vector<PIEZA_STRU>> TableroGUI_actual;
	PIEZA_STRU busca_posicion_anterior(PIEZA_STRU pieza_jugada);

	void genera_tablero_temporal();

public:
	Cl_logica();

	void analiza_gravedad(vector<vector<PIEZA_STRU>> Tablero, GUI_jugada& jugada_propia, GUI_jugada& jugada_gravedad);
	// Si la jugada es correcta:
	//	se genera la "jugada_propia" pero añadiendo, si es el caso,
	//	el resto de piezas afectadas (por haber comido una pieza contraria, un enroque ...
	//	Tambien se devuelve en "jugada_gravedad" la lista de las piezas que se ven afectadas por la gravedad.
	// 
	// Si la "jugaga_gravedad" ha generado un jaque mate devuelve 2 para que se termine la partida
	// si no es jaque mate devuelve 1
	// Si la ultima jugada en valida al función devuelve 0;
	int analiza_jugada(vector<vector<PIEZA_STRU>> Tablero_actual_, // situación del tablero antes de realizar la "jugada_propia"
		GUI_jugada& jugada_propia, // jugada que se debe analizar en función de la situación del tablero
		// se devolverá la jugada actualizada si la logica del juego afecta a otra pieza
		GUI_jugada& jugada_gravedad, // jugada que realiza la gravedad
		bool jugada_erronea);  // solamete para test


	/////////////////////

};