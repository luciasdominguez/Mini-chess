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

///////////////////////////
////////// GUI_jaque
//////////////////////


GUI_jaque::GUI_jaque()
{
	// Hacer y cambiar sprite jaque
	string path_sprite_jaque = "imagenes/jaque.png";
	pos_x = 4;
	pos_y = 1.4;
	ver_jaque = false;
	const char* cstr = path_sprite_jaque.c_str();
	sprite_jaque = new SpriteSequence(cstr, 1, 1, 100, true, pos_x, pos_y, 2, 2);
	sprite_jaque->setSize(0, 0);
}

void GUI_jaque::dibuja_jaque()
{
	glPushMatrix();
	glTranslated(0, 0, 1);

	sprite_jaque->flip(false, false);
	sprite_jaque->setPos(pos_x, pos_y);
	if (ver_jaque)
		sprite_jaque->setSize(7, 2);
	else
		sprite_jaque->setSize(0, 0);

	sprite_jaque->draw();
	//fin del codigo incluido
	glPopMatrix();
}

void GUI_jaque::set_ver_jaque(bool ver_j)
{
	ver_jaque = ver_j;
}

bool GUI_jaque::get_ver_jaque()
{
	return ver_jaque;
}

///////////////////////////
////////// GUI_jaque_mate
//////////////////////

GUI_jaque_mate::GUI_jaque_mate()
{
	string path_sprite_jaque_mate = "imagenes/jaque_mate.png";
	pos_x = 4;
	pos_y = 1.4;
	ver_jaque_mate = false;
	const char* cstr = path_sprite_jaque_mate.c_str();
	sprite_jaque_mate = new SpriteSequence(cstr, 1, 1, 100, true, pos_x, pos_y, 2, 2);
	sprite_jaque_mate->setSize(0, 0);
}

void GUI_jaque_mate::dibuja_jaque_mate()
{
	glPushMatrix();
	glTranslated(0, 0, 1);

	sprite_jaque_mate->flip(false, false);
	sprite_jaque_mate->setPos(pos_x, pos_y);
	if (ver_jaque_mate)
		sprite_jaque_mate->setSize(7, 2);
	else
		sprite_jaque_mate->setSize(0, 0);

	sprite_jaque_mate->draw();
	//fin del codigo incluido
	glPopMatrix();
}

void GUI_jaque_mate::set_ver_jaque_mate(bool ver)
{
	ver_jaque_mate = ver;
}

bool GUI_jaque_mate::get_ver_jaque_mate()
{
	return ver_jaque_mate;
}
