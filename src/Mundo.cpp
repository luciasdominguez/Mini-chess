#include "Mundo.h"
#include "freeglut.h"
#include <math.h>
#include "ETSIDI.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

void Mundo::rotarOjo()
{

}

void Mundo::dibuja()
{

		gluLookAt(x_ojo, y_ojo, z_ojo,
			0.0, y_ojo, 0.0, //NOTESE QUE HEMOS CAMBIADO ESTO 
			0.0, 1.0, 0.0); //PARA MIRAR AL CENTRO DE LA ESCENA 
		caja.dibuja();
		ETSIDI::setTextColor(1, 1, 1);
		ETSIDI::setFont("fuentes/Bitwise.ttf", 16);
		ETSIDI::printxy("MENU DE OPCIONES", -11, 17);

		ETSIDI::setTextColor(1, 1, 1);
		ETSIDI::setFont("fuentes/Bitwise.ttf", 12);
		ETSIDI::printxy("INFORMATICA INDUSTRIAL", 3, 17);

		ETSIDI::setTextColor(0, 0, 0);
		ETSIDI::setFont("fuentes/Bitwise.ttf", 20);
		ETSIDI::printxy("1- VAMOS A JUGAR", -8, 12);
		ETSIDI::printxy("2- CONTROLES", -8, 8);
		ETSIDI::printxy("3- SALIR", -8, 4);
	
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
