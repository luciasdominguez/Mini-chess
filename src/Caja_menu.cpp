#include "Caja_menu.h"
#include "ETSIDI.h"
Caja_menu::Caja_menu()
{
	pared_izq.limite1.x = -30;
	pared_izq.limite1.y = -30;
	pared_izq.limite2.x = -30;
	pared_izq.limite2.y = 60;
	pared_izq.setColor(0, 0, 100);

	pared_dcha.limite1.x = 30;
	pared_dcha.limite1.y = -30;
	pared_dcha.limite2.x = 30;
	pared_dcha.limite2.y = 60;
	pared_dcha.setColor(0, 0, 100);

	suelo.limite1.x = -30;
	suelo.limite1.y = -5;
	suelo.limite2.x = 30;
	suelo.limite2.y = -5;
	suelo.setColor(0, 0, 100);


	techo.limite1.x = -30;
	techo.limite1.y = 35;
	techo.limite2.x = 30;
	techo.limite2.y = 35;
	techo.setColor(0, 0, 100);

}

void Caja_menu::dibuja()
{
	suelo.dibuja();
	techo.dibuja();
	pared_izq.dibuja();
	pared_dcha.dibuja();

	//dibujo del fondo
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,
		ETSIDI::getTexture("imagenes/tablero_menu.png").id);
	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 1); glVertex2d(-26, -2.5);
	glTexCoord2d(1, 1); glVertex2d(26, -2.5);
	glTexCoord2d(1, 0); glVertex2d(26, 32.5);
	glTexCoord2d(0, 0); glVertex2d(-26, 32.5);
	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
}