#pragma once
#include "ETSIDI.h"
#include "GUI_Pieza2.h"
enum ENUM_ESTADO_CURSOR { OFF=0, ON};
enum ENUM_ESTADO_LOCKED { TRANS = 0, NARANJA, ROJO };


class GUI_marcador
{

protected:
	ENUM_FILA fila = f1;
	ENUM_COLUMNA columna = A;
	float tam_casilla = 1.95;
	float pos_x{}, pos_y{}; /// posición según escala del sprite
	SpriteSequence* sprite_1;
	SpriteSequence* sprite_2;
	ENUM_ESTADO_CURSOR estado_marcador = OFF;
public:
	GUI_marcador() = default;
	GUI_marcador(ENUM_FILA, ENUM_COLUMNA);
	ENUM_ESTADO_CURSOR get_estado();
	void dibuja_sprite();
	void set_posicion(ENUM_FILA, ENUM_COLUMNA);
	void calculaPos();
	ENUM_FILA get_fila();
	ENUM_COLUMNA get_columna();

	friend class Juego;
};
///////////////////////////////////////////////////////
//////////////////////////////////////////
class GUI_marcador_cursor: public GUI_marcador
{

public:
	GUI_marcador_cursor(ENUM_FILA f, ENUM_COLUMNA c);
	void incrementa_posicion(int inc_x, int inc_y);
	void switch_cursor_casilla();
	void reset_cursor_casilla();
};
///////////////////////////////////////
///////////////////////////////
class GUI_marcador_locked : public GUI_marcador
{
	bool Can_Lock_casilla = false; // la casilla puede pasar al estado Locked
	Pieza_GUI* pieza_Locked = nullptr;  // a que pieza retiene la casilla
	ENUM_ESTADO_LOCKED estado_locked = TRANS;
public:
	GUI_marcador_locked( ENUM_FILA, ENUM_COLUMNA);
	void set_estado_locked(ENUM_ESTADO_LOCKED, Pieza_GUI*);


	void captura_pieza();   /////////?????????????
	void set_Can_Lock(bool);
	bool get_Can_Lock();
	void reset_pieza_locked();
	void dibuja_sprite();
	ENUM_ESTADO_LOCKED get_estado_locked();
};

