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


/// ///////////////
///  jaque mate
///////////////////
class GUI_jaque_mate
{
	/// posición según escala del sprite
	float pos_x{}, pos_y{};
	bool ver_jaque_mate;
protected:
	SpriteSequence* sprite_jaque_mate;

public:
	GUI_jaque_mate();
	void dibuja_jaque_mate();
	void set_ver_jaque_mate(bool ver);
	bool get_ver_jaque_mate();
};

class GUI_jaque
{
	/// posición según escala del sprite
	float pos_x{}, pos_y{};
	bool ver_jaque;
protected:
	SpriteSequence* sprite_jaque;

public:
	GUI_jaque();
	void dibuja_jaque();
	void set_ver_jaque(bool ver);
	bool get_ver_jaque();
};