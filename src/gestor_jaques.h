#pragma once
#include "tablero.h"
#include "casillas.h"
#include "fichas.h"
enum class estado_J{NORMAL=0,JAQUE_A_BLANCAS,JAQUE_A_NEGRAS,MATE_A_BLANCAS,MATE_A_NEGRAS,TABLAS};

class gestor_jaques
{	
public:
	bool Mod_estado(const tablero& T);
	bool comprobar_mov_posibles(const tablero& T, const ENUM_COLOR& color);

private:
	estado_J estado = estado_J::NORMAL;
};

