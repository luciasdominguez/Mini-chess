#pragma once
#include "ETSIDI.h"
#include <string>
using namespace ETSIDI;

enum ESTADO_GENERAL { en_seleccion_partida = 0, en_jugadas};

class GUI_estado_P_J
{
	ESTADO_GENERAL estado_partidas_o_jugadas = en_seleccion_partida;
	float pos_x{}, pos_y{}; /// posición según escala del sprite
	void calcula_Pos_Est_general(ESTADO_GENERAL est_gen);

protected:
	SpriteSequence* sprite_estado_general;
public:
	GUI_estado_P_J();
	ESTADO_GENERAL get_partidas_o_jugadas();
	void set_partidas_o_jugadas(ESTADO_GENERAL p_g);
	void dibuja_seleccion_partida();


};

