#pragma once
//IMPLEMENTACION DE LA RELACION DE COMPOSICION 
#include "Pared.h" 

class Caja
{
public:
	Caja();
	Pared suelo;
	Pared techo;
	Pared pared_izq;
	Pared pared_dcha;

	void dibuja();

};