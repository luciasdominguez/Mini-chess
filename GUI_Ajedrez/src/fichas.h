#pragma once
#include "casillas.h"
#include "clases.h"
//#include "gestor_movimientos.h"
#include "tablero.h"

//enum tipo { vacio=-1, peon_=1, torre, caballo, alfil, reina, rey ,vacia=-2};

class ficha
{
protected:
	friend class casilla;
	friend class tablero;
	casilla* posicion;
	ENUM_COLOR c;
	ENUM_TIPO t ;

public:
	ficha(casilla* _pos, ENUM_COLOR _color);
	ficha() = default;

	//ficha(const ficha& F) = default;


	virtual ENUM_COLOR leer_color() { return c; }
	int pos_fila() { return posicion->leer_fila(); };
	int pos_columna() { return posicion->leer_columna(); };
	void set_columna(int colm) { posicion->columna = colm; }
	void set_fila(int fil) { posicion->fila = fil; }
	void set_pos(casilla* cas) { posicion = cas; }
	void set_color(ENUM_COLOR color) { c = color; }
	void set_casilla(casilla* cas) { if (this) { posicion = cas; } }
	void set_tipo(ENUM_TIPO tipo) { t = tipo; }
	casilla leer_posicion() const { return *posicion; };
	virtual ENUM_TIPO leer_tipo() { return t; }
	//void set_tipo(tipo tipo_) { tipo::t=tipo_; }

	virtual bool mover(casilla& casillas, const tablero& tablero) { return false; };
	ficha& operator =(ficha& f1) {
		this->c = f1.c;
		this->posicion = f1.posicion;
		return *this;
	}
	friend class gestor_movimientos;
};

//class Vacia :public ficha {
//public:
//	Vacia(const ficha& F) : t(t_NO), ficha(F) {	}
//	Vacia() = default;
//	Vacia(const Vacia& v) {};
//	Vacia(casilla cas, ENUM_COLOR color) { posicion = &cas, c = color; t = t_NO; }
//	
//private:
//	ENUM_TIPO t = t_NO;
//	bool mover(casilla& casillas, const tablero& tablero) override{ return false; };
//};

class Peon : public ficha {

public:
	Peon(const Peon &p){}
	Peon(const ficha& F) : ficha(F) {	}
	Peon(ENUM_COLOR color) { c = color; }
	Peon(casilla cas, ENUM_COLOR color) { posicion = &cas, c = color;t= peon; }
	Peon() = default;
	bool mover(casilla& casillas, const tablero& tablero) override;

private:
	bool ha_movido = false;
	//ENUM_TIPO t = peon;
};

class Torre : public ficha {
public:
	bool mover(casilla& casillas, const tablero& tablero) override;
	Torre() = default;
	Torre(casilla cas, ENUM_COLOR color) { posicion = &cas, c = color; t=torre; }
	Torre(const ficha& F) : ficha(F) {	}
private:
//	ENUM_TIPO t = torre;
};

class Caballo : public ficha {
public:
	bool mover(casilla& casillas, const tablero& tablero) override;
	Caballo(const ficha& F) : ficha(F) {	}
	Caballo() = default;
	Caballo(casilla cas, ENUM_COLOR color) { posicion = &cas, c = color;t= caballo; }
private:
	//ENUM_TIPO t =caballo;
};

class Alfil : public ficha {
public:
	Alfil(const ficha& F) :  ficha(F) {	}
	Alfil() = default;
	Alfil(casilla cas, ENUM_COLOR color) { posicion = &cas, c = color;t= alfil; }
	bool mover(casilla& casillas, const tablero& tablero) override;
private:
	//ENUM_TIPO t = alfil;
};

class Reina : public ficha {
public:
	bool mover(casilla& casillas, const tablero& tablero) override;
	Reina(const ficha& F) :ficha(F) {	}
	Reina() = default;
	Reina(casilla cas, ENUM_COLOR color) { posicion = &cas, c = color; t=reina; }
private:
	//ENUM_TIPO t = reina;
};

class Rey : public ficha {
public:
	bool mover(casilla& casillas, const tablero& tablero) override;

	bool en_jaque(const casilla& c, const tablero& t); //Pide posición para poder comprobar también si se dará jaque en posiciones futuras
	void comprobar_jaque(bool& fin, bool& jaque, const tablero& tablero, int i, int columna, ENUM_TIPO t);
	bool en_jaque_mate(const casilla& c, const tablero& t);


	Rey() = default;
	Rey(const Rey&) = default;
	Rey(casilla cas, ENUM_COLOR color) { posicion = &cas, c = color; t=rey; }
	Rey(const ficha& F) 
	{
		rey;
		
	}


private:
	//ENUM_TIPO t = rey;
};