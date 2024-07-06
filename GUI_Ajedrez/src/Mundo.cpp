#include "Mundo.h"
#include "freeglut.h"
#include <math.h>
#include "ETSIDI.h"
#include <iostream>
#include <stdlib.h>

using namespace std;



void Mundo::salir_menu() //Si exitFlag es TRUE, se termina de ejecutar el programa
{
	if (exitFlag)
		glutDestroyWindow(glutGetWindow());  // Destruir la ventana actual
}

void Mundo::dibuja_menu()
{
	gluLookAt(x_ojo, y_ojo, z_ojo,
		0.0, y_ojo, 0.0, 
		0.0, 1.0, 0.0); 

	caja.dibuja();

	ETSIDI::setTextColor(1, 1, 1);
	ETSIDI::setFont("fuentes/Bitwise.ttf", 16);
	ETSIDI::printxy("AJEDREZ GRAVITATORIO", -10, 36);
	ETSIDI::printxy("MENU DE OPCIONES", -8, 33.5);

	ETSIDI::setTextColor(1, 1, 1);
	ETSIDI::setFont("fuentes/Bitwise.ttf", 12);
	ETSIDI::printxy("INFORMATICA INDUSTRIAL", 3, -5);

	ETSIDI::setTextColor(0, 0, 0);
	ETSIDI::setFont("fuentes/Bitwise.ttf", 20);
	ETSIDI::printxy("1- VAMOS A JUGAR", -10, 20);
	ETSIDI::printxy("2- COMO JUGAR", -10, 16);
	ETSIDI::printxy("3- SALIR", -10, 12);
	
}

void Mundo::dibuja_controles()
{
	gluLookAt(x_ojo, y_ojo, z_ojo,
		0.0, y_ojo, 0.0,
		0.0, 1.0, 0.0);

	ETSIDI::setTextColor(1, 1, 1);
	ETSIDI::setFont("fuentes/Bitwise.ttf", 16);
	ETSIDI::printxy("ESTOS SON LOS CONTROLES", -5, 10);
	ETSIDI::printxy("PARA VOLVER AL MENU PULSE 4", -5, 6);
}

void Mundo::inicializa()
{
	x_ojo = 0;
	y_ojo = 7.5;
	z_ojo = 30;
}

void Mundo::tecla(unsigned char key)
{
	if (key == '1' && op_ == MENU_INICIAL)
		op_ = JUGAR;
	
	if (key == '2' && op_ == MENU_INICIAL)
		op_ = CONTROLES;

	if (key == '3' && op_ == MENU_INICIAL)
		exitFlag = true;

	if (key == '4' && op_ != MENU_INICIAL)
		op_ = MENU_INICIAL;

	salir_menu(); //Si exitFlag es TRUE, se termina de ejecutar el programa
}
