#pragma once
#include "tablero.h"

enum class estado_J{NORMAL=0,JAQUE_A_BLANCAS,JAQUE_A_NEGRAS,MATE_A_BLANCAS,MATE_A_NEGRAS,TABLAS};

class gestor_jaques
{	
public:
	void Mod_estado(const tablero& T);
	bool comprobar_mov_posibles(const tablero& T, const color& color);

private:
	estado_J estado = estado_J::NORMAL;
};

