#include "Caja.h"
#include "ETSIDI.h"
Caja::Caja()
{
	pared_izq.limite1.x = -10;
	pared_izq.limite1.y = 0;
	pared_izq.limite2.x = -10;
	pared_izq.limite2.y = 15;
	pared_izq.setColor(0, 0, 100);

	pared_dcha.limite1.x = 10;
	pared_dcha.limite1.y = 0;
	pared_dcha.limite2.x = 10;
	pared_dcha.limite2.y = 15;
	pared_dcha.setColor(0, 0, 100);

	suelo.limite1.x = -10;
	suelo.limite1.y = 0;
	suelo.limite2.x = 10;
	suelo.limite2.y = 0;
	suelo.setColor(0, 0, 100);


	techo.limite1.x = -10;
	techo.limite1.y = 15;
	techo.limite2.x = 10;
	techo.limite2.y = 15;
	techo.setColor(0, 0, 100);

}

void Caja::dibuja()
{
	suelo.dibuja();
	techo.dibuja();
	pared_izq.dibuja();
	pared_dcha.dibuja();

	//dibujo del fondo
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,
		ETSIDI::getTexture("imagenes/tablero.png").id);
	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 1); glVertex2d(-10, 0);
	glTexCoord2d(1, 1); glVertex2d(10, 0);
	glTexCoord2d(1, 0); glVertex2d(10, 15);
	glTexCoord2d(0, 0); glVertex2d(-10, 15);
	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
}