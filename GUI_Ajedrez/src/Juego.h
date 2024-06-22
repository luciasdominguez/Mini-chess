#pragma once
#include <vector>
#include "GUI_Tablero.h"
#include "GUI_Pieza2.h"
#include "GUI_marcador.h"
#include "GUI_jugada.h"
#include "GUI_almacenen_partidas.h"
#include "GUI_turno.h"
#include "listado_partidas.h"
#include "GUI_estado_P_J.h"
#include "fichas.h"

using std::vector;
using ETSIDI::Vector2D;

class Juego
{
	GUI_Tablero miTablero;
	GUI_turno* turno;
	GUI_estado_P_J* estado_Partidas_Jugadas;
	GUI_gestor_partidas* gestor_de_partidas;
	GUI_partida partida_actual; // una partida es una lista de jugadas.

	vector<PIEZA_STRU> todas_piezas_LISTA; // los valores se actualizarán en la parte de logica
	vector<Pieza_GUI> todas_piezas_GUI;
	GUI_marcador_cursor* casilla_cursor;
	GUI_marcador_locked* casilla_lckd;
	Pieza_GUI* cual_pieza_locked;
	//T_listado_partidas listado_partidas;


	void generar_piezas();
	void actualizar_piezas();

protected:
	GUI_jugada jugada_ultima;
	GUI_jugada jugada_ahora;
public:
	Juego();
	void carga_partida_al_GUI(int); // partida = lista de movimientos
	GUI_partida get_partida_actual();
	void guarda_partida_actual();
	void dibuja_juego();
	void dibujar_piezas();
	void incrementa_cursor(int inc_f, int inc_c);
	void mueve_pieza_locked(int n_movimientos);
	Pieza_GUI* get_pieza_locked();
	GUI_marcador_locked* get_casilla_locked();
	void avanza_siguiente_turno();  // calcula el turno siguiente
	void turno_();  // turno actual
	void dibuja_lista_partidas();

	void generar_listado_datos_piezas_OFF(); // funcion auxilar para generar un listado de piezas. hasta que las de la parte lógica
	void listado_datos_piezas___un_movimiento(PIEZA_STRU pieza_a_mover);
	ENUM_JUGADOR get_jugador_actual();
	void cargar_partida(string nombre); // se carga a la propiedad "partida" desde la lista de partidas
	void cargar_partida_ejemplo(); // se carga a la propiedad "partida" desde la lista de partidas
	GUI_partida get_partida();
	void check_pieza_movible(); // verifica si la casilla del cursor tiene una pieza movible
	GUI_marcador_cursor* get_casilla_cursor();
	void reset_pieza_locked();
	ESTADO_GENERAL get_selector_partidas_jugadas();
	void cambia_selector_partidas_jugadas();
	T_listado_partidas get_listado_partidas();
	GUI_gestor_partidas get_almacen_partidas();


	bool comprobar_movimiento();



	//GUI_Tablero miTablero;
	friend GUI_gestor_partidas;
	friend GUI_Tablero;
};
