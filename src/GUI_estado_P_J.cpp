#include "GUI_estado_P_J.h"

void GUI_estado_P_J::calcula_Pos_Est_general(ESTADO_GENERAL est_gen)
{
	float inc_y = 0;
	float ref_x = -9.5, ref_y = 13.7;
	switch (est_gen)
	{
	case modo_seleccion_partida:	
		inc_y = 0;	break;
	case modo_juego:			
		inc_y = -12.4;	break;
	}
	pos_x = ref_x;
	pos_y = ref_y+ inc_y;
}

GUI_estado_P_J::GUI_estado_P_J()
{
	string path_sprite_estado_general = "imagenes/selector_partida.png";
	const char* cstr = path_sprite_estado_general.c_str();
	calcula_Pos_Est_general(estado_partidas_o_jugadas); // calcula posición del sprite en función de la fila y columna de la pieza
	sprite_estado_general = new SpriteSequence(cstr, 1, 1, 100, true, pos_x, pos_y, 13, 12);
}

ESTADO_GENERAL GUI_estado_P_J::get_partidas_o_jugadas()
{
	return estado_partidas_o_jugadas;
}

void GUI_estado_P_J::set_partidas_o_jugadas(ESTADO_GENERAL p_g)
{
	estado_partidas_o_jugadas = p_g;
	dibuja_seleccion_partida();
}

void GUI_estado_P_J::dibuja_seleccion_partida()
{
	glPushMatrix();
	glTranslated(0, 0, 1);

	// Dónde va el marcador del estado general en coordenadas del tablero
	GUI_estado_P_J::calcula_Pos_Est_general(estado_partidas_o_jugadas);

	sprite_estado_general->flip(false, false);
	sprite_estado_general->setPos(pos_x, pos_y);
	sprite_estado_general->draw();

	//fin del codigo incluido
	glPopMatrix();

}
