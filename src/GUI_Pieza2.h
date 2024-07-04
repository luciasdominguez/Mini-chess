#pragma once
#include "ETSIDI.h"
#include <string>
//#include "GUI_Tablero.h"

using namespace ETSIDI;


enum ENUM_PIEZA {
	PZ_peon_rey = 0, PZ_rey = 1, PZ_reina = 2, PZ_peon_reina = 3, PZ_peon_torre_rey = 4,
	PZ_peon_torre_reina = 5, PZ_peon_caballo_rey = 6, PZ_peon_caballo_reina = 7,
	PZ_peon_alfil_rey = 8, PZ_peon_alfil_reina = 9,
	PZ_caballo_rey = 10, PZ_caballo_reina = 11,
	PZ_alfil_rey = 12, PZ_alfil_reina = 13,
	PZ_torre_rey = 14, PZ_torre_reina = 15, PZ_NO = -1
};
enum ENUM_TIPO { peon, torre, caballo, alfil, reina, rey, t_NO = -1 };
enum ENUM_FILA { f1 = 1, f2, f3, f4, f5, f6, f7, f8, f_ND = -1 };
enum ENUM_COLUMNA { A = 1, B, C, D, E, F, G, H, C_ND = -1 };
enum ENUM_COLOR { blanca = 0, negra = 1, color_NO = -1 };

typedef struct PIEZA_STRU {
	enum ENUM_COLOR c_color = color_NO;
	enum ENUM_PIEZA c_pieza = PZ_NO;
	enum ENUM_FILA c_fila = f_ND;
	enum ENUM_COLUMNA c_columna = C_ND;
	enum ENUM_TIPO c_tipo = t_NO;
};

class Pieza_GUI
{
	string textura;
	int size_x{}, size_y{};
	float pos_x{}, pos_y{}; /// posición según escala del sprite

	SpriteSequence* sprite;

	PIEZA_STRU _datos_pieza;
	void calculaPos(); /// calcula posicion en valores para el sprite en función de la posicion
	void calculaTextura();
	bool animada = false;


public:
	Pieza_GUI();
	Pieza_GUI(PIEZA_STRU d);

	void dibuja_pieza();
	void anima_pieza(bool anima);
	void set_datosPieza(PIEZA_STRU datos);
	PIEZA_STRU get_datosPieza();

	friend class Juego;
};

