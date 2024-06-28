#include "ETSIDI.h"
#include <string>
#include "GUI_Tablero.h"
using namespace ETSIDI;

class GUI_turno
{
	ENUM_JUGADOR turno = BLANCAS; //GRAVEDAD_N;
	float pos_x{}, pos_y{}; /// posición según escala del sprite
	void calcula_Pos_turno(ENUM_JUGADOR turno);

protected:
	SpriteSequence* sprite_turno;

public:
	GUI_turno();
	void dibuja_turno(ENUM_JUGADOR turno);
};

