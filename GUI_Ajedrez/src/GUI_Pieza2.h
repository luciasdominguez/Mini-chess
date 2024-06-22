#pragma once
#include "ETSIDI.h"
#include <string>

//#include "GUI_Tablero.h"

using namespace ETSIDI;


enum ENUM_PIEZA { PZ_peon_rey, PZ_rey, PZ_reina, PZ_peon_reina, PZ_peon_torre_rey, PZ_peon_torre_reina, PZ_peon_caballo_rey, PZ_peon_caballo_reina, PZ_peon_alfil_rey, PZ_peon_alfil_reina, PZ_caballo_rey, PZ_caballo_reina, PZ_alfil_rey, PZ_alfil_reina, PZ_torre_rey, PZ_torre_reina };
enum ENUM_TIPO { peon, torre, caballo, alfil, reina, rey };
enum ENUM_FILA { f1 = 1, f2, f3, f4, f5, f6, f7, f8, f_ND = 0 };
enum ENUM_COLUMNA { A = 1, B, C, D, E, F, G, H, C_ND = 0 };
enum ENUM_COLOR { blanca, negra };

typedef struct PIEZA_STRU {
	enum ENUM_COLOR c_color = blanca;
	enum ENUM_PIEZA c_pieza = PZ_peon_rey;
	enum ENUM_FILA c_fila = f2;
	enum ENUM_COLUMNA c_columna = E;
	enum ENUM_TIPO c_tipo = peon;
};

class Pieza_GUI
{
	friend class gestor_movimientos;
	string textura;
	int size_x{}, size_y{};
	float pos_x{}, pos_y{}; /// posición según escala del sprite

	SpriteSequence* sprite;

	PIEZA_STRU _datos_pieza;
	void calculaPos(); /// calcula posicion en valores para el sprite en función de la posicion
	void calculaTextura();



public:
	Pieza_GUI();
	Pieza_GUI(PIEZA_STRU d);

	void dibuja_pieza();
	void set_datosPieza(PIEZA_STRU datos);
	PIEZA_STRU get_datosPieza();

	friend class Juego;
};

