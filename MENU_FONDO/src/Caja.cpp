#include "Caja.h"

Caja::Caja()
{
	pared_izq.limite1.x = -10;
	pared_izq.limite1.y = 0;
	pared_izq.limite2.x = -10;
	pared_izq.limite2.y = 15;
	pared_izq.setColor(0, 150, 0);

	pared_dcha.limite1.x = 10;
	pared_dcha.limite1.y = 0;
	pared_dcha.limite2.x = 10;
	pared_dcha.limite2.y = 15;
	pared_dcha.setColor(0, 150, 0);

	suelo.limite1.x = -10;
	suelo.limite1.y = 0;
	suelo.limite2.x = 10;
	suelo.limite2.y = 0;
	suelo.setColor(0, 100, 0);


	techo.limite1.x = -10;
	techo.limite1.y = 15;
	techo.limite2.x = 10;
	techo.limite2.y = 15;
	techo.setColor(0, 100, 0);
}

void Caja::dibuja()
{
	suelo.dibuja();
	techo.dibuja();
	pared_izq.dibuja();
	pared_dcha.dibuja();
}