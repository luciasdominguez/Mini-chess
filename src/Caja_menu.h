#pragma once
#include "Pared_menu.h" 

class Caja_menu
{
private:
	Pared_menu suelo;
	Pared_menu techo;
	Pared_menu pared_izq;
	Pared_menu pared_dcha;

public:
	void dibuja();
	Caja_menu();
};