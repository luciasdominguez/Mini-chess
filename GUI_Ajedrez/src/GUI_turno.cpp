#include "GUI_turno.h"

GUI_turno::GUI_turno()
{
	string path_sprite_turno = "imagenes/selector_turno.png";
	const char* cstr = path_sprite_turno.c_str();
	calcula_Pos_turno(turno); // calcula posición del sprite en función de la fila y columna de la pieza
	sprite_turno = new SpriteSequence(cstr, 1, 1, 100, true, pos_x, pos_y, 2, 2);
}

void GUI_turno::dibuja_turno(ENUM_JUGADOR trn)
{
	glPushMatrix();
	glTranslated(0, 0, 1);

	// Dónde va el marcador de turno en coordenadas del tablero
	GUI_turno::calcula_Pos_turno(trn);

	sprite_turno->flip(false, false);
	sprite_turno->setPos(pos_x, pos_y);
	if ((trn == GRAVEDAD_N) || (trn == GRAVEDAD_B))
		sprite_turno->setSize(1.5, 4.5);
	else
		sprite_turno->setSize(8.5, 4.5);

	sprite_turno->draw();
	//fin del codigo incluido
	glPopMatrix();
}

void GUI_turno::calcula_Pos_turno(ENUM_JUGADOR trn)
{
	float inc_x = 0;
	float ref_x = -0.65, ref_y = -3.15;
	switch (trn)
	{
		case BLANCAS:		inc_x = 8.5;	break;
		case GRAVEDAD_B:	inc_x = 16.5;	break;
		case NEGRAS:		inc_x = 0;		break;
		case GRAVEDAD_N:	inc_x = -1.2;	break;
	}
	pos_x = ref_x + inc_x;
	pos_y = ref_y;
}