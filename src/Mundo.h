#pragma once
#include "Caja.h" 

typedef enum opcion { MENU_INICIAL = 0, JUGAR, CONTROLES, SALIR };
class Mundo
{
public: 
	void tecla(unsigned char key, opcion& op_);
	void inicializa();

	void dibuja_menu();
	void dibuja_controles();
	//void mover();

	float x_ojo;
	float y_ojo;
	float z_ojo;
	Caja caja;
};
