#pragma once
#include "Caja.h" 

class Mundo
{
public: 
	void tecla(unsigned char key);
	void inicializa();
	void rotarOjo();
	void mover();
	void dibuja();

	float x_ojo;
	float y_ojo;
	float z_ojo;
	Caja caja;

	Pared plataforma;

};
