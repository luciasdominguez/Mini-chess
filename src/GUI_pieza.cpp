#include "GUI_pieza.h"
#include "string.h"
#include "juego.h"


GUI_pieza::GUI_pieza()
{
	char textura[] = "imagenes/wario.png";  /// valor por defecto
	char toad[]= "imagenes/daisy.png";
	char luigi[] = "imagenes/luigi.png";
	char yoshi[] = "imagenes/yoshi.png";
	char daisy[] = "imagenes/daisy.png";
	char peach[] = "imagenes/peach.png";
	char mario[] = "imagenes/mario.png";
	char huesitos[] = "imagenes/huesitos.png";
	char waluigi[] = "imagenes/waluigi.png";
	char donkey[] = "imagenes/donkey.png";
	char bowsy[] = "imagenes/bowsy.png";
	char bowser[] = "imagenes/bowser.png";
	char wario[] = "imagenes/wario.png";

	switch (color) 
	{
		case blanca:
			switch (tipo)
			{
			case tipo_ND:
				break;
			case peon:
				strcpy(textura, toad);
				//size_x = 2;
				//size_y = 2;
				break;
			case torre:
				strcpy(textura, luigi);
				break;
			case caballo:
				strcpy(textura, yoshi);
				break;
			case alfil:
				strcpy(textura, daisy);
				break;
			case reina:
				strcpy(textura, peach);
				break;
			case rey:
				strcpy(textura, mario);
				break;
			}
			break;

		case negra:
			switch (tipo)
			{
			case tipo_ND:
				break;
			case peon:
				strcpy(textura, huesitos);
				break;
			case torre:
				strcpy(textura, waluigi);
				break;
			case caballo:
				strcpy(textura, donkey);
				break;
			case alfil:
				strcpy(textura, bowsy);
				break;
			case reina:
				strcpy(textura, bowser);
				break;
			case rey:
				strcpy(textura, wario);
				break;
			}
			break;
	}
	sprite = new SpriteSequence(textura, 5, 1, 100, true, 0, 5.5, 2, 2);
}


void GUI_pieza::dibuja_pieza()
{
	glPushMatrix();
	glTranslated(0, 0, 1);

	// Dónde va la pieza en coordenadas del tablero



	float pos_x, pos_y;
	//pos_x=GUI_Tablero::get_tamaño_x;
	//sprite->setPos(pos_x, pos_y);
	
	
    sprite->flip(false, false);
	//sprite.flip(true, false);
	//animación. Si no hay velocidad fotograma 0
	//si no, hace uso del ciclo automatico 1-4
	/*if ((velocidad.x < 0.01) && (velocidad.x > -0.01))
		sprite.setState(0);
	else if (sprite.getState() == 0)
		sprite.setState(1, false);*/
	sprite->draw();
	//fin del codigo incluido
	glPopMatrix();

}