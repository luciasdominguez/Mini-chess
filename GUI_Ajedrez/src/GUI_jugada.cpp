#include "GUI_jugada.h"

GUI_jugada::GUI_jugada()
{
	jugador = GRAVEDAD_N;
	numero_en_la_partida = 1;
}

void GUI_jugada::set_jugador(ENUM_JUGADOR jug)
{
	jugador = jug;
	switch (jug) //BLANCAS=0, NEGRAS, GRAVEDAD_N, GRAVEDA_B
	{
	case NEGRAS:		jugador_siguiente = GRAVEDAD_N;	break;
	case GRAVEDAD_N:	jugador_siguiente = BLANCAS;		break;
	case BLANCAS:		jugador_siguiente = GRAVEDAD_B;	break;
	case GRAVEDAD_B:	jugador_siguiente = NEGRAS;	break;
	default:			jugador_siguiente = GRAVEDAD_N;	break;
	};
}

void GUI_jugada::set_numero_en_la_partida(int num)
{
	numero_en_la_partida = num;
}

int GUI_jugada::get_numero_en_la_partida()
{
	return numero_en_la_partida;
}

vector<PIEZA_STRU> GUI_jugada::get_lista_piezas_movidas()
{
	return lista_PiezasMovidas;
}

void GUI_jugada::vaciar_jugada()
{
	lista_PiezasMovidas.erase(lista_PiezasMovidas.begin(), lista_PiezasMovidas.end());
}

void GUI_jugada::nueva_jugada()
{

}

void GUI_jugada::add_pieza_a_jugada(PIEZA_STRU pz)
{
	lista_PiezasMovidas.push_back(pz);
}

void GUI_jugada::inicio_partida()
{
	PIEZA_STRU pieza{};

	
	/////// BLANCAS //////////////
	pieza.c_color = blanca;
	///////////////////////////////
	/////////--- PEONES-----/////////
	pieza.c_tipo = peon;
	pieza.c_pieza = PZ_peon_torre_reina;	 
	pieza.c_columna = A;	pieza.c_fila = f2; lista_PiezasMovidas.push_back(pieza);
	pieza.c_pieza = PZ_peon_caballo_reina;		
	pieza.c_columna = B;	pieza.c_fila = f2; lista_PiezasMovidas.push_back(pieza);
	pieza.c_pieza = PZ_peon_alfil_reina;
	pieza.c_columna = C;	pieza.c_fila = f2; lista_PiezasMovidas.push_back(pieza);
	pieza.c_pieza = PZ_peon_reina;
	pieza.c_columna = D;	pieza.c_fila = f2; lista_PiezasMovidas.push_back(pieza);
	pieza.c_pieza = PZ_peon_rey;
	pieza.c_columna = E;	pieza.c_fila = f2; lista_PiezasMovidas.push_back(pieza);
	pieza.c_pieza = PZ_peon_alfil_rey;
	pieza.c_columna = F;	pieza.c_fila = f2; lista_PiezasMovidas.push_back(pieza);
	pieza.c_pieza = PZ_peon_caballo_rey;
	pieza.c_columna = G;	pieza.c_fila = f2; lista_PiezasMovidas.push_back(pieza);
	pieza.c_pieza = PZ_peon_torre_rey;
	pieza.c_columna = H;	pieza.c_fila = f2; lista_PiezasMovidas.push_back(pieza);
	pieza.c_tipo = torre; //////////////////
	pieza.c_pieza = PZ_torre_reina;
	pieza.c_columna = A;	pieza.c_fila = f1; lista_PiezasMovidas.push_back(pieza);
	pieza.c_pieza = PZ_torre_rey;
	pieza.c_columna = H;	pieza.c_fila = f1; lista_PiezasMovidas.push_back(pieza);
	pieza.c_tipo = caballo; //////////////////
	pieza.c_pieza = PZ_caballo_reina;
	pieza.c_columna = B;	pieza.c_fila = f1; lista_PiezasMovidas.push_back(pieza);
	pieza.c_pieza = PZ_caballo_rey;
	pieza.c_columna = G;	pieza.c_fila = f1; lista_PiezasMovidas.push_back(pieza);
	pieza.c_tipo = alfil; //////////////////
	pieza.c_pieza = PZ_alfil_reina;
	pieza.c_columna = C;	pieza.c_fila = f1; lista_PiezasMovidas.push_back(pieza);
	pieza.c_pieza = PZ_alfil_rey;
	pieza.c_columna = F;	pieza.c_fila = f1; lista_PiezasMovidas.push_back(pieza);
	pieza.c_tipo = reina; //////////////////
	pieza.c_pieza = PZ_reina;
	pieza.c_columna = D;	pieza.c_fila = f1; lista_PiezasMovidas.push_back(pieza);
	pieza.c_tipo = rey; //////////////////
	pieza.c_pieza = PZ_rey;
	pieza.c_columna = E;	pieza.c_fila = f1; lista_PiezasMovidas.push_back(pieza);

	/////// BLANCAS //////////////
	pieza.c_color = negra;
	///////////////////////////////
	/////////--- PEONES-----/////////
	pieza.c_tipo = peon;
	pieza.c_pieza = PZ_peon_torre_reina;
	pieza.c_columna = A;	pieza.c_fila = f7; lista_PiezasMovidas.push_back(pieza);
	pieza.c_pieza = PZ_peon_caballo_reina;
	pieza.c_columna = B;	pieza.c_fila = f7; lista_PiezasMovidas.push_back(pieza);
	pieza.c_pieza = PZ_peon_alfil_reina;
	pieza.c_columna = C;	pieza.c_fila = f7; lista_PiezasMovidas.push_back(pieza);
	pieza.c_pieza = PZ_peon_reina;
	pieza.c_columna = D;	pieza.c_fila = f7; lista_PiezasMovidas.push_back(pieza);
	pieza.c_pieza = PZ_peon_rey;
	pieza.c_columna = E;	pieza.c_fila = f7; lista_PiezasMovidas.push_back(pieza);
	pieza.c_pieza = PZ_peon_alfil_rey;
	pieza.c_columna = F;	pieza.c_fila = f7; lista_PiezasMovidas.push_back(pieza);
	pieza.c_pieza = PZ_peon_caballo_rey;
	pieza.c_columna = G;	pieza.c_fila = f7; lista_PiezasMovidas.push_back(pieza);
	pieza.c_pieza = PZ_peon_torre_rey;
	pieza.c_columna = H;	pieza.c_fila = f7; lista_PiezasMovidas.push_back(pieza);
	pieza.c_tipo = torre; //////////////////
	pieza.c_pieza = PZ_torre_reina;
	pieza.c_columna = A;	pieza.c_fila = f8; lista_PiezasMovidas.push_back(pieza);
	pieza.c_pieza = PZ_torre_rey;
	pieza.c_columna = H;	pieza.c_fila = f8; lista_PiezasMovidas.push_back(pieza);
	pieza.c_tipo = caballo; //////////////////
	pieza.c_pieza = PZ_caballo_reina;
	pieza.c_columna = B;	pieza.c_fila = f8; lista_PiezasMovidas.push_back(pieza);
	pieza.c_pieza = PZ_caballo_rey;
	pieza.c_columna = G;	pieza.c_fila = f8; lista_PiezasMovidas.push_back(pieza);
	pieza.c_tipo = alfil; //////////////////
	pieza.c_pieza = PZ_alfil_reina;
	pieza.c_columna = C;	pieza.c_fila = f8; lista_PiezasMovidas.push_back(pieza);
	pieza.c_pieza = PZ_alfil_rey;
	pieza.c_columna = F;	pieza.c_fila = f8; lista_PiezasMovidas.push_back(pieza);
	pieza.c_tipo = reina; //////////////////
	pieza.c_pieza = PZ_reina;
	pieza.c_columna = D;	pieza.c_fila = f8; lista_PiezasMovidas.push_back(pieza);
	pieza.c_tipo = rey; //////////////////
	pieza.c_pieza = PZ_rey;
	pieza.c_columna = E;	pieza.c_fila = f8; lista_PiezasMovidas.push_back(pieza);
}

void GUI_jugada::ejemplo_jugada_01()
{
	PIEZA_STRU pieza{};
	pieza.c_color = blanca;
	pieza.c_tipo = peon;
	pieza.c_pieza = PZ_peon_torre_reina;
	pieza.c_columna = A;	pieza.c_fila = f2; lista_PiezasMovidas.push_back(pieza);
}

void GUI_jugada::ejemplo_jugada_02()
{
	PIEZA_STRU pieza{};
	pieza.c_color = blanca;
	pieza.c_tipo = peon;
	pieza.c_pieza = PZ_peon_caballo_reina;
	pieza.c_columna = B;	pieza.c_fila = f2; lista_PiezasMovidas.push_back(pieza);

}

void GUI_jugada::ejemplo_jugada_03()
{
	PIEZA_STRU pieza{};
	pieza.c_color = blanca;
	pieza.c_tipo = peon;
	pieza.c_pieza = PZ_peon_alfil_reina;
	pieza.c_columna = C;	pieza.c_fila = f2; lista_PiezasMovidas.push_back(pieza);
}

void GUI_jugada::ejemplo_jugada_04()
{
	PIEZA_STRU pieza{};
	pieza.c_color = negra;
	pieza.c_tipo = peon;
	pieza.c_pieza = PZ_peon_reina;
	pieza.c_columna = D;	pieza.c_fila = f2; lista_PiezasMovidas.push_back(pieza);
}
