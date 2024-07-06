#pragma once
#include "Caja.h" 

typedef enum opcion { MENU_INICIAL = 0, JUGAR, CONTROLES, FIN, SALIR };
class Mundo
{
public: 
	Mundo() { inicializa(); };
	void tecla(unsigned char key);
	void inicializa();

	void dibuja_menu();
	void salir_menu();
	void dibuja_controles();
	void fin_partida() { op_ = FIN; };
	opcion get_opcion() { return op_; };

private:
	opcion op_ = MENU_INICIAL;
	bool exitFlag = false;

	float x_ojo;
	float y_ojo;
	float z_ojo;

	Caja caja;

};
