#include "Juego.h"


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

	//Vector2D t;



	//calculo_posicion_pieza(miT->tamaño_tablero, miT->posicion_tablero, miP->fila, miP->columna );

	pieza1.dibuja_pieza();
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
