#include "Juego.h"
#include "GUI_Pieza2.h"
#include <windows.data.json.h>

Juego::Juego()
{
	generar_listado_datos_piezas_OFF();
	generar_piezas();
}

void Juego::dibuja_juego()
{
	miTablero.dibuja_tablero();
	actualizar_piezas();
	dibujar_piezas();
}

void Juego::generar_piezas()
{
	// Aqui pondremos un bucle para generar el vector de GUI_pieza (solo se ejecuta al principio)
	for (int i = 0; i < lista_datos_de_piezas.size(); i++)
	{
		STRU_PIEZA datos_pz = lista_datos_de_piezas[i];
		GUI_Pieza pz(datos_pz);
		lista_de_piezas.push_back(pz);

	}
}

void Juego::actualizar_piezas()
// se actualizará los valores de las piezas en base a la lista_datos_de_piezas
{
	for (int i = 0; i < lista_datos_de_piezas.size(); i++)
	{
		STRU_PIEZA datos_pz = lista_datos_de_piezas[i];

		//GUI_Pieza pz(datos_pz);
	}


	STRU_PIEZA pieza{};

	for (auto it_in = lista_datos_de_piezas.begin(); it_in != lista_datos_de_piezas.end(); ++it_in)
	{
		auto tipo_in = (*it_in).c_tipo;
		auto sub_tipo_in = (*it_in).c_pieza;
		auto color_in = (*it_in).c_color;
		auto fila_in = (*it_in).c_fila;
		auto columna_in = (*it_in).c_columna;

		for (auto it_pz = lista_de_piezas.begin(); it_pz != lista_de_piezas.end(); ++it_pz)
		{
			if (tipo_in == (*it_pz)._datos_pieza.c_tipo && sub_tipo_in == (*it_pz)._datos_pieza.c_pieza && color_in == (*it_pz)._datos_pieza.c_color)
				// si el elemnto del listado coincide con las características 
				// del objeto se le asigna la posición del listado
			{
				(*it_pz)._datos_pieza.c_fila = fila_in;
				(*it_pz)._datos_pieza.c_columna = columna_in;
			}
		};

	}


}
void Juego::dibujar_piezas()
// Aqui pondremos un bucle para dibjuar todas las piezas
{
	for (int i = 0; i < lista_de_piezas.size(); i++)
	{
		lista_de_piezas[i].dibuja_pieza();
	}
}




void Juego::generar_listado_datos_piezas_OFF()
// Se ejecuta para tener relleno lista_datos_de_piezas con todas las piezas 
// fuera del tablero. Solo se ejecuta al principio del programa
{
	STRU_PIEZA pieza{};

	pieza.c_columna = columna_ND;
	pieza.c_fila = fila_ND;
	pieza.c_color = blanca;

	/////// BLANCAS //////////////
	pieza.c_tipo = peon; /////////--- PEONES-----/////////
	pieza.c_pieza = PZ_peon_torre_reina;		lista_datos_de_piezas.push_back(pieza);
	pieza.c_pieza = PZ_peon_caballo_reina;		lista_datos_de_piezas.push_back(pieza);
	pieza.c_pieza = PZ_peon_alfil_reina;		lista_datos_de_piezas.push_back(pieza);
	pieza.c_pieza = PZ_peon_reina;				lista_datos_de_piezas.push_back(pieza);
	pieza.c_pieza = PZ_peon_rey;				lista_datos_de_piezas.push_back(pieza);
	pieza.c_pieza = PZ_peon_alfil_rey;			lista_datos_de_piezas.push_back(pieza);
	pieza.c_pieza = PZ_peon_caballo_rey;		lista_datos_de_piezas.push_back(pieza);
	pieza.c_pieza = PZ_peon_torre_rey;			lista_datos_de_piezas.push_back(pieza);
	pieza.c_tipo = torre; //////////////////
	pieza.c_pieza = PZ_torre_reina;				lista_datos_de_piezas.push_back(pieza);
	pieza.c_pieza = PZ_torre_rey; 				lista_datos_de_piezas.push_back(pieza);
	pieza.c_tipo = caballo; //////////////////
	pieza.c_pieza = PZ_caballo_reina; 			lista_datos_de_piezas.push_back(pieza);
	pieza.c_pieza = PZ_caballo_rey; 			lista_datos_de_piezas.push_back(pieza);
	pieza.c_tipo = alfil; //////////////////
	pieza.c_pieza = PZ_alfil_reina; 			lista_datos_de_piezas.push_back(pieza);
	pieza.c_pieza = PZ_alfil_rey; 				lista_datos_de_piezas.push_back(pieza);
	pieza.c_tipo = reina; //////////////////
	pieza.c_pieza = PZ_reina; 					lista_datos_de_piezas.push_back(pieza);
	pieza.c_tipo = rey; //////////////////
	pieza.c_pieza = PZ_rey; 					lista_datos_de_piezas.push_back(pieza);

	/////// NEGRAS //////////////
	pieza.c_color = negra;
	pieza.c_tipo = peon; /////////--- PEONES-----/////////
	pieza.c_pieza = PZ_peon_torre_reina;		lista_datos_de_piezas.push_back(pieza);
	pieza.c_pieza = PZ_peon_caballo_reina;		lista_datos_de_piezas.push_back(pieza);
	pieza.c_pieza = PZ_peon_alfil_reina;		lista_datos_de_piezas.push_back(pieza);
	pieza.c_pieza = PZ_peon_reina;				lista_datos_de_piezas.push_back(pieza);
	pieza.c_pieza = PZ_peon_rey;				lista_datos_de_piezas.push_back(pieza);
	pieza.c_pieza = PZ_peon_alfil_rey;			lista_datos_de_piezas.push_back(pieza);
	pieza.c_pieza = PZ_peon_caballo_rey;		lista_datos_de_piezas.push_back(pieza);
	pieza.c_pieza = PZ_peon_torre_rey;			lista_datos_de_piezas.push_back(pieza);
	pieza.c_tipo = torre; //////////////////
	pieza.c_pieza = PZ_torre_reina;				lista_datos_de_piezas.push_back(pieza);
	pieza.c_pieza = PZ_torre_rey; 				lista_datos_de_piezas.push_back(pieza);
	pieza.c_tipo = caballo; //////////////////
	pieza.c_pieza = PZ_caballo_reina; 			lista_datos_de_piezas.push_back(pieza);
	pieza.c_pieza = PZ_caballo_rey; 			lista_datos_de_piezas.push_back(pieza);
	pieza.c_tipo = alfil; //////////////////
	pieza.c_pieza = PZ_alfil_reina; 			lista_datos_de_piezas.push_back(pieza);
	pieza.c_pieza = PZ_alfil_rey; 				lista_datos_de_piezas.push_back(pieza);
	pieza.c_tipo = reina; //////////////////
	pieza.c_pieza = PZ_reina; 					lista_datos_de_piezas.push_back(pieza);
	pieza.c_tipo = rey; //////////////////
	pieza.c_pieza = PZ_rey; 					lista_datos_de_piezas.push_back(pieza);
}

void Juego::generar_listado_datos_piezas_NEW()
{
	STRU_PIEZA pieza{};
	int contador = 0;

	for (auto it = lista_datos_de_piezas.begin(); it != lista_datos_de_piezas.end(); ++it)
	{
		contador++;
		auto tip = (*it).c_tipo; auto pz_pieza = (*it).c_pieza; auto col = (*it).c_color;
		switch(col)
		{
		case (blanca):
			/////
		   switch (pz_pieza)
			{
				case PZ_peon_torre_reina:
					(*it).c_columna = A;(*it).c_fila = f2;break;
				case PZ_peon_caballo_reina:
					(*it).c_columna = B;(*it).c_fila = f2;break;
				case PZ_peon_alfil_reina:
					(*it).c_columna = C;(*it).c_fila = f2;break;
				case PZ_peon_reina:
					(*it).c_columna = D;(*it).c_fila = f2;break;
				case PZ_peon_rey:
					(*it).c_columna = E;(*it).c_fila = f2;break;
				case PZ_peon_alfil_rey:
					(*it).c_columna = F;(*it).c_fila = f2;break;
				case PZ_peon_caballo_rey:
					(*it).c_columna = G;(*it).c_fila = f2;break;
				case PZ_peon_torre_rey:
					(*it).c_columna = H;(*it).c_fila = f2;break;
				case PZ_torre_reina:
					(*it).c_columna = A;(*it).c_fila = f1;break;
				case PZ_caballo_reina:
					(*it).c_columna = B;(*it).c_fila = f1;break;
				case PZ_alfil_reina:
					(*it).c_columna = C;(*it).c_fila = f1;break;
				case PZ_reina:
					(*it).c_columna = D;(*it).c_fila = f1;break;
				case PZ_rey:
					(*it).c_columna = E;(*it).c_fila = f1;break;
				case PZ_alfil_rey:
					(*it).c_columna = F;(*it).c_fila = f1;break;
				case PZ_caballo_rey:
					(*it).c_columna = G;(*it).c_fila = f1;break;
				case PZ_torre_rey:
					(*it).c_columna = H;(*it).c_fila = f1;break;
			};
			break;
			////
			break;
		case (negra):
			////
			switch (pz_pieza)
			{
			case PZ_peon_torre_reina:
				(*it).c_columna = A;(*it).c_fila = f7;break;
			case PZ_peon_caballo_reina:
				(*it).c_columna = B;(*it).c_fila = f7;break;
			case PZ_peon_alfil_reina:
				(*it).c_columna = C;(*it).c_fila = f7;break;
			case PZ_peon_reina:
				(*it).c_columna = D;(*it).c_fila = f7;break;
			case PZ_peon_rey:
				(*it).c_columna = E;(*it).c_fila = f7;break;
			case PZ_peon_alfil_rey:
				(*it).c_columna = F;(*it).c_fila = f7;break;
			case PZ_peon_caballo_rey:
				(*it).c_columna = G;(*it).c_fila = f7;break;
			case PZ_peon_torre_rey:
				(*it).c_columna = H;(*it).c_fila = f7;break;
			case PZ_torre_reina:
				(*it).c_columna = A;(*it).c_fila = f8;break;
			case PZ_caballo_reina:
				(*it).c_columna = B;(*it).c_fila = f8;break;
			case PZ_alfil_reina:
				(*it).c_columna = C;(*it).c_fila = f8;break;
			case PZ_reina:
				(*it).c_columna = D;(*it).c_fila = f8;break;
			case PZ_rey:
				(*it).c_columna = E;(*it).c_fila = f8;break;
			case PZ_alfil_rey:
				(*it).c_columna = F;(*it).c_fila = f8;break;
			case PZ_caballo_rey:
				(*it).c_columna = G;(*it).c_fila = f8;break;
			case PZ_torre_rey:
				(*it).c_columna = H;(*it).c_fila = f8;break;
			};
			break;
			////
			break;
		}
	}
}

