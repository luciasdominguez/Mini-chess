#pragma once

#include "casillas.h"
#include "clases.h"
//#include "tablero.h"
//#include "gestor_movimientos.h"
#include "tablero.h"

enum class tipo {vacio, peon, torre, caballo, alfil, reina, rey};

class ficha
{
protected:
	friend class casilla;
	friend class tablero;
	//friend class gestor_movimientos;

	casilla* posicion;
	ENUM_COLOR c;
	const tipo t = tipo::vacio;

public:
	ficha() = default;
	ficha(casilla* _pos, ENUM_COLOR _color);
	void set_fila(int f) { posicion->fila= f; }
	void set_columna(int c) { posicion->columna = c; }
	ENUM_COLOR leer_color() { return c; }
	int pos_fila() { return posicion->leer_fila(); };
	int pos_columna() { return posicion->leer_columna(); };
	tipo leer_tipo() { return t; }

	virtual bool mover(casilla& casillas) {};

	friend class gestor_movimientos;
	friend class GUI_jugada;
	friend class Juego;
};


class Peon : public ficha {

public:
	friend class tablero;
	
	Peon() = default;

	bool mover(casilla& casillas) override;

private:
	bool ha_movido = false;
	const tipo t = tipo::peon;
	friend class Juego;
};

class Torre : public ficha {
public:
	bool mover(casilla& casillas) override;
	Torre() = default;
private:
	const tipo t = tipo::torre;
};

class Caballo : public ficha {
public:
	Caballo() = default;
	bool mover(casilla& casillas) override;
};

class Alfil : public ficha {
public:
	bool mover(casilla& casillas) override;
	Alfil() = default;
private:
	const tipo t = tipo::alfil;
};

class Reina : public ficha {
public:
	bool mover(casilla& casillas) override;
	Reina() = default;
private:
	const tipo t = tipo::reina;
};

class Rey : public ficha {
public:
	Rey() = default;
	bool mover(casilla& casillas, const tablero& tablero);
	bool en_jaque(const casilla& c, const tablero& t); //Pide posición para poder comprobar también si se dará jaque en posiciones futuras
	void comprobar_jaque(bool& fin, bool& jaque, const tablero& tablero, int i, int columna, tipo t);

private:
	const tipo t = tipo::rey;
};