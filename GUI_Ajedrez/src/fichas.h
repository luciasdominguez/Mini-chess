#pragma once
#include "casillas.h"
#include "clases.h"
//#include "gestor_movimientos.h"
#include "tablero.h"

enum class tipo { vacio, peon, torre, caballo, alfil, reina, rey };

class ficha
{
protected:
	friend class casilla;
	friend class tablero;
	casilla* posicion;
	ENUM_COLOR c;
	const tipo t = tipo::vacio;

public:
	ficha(casilla* _pos, ENUM_COLOR _color);
	ficha() = default;

	ficha(const ficha& F) = default;


	ENUM_COLOR leer_color() { return c; }
	int pos_fila() { return posicion->leer_fila(); };
	int pos_columna() { return posicion->leer_columna(); };
	casilla leer_posicion() const { return *posicion; };
	tipo leer_tipo() { return t; }

	virtual bool mover(casilla& casillas, const tablero& tablero) { return false; };
	ficha& operator =(ficha& f1) {
		this->c = f1.c;
		this->posicion = f1.posicion;
		return *this;
	}
	friend class gestor_movimientos;
};


class Peon : public ficha {

public:
	
	bool mover(casilla& casillas, const tablero& tablero) override;

private:
	bool ha_movido = false;
	const tipo t = tipo::peon;
};

class Torre : public ficha {
public:
	bool mover(casilla& casillas, const tablero& tablero) override;

private:
	const tipo t = tipo::torre;
};

class Caballo : public ficha {
public:
	bool mover(casilla& casillas, const tablero& tablero) override;
};

class Alfil : public ficha {
public:
	bool mover(casilla& casillas, const tablero& tablero) override;

private:
	const tipo t = tipo::alfil;
};

class Reina : public ficha {
public:
	bool mover(casilla& casillas, const tablero& tablero) override;

private:
	const tipo t = tipo::reina;
};

class Rey : public ficha {
public:
	bool mover(casilla& casillas, const tablero& tablero) override;
	bool en_jaque(const casilla& c, const tablero& t); //Pide posición para poder comprobar también si se dará jaque en posiciones futuras
	void comprobar_jaque(bool& fin, bool& jaque, const tablero& tablero, int i, int columna, tipo t);

	Rey() = default;
	Rey(const Rey&) = default;
	Rey(const ficha& F) :
		t(tipo::rey)
	{
		ficha(/*F*/);
	}


private:
	const tipo t = tipo::rey;
};