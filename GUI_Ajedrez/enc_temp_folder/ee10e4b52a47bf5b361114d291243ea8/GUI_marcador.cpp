#include "GUI_marcador.h"

GUI_marcador::GUI_marcador(ENUM_FILA fl, ENUM_COLUMNA cl)
{
	fila = fl; columna = cl;
	estado_marcador = OFF;
}


void GUI_marcador::calculaPos()
{
	float ref_x = 0, ref_y = 3.6, inc_casilla = 1.9;// referencia de casilla inferior izquierda
	pos_x = ref_x + (8 - (int)fila) * inc_casilla +inc_casilla * 0.05;
	pos_y = ref_y + (((int)columna) - 1) * inc_casilla+ inc_casilla * -0.05;

}


ENUM_FILA GUI_marcador::get_fila()
{
	return fila;
}

ENUM_COLUMNA GUI_marcador::get_columna()
{
	return columna;
}


void GUI_marcador::dibuja_sprite()
{
	glPushMatrix();
	glTranslated(0, 0, 1);

	// Dónde va el marcador (en coordenadas del tablero)
	GUI_marcador::calculaPos();

	//sprite_tp_Cursor->flip(false, false);
	sprite_1->flip(false, false);
	//sprite.flip(true, false);
	//animación. Si no hay velocidad fotograma 0
	//si no, hace uso del ciclo automatico 1-4
	/*if ((velocidad.x < 0.01) && (velocidad.x > -0.01))
		sprite.setState(0);
	else if (sprite.getState() == 0)
		sprite.setState(1, false);*/
	//sprite_tp_Cursor->setPos(pos_x, pos_y);
	//sprite_tp_Locked->setPos(pos_x, pos_y);
	sprite_1->setPos(pos_x, pos_y);

	switch (estado_marcador)
	{
	case OFF:
		sprite_1->setSize(0, 0);
		break;
	case ON:
		sprite_1->setSize(tam_casilla, tam_casilla);
		break;
	}

	sprite_1->loop();
	sprite_1->pause(false);
	sprite_1->draw();
	//case tp_Cursor:
	//	sprite_tp_Cursor->setSize(tam_casilla, tam_casilla);
	//	sprite_tp_Locked->setSize(0, 0);
	//	break;
	//case tp_Locked:
	//	sprite_tp_Cursor->setSize(0, 0);
	//	sprite_tp_Locked->setSize(tam_casilla, tam_casilla);
	//	break;

	//sprite_EnFoco->setSize(3, 3);

	//sprite_tp_Cursor->draw(); sprite_tp_Locked->draw();
 //sprite->draw();
	//fin del codigo incluido
	///////////////////////////////////////////////////////
	glPopMatrix();
}


ENUM_ESTADO_CURSOR GUI_marcador::get_estado()
{
	return estado_marcador;
}

void GUI_marcador::set_posicion(ENUM_FILA f, ENUM_COLUMNA c)
{
	fila = f; columna = c;
}

//////////////////////////////////////////////////////
/////////////////////////////////////

GUI_marcador_cursor::GUI_marcador_cursor( ENUM_FILA f, ENUM_COLUMNA c)
{
	string textura_Cursor = "imagenes/casilla_Cursor.png";
	//sprite_1 = new SpriteSequence(textura_Cursor.c_str(), 1, 1, 100, true, 0, 0, 2, 2);
	sprite_1 = new SpriteSequence(textura_Cursor.c_str(), 2, 1, 300, true, 0, 0, 2, 2);
	fila = f; columna = c;
	sprite_2 = nullptr;
}

void GUI_marcador_cursor::incrementa_posicion(int inc_f, int inc_c)
{
	if (estado_marcador = ON) {  // si esta activo el curso se puede mover a otra posición
		int nueva_fila = ((int)fila) + inc_f;
		if ((nueva_fila < 1) || (nueva_fila > 8)) nueva_fila = fila;
		fila = (ENUM_FILA)(nueva_fila);
		int nueva_columna = ((int)columna) + inc_c;
		if ((nueva_columna < 1) || (nueva_columna > 8)) nueva_columna = columna;
		columna = (ENUM_COLUMNA)(nueva_columna);
	}
}

void GUI_marcador_cursor::switch_cursor_casilla()
{
	auto est = estado_marcador;
	switch (est)
	{
	case OFF:	estado_marcador = ON;break;
	case ON:	estado_marcador = OFF;break;
	}
}

void GUI_marcador_cursor::reset_cursor_casilla()
{
	estado_marcador = OFF;
}


/////////////////////////////
////////////////////////////// 

GUI_marcador_locked::GUI_marcador_locked( ENUM_FILA f, ENUM_COLUMNA c)
{
	string text1 = "imagenes/casilla_Locked_naranja.png";
	sprite_1 = new SpriteSequence(text1.c_str(), 1, 1, 100, true, 0, 0, 2, 2);
	string text2 = "imagenes/casilla_Locked_rojo.png";
	sprite_2 = new SpriteSequence(text2.c_str(), 1, 1, 100, true, 0, 0, 2, 2);

	fila = f; columna = c; 
	estado_locked = TRANS;
	pieza_Locked = nullptr;
}

void GUI_marcador_locked::set_estado_locked(ENUM_ESTADO_LOCKED est, Pieza_GUI* pz_locked)
{
	switch (est)
	{
	case TRANS:
		estado_locked = TRANS;
		sprite_1->setSize(0, 0);
		sprite_2->setSize(0, 0);
		if (pieza_Locked != nullptr)
			pieza_Locked->anima_pieza(false);
		pieza_Locked = nullptr;
		break;
	case NARANJA:
		estado_locked = NARANJA;
		sprite_1->setSize(tam_casilla, tam_casilla);
		sprite_2->setSize(0, 0);
		if (pieza_Locked!=nullptr)
			pieza_Locked->anima_pieza(false);
		pieza_Locked = nullptr;
		break;
	case ROJO:
		estado_locked = ROJO;
		sprite_1->setSize(0, 0);
		sprite_2->setSize(tam_casilla, tam_casilla);
		pieza_Locked = pz_locked;
		pieza_Locked->anima_pieza(true);
		break;
	}

}


void GUI_marcador_locked::reset_pieza_locked()
{
	pieza_Locked = nullptr;
}


void GUI_marcador_locked::set_Can_Lock(bool C)
{
	Can_Lock_casilla = C;
	if (C) estado_marcador = ON;
	else estado_marcador = OFF;
}

bool GUI_marcador_locked::get_Can_Lock()
{
	return Can_Lock_casilla;
}

void GUI_marcador_locked::dibuja_sprite()
{
	glPushMatrix();
	glTranslated(0, 0, 1);
	// Dónde va el marcador (en coordenadas del tablero)
	GUI_marcador::calculaPos();

	sprite_1->flip(false, false);
	sprite_2->flip(false, false);
	sprite_1->setPos(pos_x, pos_y);
	sprite_2->setPos(pos_x, pos_y);


	switch (estado_locked)
	{
	case TRANS:
		sprite_1->setSize(0, 0);
		sprite_2->setSize(0, 0);
		break;
	case NARANJA:
		sprite_1->setSize(tam_casilla, tam_casilla);
		sprite_2->setSize(0, 0);
		break;
	case ROJO:
		sprite_1->setSize(0, 0);
		sprite_2->setSize(tam_casilla, tam_casilla);
		break;
	}
	sprite_1->draw();
	sprite_2->draw();

	glPopMatrix();
}

ENUM_ESTADO_LOCKED GUI_marcador_locked::get_estado_locked()
{
	return estado_locked;
}
