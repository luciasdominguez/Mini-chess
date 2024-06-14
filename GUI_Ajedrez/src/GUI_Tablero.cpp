#include "GUI_Tablero.h"

GUI_Tablero::GUI_Tablero()
{
}

void GUI_Tablero::dibuja_tablero()
{
	//dibujo del tablero
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,
		ETSIDI::getTexture("imagenes/tablero.png").id);
	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);

	glTexCoord2d(0, 1);glVertex2d(posicion_tablero.x, posicion_tablero.y);
	glTexCoord2d(1, 1);glVertex2d(posicion_tablero.x + tamaño_tablero.x, posicion_tablero.y);
	glTexCoord2d(1, 0);glVertex2d(posicion_tablero.x + tamaño_tablero.x, posicion_tablero.y + tamaño_tablero.y);
	glTexCoord2d(0, 0);glVertex2d(posicion_tablero.x, posicion_tablero.y + tamaño_tablero.y);

	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
}




