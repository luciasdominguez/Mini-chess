#include "Mundo.h"
#include "freeglut.h"
#include <math.h>
#include "ETSIDI.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

bool exitFlag = false;

void salir_menu() //Si exitFlag es TRUE, se termina de ejecutar el programa
{
	if (exitFlag)
		glutDestroyWindow(glutGetWindow());  // Destruir la ventana actual
}

void Mundo::dibuja_menu()
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
	ETSIDI::printxy("1- VAMOS A JUGAR", -8, 11);
	ETSIDI::printxy("2- CONTROLES", -8, 8);
	ETSIDI::printxy("3- SALIR", -8, 5);
	
}

void Mundo::dibuja_controles()
{
	gluLookAt(x_ojo, y_ojo, z_ojo,
		0.0, y_ojo, 0.0,
		0.0, 1.0, 0.0);
	ETSIDI::setTextColor(1, 1, 1);
	ETSIDI::setFont("fuentes/Bitwise.ttf", 14);
	ETSIDI::printxy("ESTOS SON LOS CONTROLES", -12, 17);
	ETSIDI::setTextColor(100, 0, 0);
	ETSIDI::setFont("fuentes/Bitwise.ttf", 12);
	ETSIDI::printxy("PARA VOLVER AL MENU PULSE 4", -6, -2);
	//escritura de los controles
	ETSIDI::setTextColor(50, 50, 0);
	ETSIDI::setFont("fuentes/Bitwise.ttf", 12);
	ETSIDI::printxy("S: cargar partida O guardar y salir", -14, 16);
	ETSIDI::printxy("N: genera partida con posiciones iniciales", -14, 15);
	ETSIDI::printxy("E: cargar partida ejemplo", -14, 14);
	ETSIDI::printxy("J: modo juego", -14, 13);
	ETSIDI::printxy("P: seleccionar partida", -14, 12);
	ETSIDI::printxy("(guion): retroceder en la jugada", -14, 11);
	ETSIDI::printxy("+: avanzar en la jugada", -14, 10);
	ETSIDI::printxy("5: activar cursor", -14, 9);
	ETSIDI::printxy("(punto): selecciona pieza", -14, 8);
	ETSIDI::printxy("0: ejecutar movimiento", -14, 7);
	ETSIDI::printxy("(asterisco): juega la gravedad", -14, 6);
	ETSIDI::printxy("(espacio): poner piezas en el almacen", -14, 5);
	ETSIDI::printxy("8, 9, 6, 3, 2, 1, 4, 7: mover las piezas", -14, 4);
	
}

void Mundo::inicializa()
{
	x_ojo = 0;
	y_ojo = 7.5;
	z_ojo = 30;
}

void Mundo::tecla(unsigned char key, opcion& op_)
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
