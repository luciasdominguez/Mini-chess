#pragma once
//IMPLEMENTACION DE LA RELACION DE COMPOSICION 
#include "Pared.h" 

class Caja
{
private:
	
	Pared suelo;
	Pared techo;
	Pared pared_izq;
	Pared pared_dcha;

public:
	void dibuja();
	Caja();

};