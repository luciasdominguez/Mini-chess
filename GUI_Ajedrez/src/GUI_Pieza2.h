#pragma once
#include "string.h"
#include "ETSIDI.h"
//#include "GUI_Tablero.h"

using namespace ETSIDI;


class GUI_Pieza2
{

	enum ENUM_TIPO { peon = 1, torre, caballo, alfil, reina, rey, tipo_ND = 0 };
	enum ENUM_FILA { f1 = 1, f2, f3, f4, f5, f6, f7, f8, fila_ND = 0 };
	enum ENUM_COLUMNA { A = 1, B, C, D, E, F, G, H, columna_ND = 0 };
	enum ENUM_COLOR { blanca = 1, negra, color_ND = 0 };


	char* textura{};
	int size_x{}, size_y{};
	SpriteSequence* sprite;
	ENUM_COLOR color = blanca;
	ENUM_TIPO tipo = rey;


public:
	//GUI_pieza() = default;
	GUI_Pieza2();
	void dibuja_pieza();

	friend class Juego;
};

