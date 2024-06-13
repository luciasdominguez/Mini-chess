#pragma once
#include "clases.h"


enum class color { blanca, negra };
enum class tipo{ vacio, peon, torre, caballo, alfil, reina, rey};

class ficha {
protected:
	int pos_fil; ///Fila en la que está la ficha
	int pos_col; ///Columna en la que está la ficha
	color c;
	const tipo t = tipo::vacio;

public:
	ficha(int fila, int columna, color color_ficha);
	
	tipo leer_tipo() const { return t; };
	color leer_color() const { return c; };

	virtual void mover(casilla& casillas) {};

	friend class Gestor_Movimientos;
};

class peon : public ficha{

public:
	void mover(casilla& casillas) override;

private:
	bool ha_movido = false;
	const tipo t = tipo::peon;
};

class torre : public ficha {
public:
	void mover(casilla& casillas) override;

private:
	const tipo t = tipo::torre;
};

class caballo : public ficha {
public:
	void mover(casilla& casillas) override;
};

class alfil : public ficha {
public:
	void mover(casilla& casillas) override;

private:
	const tipo t = tipo::alfil;
};

class reina : public ficha {
public:
	void mover(casilla& casillas) override;

private:
	const tipo t = tipo::reina;
};

class rey : public ficha {
public:
	void mover(casilla& casillas) override;
	bool en_jaque(const casilla& c, const tablero& t); //Pide posición para poder comprobar también si se dará jaque en posiciones futuras


private:
	const tipo t = tipo::rey;
};