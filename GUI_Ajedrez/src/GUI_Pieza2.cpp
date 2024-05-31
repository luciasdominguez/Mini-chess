#include "GUI_Pieza2.h"



GUI_Pieza::GUI_Pieza()
{
	    calculaTextura();	
		calculaPos(); // calcula posición del sprite en función de la fila y columna de la pieza
		//sprite = new SpriteSequence(textura, 5, 1, 100, true, pos_x, pos_y, 2, 2);

}



GUI_Pieza::GUI_Pieza(STRU_PIEZA d)
{
	_datos_pieza = d;
	calculaTextura();
	const char* cstr = textura.c_str();
	calculaPos(); // calcula posición del sprite en función de la fila y columna de la pieza
	sprite = new SpriteSequence(cstr, 5, 1, 100, true, pos_x, pos_y, 2, 2);

}


void GUI_Pieza::dibuja_pieza()
{
	glPushMatrix();
	glTranslated(0, 0, 1);

	// Dónde va la pieza en coordenadas del tablero
	GUI_Pieza::calculaPos();

	sprite->flip(false, false);
	//sprite.flip(true, false);
	//animación. Si no hay velocidad fotograma 0
	//si no, hace uso del ciclo automatico 1-4
	/*if ((velocidad.x < 0.01) && (velocidad.x > -0.01))
		sprite.setState(0);
	else if (sprite.getState() == 0)
		sprite.setState(1, false);*/
	
	sprite->setPos(pos_x,pos_y);

	if (_datos_pieza.c_fila != fila_ND && _datos_pieza.c_columna != columna_ND)
	{
		sprite->setSize(2, 2);
	}
	else
	{
		sprite->setSize(1, 2);
	};


	sprite->draw();
	//fin del codigo incluido
	glPopMatrix();

}

void GUI_Pieza::calculaPos() 
{   //Vector2D posicion_tablero{ -3.0, 0.2 };	// Posición esquina izq abajo	
	float ref_x = 0, ref_y = 3.6, inc_casilla = 1.9, inc_desposito = 0.95;// referencia de casilla inferior izquierda
	if (_datos_pieza.c_fila != fila_ND && _datos_pieza.c_columna != columna_ND)
	{
		pos_x = ref_x + (8 - (int)_datos_pieza.c_fila) * inc_casilla;
		pos_y = ref_y + (((int)_datos_pieza.c_columna) - 1) * inc_casilla;
	}
	else // La pieza no está en juego
	{
		float offset_color = 0;
		if (_datos_pieza.c_color==negra) { offset_color = inc_desposito*9; }
	
		if (_datos_pieza.c_tipo == peon) { ref_y = -1; }
		else {ref_y = -3;};
		pos_y = ref_y;
		ref_x = -1.2;
		switch (_datos_pieza.c_tipo)
		{
		case peon:
			switch (_datos_pieza.c_pieza) // En función del subtipo cambia la posición en la zona de almacen
			{
			case PZ_peon_torre_reina:
				pos_x = 1 * inc_desposito + ref_x + offset_color;
				break;
			case PZ_peon_caballo_reina:
				pos_x = 2 * inc_desposito + ref_x + offset_color;
				break;
			case PZ_peon_alfil_reina:
				pos_x = 3 * inc_desposito + ref_x + offset_color;
				break;
			case PZ_peon_reina:
				pos_x = 4 * inc_desposito + ref_x + offset_color;
				break;
			case PZ_peon_rey:
				pos_x = 5 * inc_desposito + ref_x + offset_color;
				break;
			case PZ_peon_alfil_rey:
				pos_x = 6 * inc_desposito + ref_x + offset_color;
				break;
			case PZ_peon_caballo_rey:
				pos_x = 7 * inc_desposito + ref_x + offset_color;
				break;
			case PZ_peon_torre_rey:
				pos_x = 8 * inc_desposito + ref_x + offset_color;
				break;
			}
			break;
		case torre:
			switch (_datos_pieza.c_pieza) // En función del subtipo cambia la posición en la zona de almacen
			{
				case PZ_torre_reina:
					pos_x = 1 * inc_desposito + ref_x + offset_color;
					break;
				case PZ_torre_rey:
					pos_x = 8 * inc_desposito + ref_x + offset_color;
					break;
			};
			break;
		case caballo:
			switch (_datos_pieza.c_pieza) // En función del subtipo cambia la posición en la zona de almacen
			{
				case PZ_caballo_reina:
					pos_x = 2 * inc_desposito + ref_x + offset_color;
					break;
				case PZ_caballo_rey:
					pos_x = 7 * inc_desposito + ref_x + offset_color;
					break;
			}
			break;
		case alfil:
			switch (_datos_pieza.c_pieza) // En función del subtipo cambia la posición en la zona de almacen
			{
				case PZ_alfil_reina:
					pos_x = 3 * inc_desposito + ref_x + offset_color;
					break;
				case PZ_alfil_rey:
					pos_x = 6 * inc_desposito + ref_x + offset_color;
					break;
			};
			break;
		case reina:
			pos_x = 4 * inc_desposito + ref_x + offset_color;
			break;
		case rey:
			pos_x = 5 * inc_desposito + ref_x + offset_color;
			break;
		};

	};

}

void GUI_Pieza::calculaTextura()
{
		
	 //   char textura[] = "imagenes/wario.png"; // Valor por defecto
		//char toad[] = "imagenes/toad.png";
		//char luigi[] = "imagenes/luigi.png";
		//char yoshi[] = "imagenes/yoshi.png";
		//char daisy[] = "imagenes/daisy.png";
		//char peach[] = "imagenes/peach.png";
		//char mario[] = "imagenes/mario.png";
		//char huesitos[] = "imagenes/huesitos.png";
		//char waluigi[] = "imagenes/waluigi.png";
		//char donkey[] = "imagenes/donkey.png";
		//char bowsy[] = "imagenes/bowsy.png";
		//char bowser[] = "imagenes/bowser.png";
		//char wario[] = "imagenes/wario.png";

		//char textura[] = "imagenes/wario.png"; // Valor por defecto
		string toad = "imagenes/toad.png";
		string luigi = "imagenes/luigi.png";
		string yoshi = "imagenes/yoshi.png";
		string daisy = "imagenes/daisy.png";
		string peach= "imagenes/peach.png";
		string mario= "imagenes/mario.png";
		string huesitos = "imagenes/huesitos.png";
		string waluigi= "imagenes/waluigi.png";
		string donkey= "imagenes/donkey.png";
		string bowsy= "imagenes/bowsy.png";
		string bowser = "imagenes/bowser.png";
		string wario = "imagenes/wario.png";

		ENUM_COLOR color = _datos_pieza.c_color;
		ENUM_TIPO tipo = _datos_pieza.c_tipo;
		ENUM_FILA c_fila = _datos_pieza.c_fila;
		ENUM_COLUMNA c_columna = _datos_pieza.c_columna;
		//ENUM_COLOR color = d.c_color;
		//ENUM_TIPO tipo = d.c_tipo;
		//ENUM_FILA c_fila = d.c_fila;
		//ENUM_COLUMNA c_columna = d.c_columna;

		// selección del sprite en función del tipo y del color
		switch (color)
		{
		case blanca:
			switch (tipo)
			{
			case peon:
				textura=toad;
				//size_x = 2;
				//size_y = 2;
				break;
			case torre:
				textura=luigi;
				break;
			case caballo:
				textura= yoshi;
				break;
			case alfil:
				textura= daisy;
				break;
			case reina:
				textura= peach;
				break;
			case rey:
				textura= mario;
				break;
			}
			break;

		case negra:
			switch (tipo)
			{
			case peon:
				textura=huesitos;
				break;
			case torre:
				textura= waluigi;
				break;
			case caballo:
				textura= donkey;
				break;
			case alfil:
				textura= bowsy;
				break;
			case reina:
				textura= bowser;
				break;
			case rey:
				textura= wario;
				break;
			}
			break;
		}

}

void GUI_Pieza::set_datosPieza(STRU_PIEZA datos)
{
	_datos_pieza = datos;
}

STRU_PIEZA GUI_Pieza::get_datosPieza()
{
	return _datos_pieza;
}



