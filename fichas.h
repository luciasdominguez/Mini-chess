#pragma once
//#include "casillas.h"
#include "clases.h"
#include "gestor_movimientos.h"
#include "tablero.h"

enum class tipo {vacio, peon, torre, caballo, alfil, reina, rey};

class ficha
{
protected:
	friend class casilla;
	casilla* posicion;
	color c;
	const tipo t = tipo::vacio;

public:
	ficha(casilla* _pos, color _color);
	ficha() = default;

	ficha(const ficha& F) = default;

	color leer_color() { return c; }
	int pos_fila() { return posicion->leer_fila(); };
	int pos_columna() { return posicion->leer_columna(); };
	casilla leer_posicion() const { return *posicion; };
	tipo leer_tipo() { return t; }

	virtual void mover(casilla& casillas) {};

	friend class gestor_movimientos;
};


class peon : public ficha {

public:
	void mover(casilla& casillas) override;

private:
	bool ha_movido = false;
	const tipo t = tipo::peon;
};

class torre : public ficha {
public:
	void mover(casilla& casillas, const tablero& tablero);

private:
	const tipo t = tipo::torre;
};

class caballo : public ficha {
public:
	void mover(casilla& casillas) override;
};

class alfil : public ficha {
public:
	void mover(casilla& casillas, const tablero& tablero);

private:
	const tipo t = tipo::alfil;
};

class reina : public ficha {
public:
	void mover(casilla& casillas, const tablero& tablero);

private:
	const tipo t = tipo::reina;
};

class rey : public ficha {
public:
	void mover(casilla& casillas, const tablero& tablero);
	bool en_jaque(const casilla& c, const tablero& t); //Pide posición para poder comprobar también si se dará jaque en posiciones futuras
	void comprobar_jaque(bool& fin, bool& jaque, const tablero& tablero, int i, int columna, tipo t);

	rey() = default;
	rey(const rey&) = default;
	rey(const ficha& F) :
		t(tipo::rey)
	{
		ficha(F);
	}
	

private:
	const tipo t = tipo::rey;
};