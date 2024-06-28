#include "Mundo.h"
#include "freeglut.h"
#include <math.h>

void Mundo::rotarOjo()
{

}

void Mundo::dibuja()
{
	gluLookAt(x_ojo, y_ojo, z_ojo,
		0.0, y_ojo, 0.0, //NOTESE QUE HEMOS CAMBIADO ESTO 
		0.0, 1.0, 0.0); //PARA MIRAR AL CENTRO DE LA ESCENA 
	caja.dibuja();

	//plataforma.dibuja();

}

void Mundo::mover()
{

}

void Mundo::inicializa()
{
	x_ojo = 0;
	y_ojo = 7.5;
	z_ojo = 30;

	plataforma.limite1.x = -5.0f;
	plataforma.limite2.x = 5.0f;
	plataforma.limite1.y = 9.0f;
	plataforma.limite2.y = 9.0f;
}

void Mundo::tecla(unsigned char key)
{

}
