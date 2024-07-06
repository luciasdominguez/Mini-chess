#pragma once
#include "Caja_menu.h" 
#pragma once
#include "Caja_menu.h" 

typedef enum opcion { MENU_INICIAL = 0, JUGAR, CONTROLES, SALIR };
class Mundo_menu
{
public:
	void tecla(unsigned char key, opcion& op_);
	void inicializa();

	void dibuja_menu();
	void dibuja_controles();

	float x_ojo;
	float y_ojo;
	float z_ojo;
	Caja_menu caja;
};
