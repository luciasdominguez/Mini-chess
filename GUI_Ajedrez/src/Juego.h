#pragma once
#include <vector>
#include "GUI_Tablero.h"
#include "GUI_Pieza2.h"

using std::vector;
using ETSIDI::Vector2D;

class Juego
{
 
	//std::vector<Objeto> elementos;
	//elementos.emplace(elementos.end());
	//vector<GUI_pieza*> lista_piezas;
	//vector<GUI_pieza*> lista;
	//STRU_PIEZA d;
	
	//GUI_Pieza2 pieza1(d);
	//GUI_Pieza2 pieza1;
	//GUI_Pieza2 pieza2;
	GUI_Tablero miTablero;

	//lista_piezas[];
	vector<STRU_PIEZA> lista_datos_de_piezas; // los valores se actualizarán en la parte de logica
	vector<GUI_Pieza> lista_de_piezas;
	void generar_piezas();
	void actualizar_piezas();

public:

	Juego();
	void dibuja_juego();
	void dibujar_piezas();

	void generar_listado_datos_piezas_NEW();
	void generar_listado_datos_piezas_OFF(); // funcion auxilar para generar un listado de piezas. hasta que las de la parte lógica


	//GUI_Tablero miTablero;

	void generar_listado_datos_piezas_2(STRU_PIEZA pieza_a_mover);

};

