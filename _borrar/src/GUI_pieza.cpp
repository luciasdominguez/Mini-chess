#include "GUI_pieza.h"
#include "ETSIDI.h"
#include "string.h"

GUI_pieza::GUI_pieza()
{
	char destino[] = "";
	char toad[]= "imagenes/toad.png";
	char luigi[] = "imagenes/luigi.png";
	char yoshi[] = "imagenes/yoshi.png";
	char daisy[] = "imagenes/daisy.png";
	char peach[] = "imagenes/peach.png";
	char mario[] = "imagenes/mario.png";
	char huesitos[] = "imagenes/huesito.png";
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
			case vacio:
				break;
			case peon:
				strcpy(destino, toad);
				break;
			case torre:
				strcpy(destino, luigi);
				break;
			case caballo:
				strcpy(destino, yoshi);
				break;
			case alfil:
				strcpy(destino, daisy);
				break;
			case reina:
				strcpy(destino, peach);
				break;
			case rey:
				strcpy(destino, mario);
				break;
			}

		case negra:
			switch (tipo)
			{
			case vacio:
				break;
			case peon:
				strcpy(destino, huesitos);
				break;
			case torre:
				strcpy(destino, waluigi);
				break;
			case caballo:
				strcpy(destino, donkey);
				break;
			case alfil:
				strcpy(destino, bowsy);
				break;
			case reina:
				strcpy(destino, bowser);
				break;
			case rey:
				strcpy(destino, wario);
				break;
			}
	}
	ETSIDI::SpriteSequence sprite{destino, 5};
}

void GUI_pieza::dibuja_pieza()
{

}