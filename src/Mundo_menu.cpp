#include "Mundo_menu.h"
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

void Mundo_menu::dibuja_menu()
{
	gluLookAt(x_ojo, y_ojo, z_ojo,
		0.0, y_ojo, 0.0,
		0.0, 1.0, 0.0);

	caja.dibuja();

	ETSIDI::setTextColor(1, 1, 1);
	ETSIDI::setFont("fuentes/SwanseaBold.ttf", 16);
	ETSIDI::printxy("AJEDREZ GRAVITATORIO", -10, 36);
	ETSIDI::printxy("MENU DE OPCIONES", -8, 33.5);

	ETSIDI::setTextColor(1, 1, 1);
	ETSIDI::setFont("fuentes/SwanseaBold.ttf", 15);
	ETSIDI::printxy("INFORMATICA INDUSTRIAL", 3, -5);

	ETSIDI::setTextColor(0, 0, 0);
	ETSIDI::setFont("fuentes/SwanseaBold.ttf", 15);
	ETSIDI::printxy("1- VAMOS A JUGAR", -10, 20);
	ETSIDI::printxy("2- COMO JUGAR", -9, 16);
	ETSIDI::printxy("3- SALIR", -6, 12);
}

void Mundo_menu::dibuja_controles()
{
	gluLookAt(x_ojo, y_ojo, z_ojo,
		0.0, y_ojo, 0.0,
		0.0, 1.0, 0.0);
	ETSIDI::setTextColor(1, 1, 1);
	ETSIDI::setFont("fuentes/SwanseaBold.ttf", 14);
	ETSIDI::printxy("CONTROLES:", -12, 29);
	ETSIDI::setTextColor(100, 0, 0);
	ETSIDI::setFont("fuentes/SwanseaBold.ttf", 14);
	ETSIDI::printxy("PARA VOLVER AL MENU PULSE M", -2, 0);
	//escritura de los controles
	ETSIDI::setTextColor(50, 50, 0);
	ETSIDI::setFont("fuentes/SwanseaBold.ttf", 14);
	ETSIDI::printxy("S: cargar partida O guardar y salir", -16, 26);
	ETSIDI::printxy("N: genera partida con posiciones iniciales", -16, 24);
	ETSIDI::printxy("J: modo jugar", -16, 22);
	ETSIDI::printxy("P: modo seleccionar partida", -16, 20);
	ETSIDI::printxy("(guion): retroceder en la jugada", -16, 18);
	ETSIDI::printxy("+: avanzar en la jugada", -16, 16);
	ETSIDI::printxy("5: activar/desactivar cursor", -16, 14);
	ETSIDI::printxy("(punto): seleccionar pieza", -16, 12);
	ETSIDI::printxy("0: confirmar movimiento", -16, 10);
	ETSIDI::printxy("(asterisco): juega la gravedad", -16, 8);
	ETSIDI::printxy("1, 2, 3, 4, 6, 7, 8, 9: mover las piezas (según keypad)", -16, 6);

}

void Mundo_menu::inicializa()
{
	x_ojo = 0;
	y_ojo = 7.5;
	z_ojo = 30;
}

void Mundo_menu::tecla(unsigned char key, opcion& op_)
{
	if (key == '1' && op_ == MENU_INICIAL)
		op_ = JUGAR;

	else if (key == '2' && op_ == MENU_INICIAL)
		op_ = CONTROLES;

	else if (key == '3' && op_ == MENU_INICIAL)
		exitFlag = true;

	else if (key == 'm' && op_ != MENU_INICIAL)
		op_ = MENU_INICIAL;

	salir_menu(); //Si exitFlag es TRUE, se termina de ejecutar el programa
}
