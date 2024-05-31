#pragma once
#include "ETSIDI.h"
#include <string>
//#include "GUI_Tablero.h"

using namespace ETSIDI;

enum class en_tipo
{
	peon=1,	torre,	caballo, alfil,	reina,	rey, tipo_ND=0
};

enum class en_color
{
	blanca = 1, negra, color_ND = 0
};



enum ENUM_TIPO { peon = 0, torre, caballo, alfil, reina, rey };
enum ENUM_SUBTIPO { SB_no_aplica = 0, SB_rey , SB_reina, SB_caballo_rey, SB_caballo_reina, SB_alfil_rey, SB_alfil_reina, SB_torre_rey, SB_torre_reina};
enum ENUM_FILA { f1 = 1, f2, f3, f4, f5, f6, f7, f8, fila_ND = 0 };
enum ENUM_COLUMNA { A = 1, B, C, D, E, F, G, H, columna_ND = 0 };
enum ENUM_COLOR { blanca = 0, negra };

typedef struct STRU_PIEZA {
	enum ENUM_TIPO c_tipo = peon;
	enum ENUM_SUBTIPO c_subtipo = SB_torre_rey;
	enum ENUM_FILA c_fila = f1;
	enum ENUM_COLUMNA c_columna = A;
	enum ENUM_COLOR c_color = blanca;
};

class GUI_Pieza2
{
	string textura;
	//char* textura{};
	int size_x{}, size_y{};
	float pos_x{}, pos_y{}; /// posición según el sprite

	SpriteSequence* sprite;
	//ENUM_COLOR color = color_ND;
	//ENUM_TIPO tipo = tipo_ND;

	STRU_PIEZA _datos_pieza;
	void calculaPos(); /// calcula posicion en valores para el sprite en función de la posicion
	void calculaTextura();



public:
	GUI_Pieza2();
	GUI_Pieza2(STRU_PIEZA d);

	void dibuja_pieza();
	void set_datosPieza(STRU_PIEZA datos);
	STRU_PIEZA get_datosPieza();

	friend class Juego;
};

