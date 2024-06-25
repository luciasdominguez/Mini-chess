#include "logica.h"
#include "GUI_jugada.h"

int Cl_logica::analiza_jugada(GUI_partida partida_in, GUI_jugada& jugada_propia, GUI_jugada& jugada_gravedad, int test)
{
	bool jugada_correcta = false;
	bool jaque_mate = false;
	PIEZA_STRU pz;
	// Se analiza si la "jugada_propia" es correcta. Si no fues correcta se devuelve 0
	//

	jugada_correcta = true;     //test
	//jugada_correcta = false;   //test
	// ..........................

	if (!jugada_correcta) return 0;

	// Si la jugada es correcta:
	//	se genera la "jugada_propia" que será la ultima que ha entrado 
	//	pero añadiendo, si es el caso, el resto de piezas afectadas (por haber comido una pieza contraria, un enroque ...
	//	Tambien se devuelve en "jugada_gravedad" la lista de las piezas que se ven afectadas por la gravedad.
	// 
	// Si la "jugaga_gravedad" ha generado un jaque mate devuelve 2 para que se termine la partida
	// si no es jaque mate devuelve 1


	//TEST "jugada_propia"
	jugada_propia = jugada_propia; // la jugada no tiene más piezas implicadas


	//TEST "jugada_gravedad"
	jugada_gravedad.vaciar_jugada();
	switch (test) {
		case 1:
			pz.c_color = negra; pz.c_tipo = caballo; pz.c_pieza = PZ_caballo_rey; pz.c_columna = B; pz.c_fila = f6;
			jugada_gravedad.add_pieza_a_jugada(pz);
			pz.c_color = blanca; pz.c_tipo = alfil; pz.c_pieza = PZ_alfil_rey; pz.c_columna = G; pz.c_fila = f4;
			jugada_gravedad.add_pieza_a_jugada(pz);
			break;
		case 2:
			pz.c_color = negra; pz.c_tipo = alfil; pz.c_pieza = PZ_alfil_rey; pz.c_columna = C; pz.c_fila = f6;
			jugada_gravedad.add_pieza_a_jugada(pz);
			pz.c_color = negra; pz.c_tipo = torre; pz.c_pieza = PZ_torre_rey; pz.c_columna = C; pz.c_fila = f_ND;
			jugada_gravedad.add_pieza_a_jugada(pz);
			break;
		case 3:
			pz.c_color = negra; pz.c_tipo = reina; pz.c_pieza = PZ_reina; pz.c_columna = H; pz.c_fila = f5;
			jugada_gravedad.jaque_mate = true;
			jugada_gravedad.add_pieza_a_jugada(pz);
			return 2;
	}

	//FIN TEST "jugada_gravedad"
	//return 2;
	return 1;
	
}
