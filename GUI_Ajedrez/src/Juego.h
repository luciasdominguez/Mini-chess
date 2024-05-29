#pragma once
#include "GUI_Tablero.h"
#include "GUI_Fila.h"
#include "GUI_Casilla.h"
#include <vector>
#include "GUI_Pieza2.h"

using std::vector;
using ETSIDI::Vector2D;

enum ENUM_TIPO { peon = 1, torre, caballo, alfil, reina, rey, tipo_ND=0 };
enum ENUM_FILA { f1 = 1, f2, f3, f4, f5, f6, f7, f8, fila_ND=0 };
enum ENUM_COLUMNA { A = 1, B, C, D, E, F, G, H, columna_ND=0 };
enum ENUM_COLOR { blanca = 1, negra, color_ND=0 };

typedef struct STRU_PIEZA {
	enum ENUM_TIPO c_tipo;
	enum ENUM_FILA c_fila;
	enum ENUM_COLUMNA c_columna;
	enum ENUM_COLOR c_color;
};

class Juego
{
 
	//std::vector<Objeto> elementos;
	//elementos.emplace(elementos.end());
	//vector<GUI_pieza*> lista_piezas;
	//vector<GUI_pieza*> lista;
	GUI_Pieza2 pieza1;
	GUI_Pieza2 pieza2;
	GUI_Tablero miTablero;
	//lista_piezas[]


	//vector<GUI_pieza*> lista_piezas;

	

	//enum color { blanca = 0, negra } color{};
	//enum tipo { peon = 0, torre, caballo, alfil, reina, rey, vacio } tipo{};
	//enum fila { f1 = 1, f2, f3, f4, f5, f6, f7, f8 } fila{};
	//enum columa { A = 1, B, C, D, E, F, G, H } columna{};

public:

	Juego();
	void dibuja_juego();
	Vector2D calculo_posicion_pieza(Vector2D tam_tablero, Vector2D pos_tablero, enum fila fila, enum columna columna);
	void leer_listado_piezas();

	//GUI_Tablero miTablero;

};

