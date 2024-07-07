#pragma once
#include "casillas.h"
#include "clases.h"
#include "tablero.h"


class ficha
{
protected:
	friend class casilla;
	friend class tablero;
	friend class gestor_movimientos;

	casilla* posicion;

	ENUM_COLOR campo_color;
	ENUM_TIPO campo_tipo ;
	ENUM_PIEZA campo_pieza;

	PIEZA_STRU pieza;

	bool ha_movido = false;

public:
	ficha(casilla* _pos, ENUM_COLOR _color);
	ficha() = default;

	virtual ENUM_COLOR leer_color() { return campo_color; }
	int pos_fila() { return posicion->leer_fila(); };
	int pos_columna() { return posicion->leer_columna(); };
	casilla leer_posicion() const { return *posicion; };
	virtual ENUM_TIPO leer_tipo() { return campo_tipo; }
	virtual ENUM_PIEZA leer_pieza() { return campo_pieza; }

	void set_columna(int colm) { posicion->columna = colm; }
	void set_fila(int fil) { posicion->fila = fil; }
	void set_pos(casilla* cas) { posicion = cas; }
	void set_color(ENUM_COLOR color) { campo_color = color; }
	void set_casilla(casilla* cas) { if (this) { posicion = cas; } }
	void set_tipo(ENUM_TIPO tipo) { campo_tipo = tipo; }
	void set_pieza(ENUM_PIEZA pieza) { if (this) { campo_pieza = pieza; } }
	

	virtual bool mover(casilla& casillas, const tablero& tablero) { return false; };
	void mod_ha_movido() { this->ha_movido = true; };

	ficha& operator =(ficha& f1) {
		this->campo_color = f1.campo_color;
		this->posicion = f1.posicion;
		return *this;
	}
	
};

class Peon : public ficha {

public:
	Peon(const ficha& F) : ficha(F) {	}
	Peon(ENUM_COLOR color) { campo_color = color; }
	Peon(casilla cas, ENUM_COLOR color) { posicion = &cas, campo_color = color;campo_tipo= peon; }
	Peon() = default;
	Peon(const Peon&) = default;

	bool mover(casilla& casillas, const tablero& tablero) override;
	
	
};

class Torre : public ficha {
public:
	bool mover(casilla& casillas, const tablero& tablero) override;

	Torre() = default;
	Torre(const Torre&) = default;
	Torre(casilla cas, ENUM_COLOR color) { posicion = &cas, campo_color = color; campo_tipo=torre; }
	Torre(const ficha& F) : ficha(F) {	}
};

class Caballo : public ficha {
public:
	bool mover(casilla& casillas, const tablero& tablero) override;

	Caballo(const ficha& F) : ficha(F) {	}
	Caballo() = default;
	Caballo(const Caballo&) = default;
	Caballo(casilla cas, ENUM_COLOR color) { posicion = &cas, campo_color = color;campo_tipo= caballo; }
};

class Alfil : public ficha {
public:
	Alfil(const ficha& F) :  ficha(F) {	}
	Alfil() = default;
	Alfil(const Alfil&) = default;
	Alfil(casilla cas, ENUM_COLOR color) { posicion = &cas, campo_color = color;campo_tipo= alfil; }

	bool mover(casilla& casillas, const tablero& tablero) override;
};

class Reina : public ficha {
public:
	bool mover(casilla& casillas, const tablero& tablero) override;

	Reina(const ficha& F) :ficha(F) {	}
	Reina() = default;
	Reina(const Reina&) = default;
	Reina(casilla cas, ENUM_COLOR color) { posicion = &cas, campo_color = color; campo_tipo=reina; }
};

class Rey : public ficha {
public:
	bool mover(casilla& casillas, const tablero& tablero) override;

	bool en_jaque(const casilla& c, const tablero& t); //Pide posición para poder comprobar también si se dará jaque en posiciones futuras
	void comprobar_jaque(bool& fin, bool& jaque, const tablero& tablero, int i, int columna, ENUM_TIPO t);
	bool en_jaque_mate(const casilla& c, const tablero& t);


	Rey() = default;
	Rey(const Rey&) = default;
	Rey(casilla cas, ENUM_COLOR color) { posicion = &cas, campo_color = color; campo_tipo = rey; };
	Rey(const ficha& F)
	{
		rey;
	};

	Rey(ficha* F) : ficha(*F)
	{ campo_tipo = rey; }
};