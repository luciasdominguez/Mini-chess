#include "GUI_movimiento.h"

GUI_movimiento::GUI_movimiento()
{
	jugador = GRAVEDAD;
	numero_en_la_partida = 1;
}

void GUI_movimiento::set_jugador(ENUM_JUGADOR jug)
{
	jugador = jug;
}

int GUI_movimiento::get_numero_en_la_partida()
{
	return numero_en_la_partida;
}

void GUI_movimiento::vaciar_movimiento()
{
	lista_PiezasMovidas.erase(lista_PiezasMovidas.begin(), lista_PiezasMovidas.end());
}

void GUI_movimiento::nuevo_movimiento()
{

}

void GUI_movimiento::add_pieza_a_movimiento(PIEZA_STRU pz)
{
	lista_PiezasMovidas.push_back(pz);
}

void GUI_movimiento::inicio_partida()
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

void GUI_movimiento::ejemplo_movi_01()
{
	PIEZA_STRU pieza{};
	pieza.c_color = blanca;
	pieza.c_tipo = peon;
	pieza.c_pieza = PZ_peon_torre_reina;
	pieza.c_columna = A;	pieza.c_fila = f2; lista_PiezasMovidas.push_back(pieza);
	//pieza.c_pieza = PZ_peon_caballo_reina;
	//pieza.c_columna = B;	pieza.c_fila = f2; lista_PiezasMovidas.push_back(pieza);
	//pieza.c_pieza = PZ_peon_alfil_reina;
	//pieza.c_columna = C;	pieza.c_fila = f2; lista_PiezasMovidas.push_back(pieza);
	//pieza.c_pieza = PZ_peon_reina;
	//pieza.c_columna = D;	pieza.c_fila = f2; lista_PiezasMovidas.push_back(pieza);
	//pieza.c_pieza = PZ_peon_rey;
	//pieza.c_columna = E;	pieza.c_fila = f2; lista_PiezasMovidas.push_back(pieza);
	//pieza.c_pieza = PZ_peon_alfil_rey;
	//pieza.c_columna = F;	pieza.c_fila = f2; lista_PiezasMovidas.push_back(pieza);
	//pieza.c_pieza = PZ_peon_caballo_rey;
	//pieza.c_columna = G;	pieza.c_fila = f2; lista_PiezasMovidas.push_back(pieza);
	//pieza.c_pieza = PZ_peon_torre_rey;
	//pieza.c_columna = H;	pieza.c_fila = f2; lista_PiezasMovidas.push_back(pieza);
	//pieza.c_tipo = torre; //////////////////
	//pieza.c_pieza = PZ_torre_reina;
	//pieza.c_columna = A;	pieza.c_fila = f1; lista_PiezasMovidas.push_back(pieza);
	//pieza.c_pieza = PZ_torre_rey;
	//pieza.c_columna = H;	pieza.c_fila = f1; lista_PiezasMovidas.push_back(pieza);
}

void GUI_movimiento::ejemplo_movi_02()
{
	PIEZA_STRU pieza{};
	pieza.c_color = blanca;
	pieza.c_tipo = peon;
	pieza.c_pieza = PZ_peon_caballo_reina;
	pieza.c_columna = B;	pieza.c_fila = f2; lista_PiezasMovidas.push_back(pieza);

}

void GUI_movimiento::ejemplo_movi_03()
{
	PIEZA_STRU pieza{};
	pieza.c_color = blanca;
	pieza.c_tipo = peon;
	pieza.c_pieza = PZ_peon_alfil_reina;
	pieza.c_columna = C;	pieza.c_fila = f2; lista_PiezasMovidas.push_back(pieza);
}

void GUI_movimiento::ejemplo_movi_04()
{
	PIEZA_STRU pieza{};
	pieza.c_color = blanca;
	pieza.c_tipo = peon;
	pieza.c_pieza = PZ_peon_reina;
	pieza.c_columna = D;	pieza.c_fila = f2; lista_PiezasMovidas.push_back(pieza);
}
