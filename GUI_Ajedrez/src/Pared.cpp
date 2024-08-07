#include "Pared.h"
#include "freeglut.h"
Pared::Pared()
{
	rojo = 0;
	verde = 0;
	azul = 0;
}
void Pared::setColor(unsigned char r, unsigned char g, unsigned char b) { rojo = r, verde = g, azul = b; }

void Pared::dibuja()
{
	glDisable(GL_LIGHTING);
	glColor3ub(rojo, verde, azul);
	glBegin(GL_POLYGON);
	glVertex3d(limite1.x, limite1.y, 10);
	glVertex3d(limite2.x, limite2.y, 10);
	glVertex3d(limite2.x, limite2.y, -10);
	glVertex3d(limite1.x, limite1.y, -10);
	glEnd();
	glEnable(GL_LIGHTING);
}
