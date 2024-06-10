#pragma once
#include <vector>
#include "GUI_Tablero.h"
#include "GUI_Pieza2.h"
#include "GUI_casilla.h"
#include "GUI_movimiento.h"
#include "GUI_gestion_partidas.h"

using std::vector;
using ETSIDI::Vector2D;
//ENUM_JUGADOR turno_ = GRAVEDAD;

class Juego
{
 
	GUI_Tablero miTablero;
	GUI_gestion_partidas almacen_de_partidas;
	vector<GUI_movimiento> partida; // una partida es una lista de movimientos.
	GUI_movimiento Movimiento_actual;
	GUI_movimiento Movimiento_nuevo;
	vector<PIEZA_STRU> todas_piezas_LISTA; // los valores se actualizarán en la parte de logica
	vector<Pieza_GUI> todas_piezas_GUI;
	GUI_marcador_cursor* casilla_cursor;
	GUI_marcador_locked* casilla_lckd;
	Pieza_GUI* cual_pieza_locked;
	

	void generar_piezas();
	void actualizar_piezas();

public:

	Juego();
	void carga_partida_al_GUI(int); // partida = lista de movimientos
	void dibuja_juego();
	void dibujar_piezas();
	void incrementa_cursor(int inc_f, int inc_c);
	void mueve_pieza_locked();
	Pieza_GUI* get_pieza_locked();
	GUI_marcador_locked* get_casilla_locked();


	void generar_listado_datos_piezas_OFF(); // funcion auxilar para generar un listado de piezas. hasta que las de la parte lógica
	void listado_datos_piezas___un_movimiento(PIEZA_STRU pieza_a_mover);
	int  get_movimiento_actual();
	void cargar_partida(string nombre); // se carga a la propiedad "partida" desde la lista de partidas
	void cargar_partida_ejemplo(); // se carga a la propiedad "partida" desde la lista de partidas
	vector<GUI_movimiento> get_partida();
	void check_pieza_movible(); // verifica si la casilla del cursor tiene una pieza movible
	GUI_marcador_cursor* get_casilla_cursor();
	void reset_pieza_locked();

	//GUI_Tablero miTablero;

};

