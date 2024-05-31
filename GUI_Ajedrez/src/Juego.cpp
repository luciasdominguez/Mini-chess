#include "Juego.h"
#include "GUI_Pieza2.h"

Juego::Juego()
{
	
	//
	////miTablero->dibuja_tablero();
	//GUI_pieza* miP = new GUI_pieza;
	//this->leer_listado_piezas();
}

void Juego::dibuja_juego()
{
	miTablero.dibuja_tablero();


	//calculo_posicion_pieza(miT->tamaño_tablero, miT->posicion_tablero, miP->fila, miP->columna );
	////STRU_PIEZA p1_datos{ rey,SB_no_aplica, f5, A, blanca };
	STRU_PIEZA p1_datos{ torre,SB_torre_reina, fila_ND, A, negra };
	//STRU_PIEZA p2_datos{ caballo,SB_caballo_rey, f8, B, negra };
	STRU_PIEZA p2_datos{ peon,SB_torre_reina, fila_ND, A, blanca };


	GUI_Pieza2 pieza1({ torre,SB_torre_reina, fila_ND, columna_ND, negra });
	//pieza1.set_datosPieza(p1_datos);
	pieza1.dibuja_pieza();
	GUI_Pieza2 pieza2(p2_datos);
	//pieza2.set_datosPieza(p2_datos);
	pieza2.dibuja_pieza();
}

void Juego::leer_listado_piezas()
{
	// Aqui pondremos un bucle para generar el vector de piezas
	STRU_PIEZA pz1{};
	pz1.c_color = blanca;
	pz1.c_columna = B;
	pz1.c_fila = f2;
	pz1.c_tipo = peon;

	STRU_PIEZA pz2{};
	pz1.c_color = blanca;
	pz1.c_columna = G;
	pz1.c_fila = f3;
	pz1.c_tipo = rey;

	////////////////
	vector<STRU_PIEZA> lista_de_piezas;
	lista_de_piezas.push_back(pz1);
	lista_de_piezas.push_back(pz2);
}

Vector2D Juego::calculo_posicion_pieza(Vector2D tam_tablero, Vector2D pos_tablero, fila fila, columna columna)
{
	float pos_x = tam_tablero.x / 10 + pos_tablero.x;
	float pos_y = tam_tablero.y / 10 + pos_tablero.y;
	return Vector2D();
}
