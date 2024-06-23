#include "logica.h"
#include "GUI_jugada.h"

bool Cl_logica::analiza_jugada(GUI_partida partida_in, GUI_jugada& jugada_propia, GUI_jugada& jugada_gravedad, int test)
{
	bool jugada_correcta = false;
	PIEZA_STRU pz;
	// Se analiza si la "jugada_propia" es correcta. Si o fues correcta se devuelve false
	//

	jugada_correcta = true;     //test
	//jugada_correcta = false;   //test
	// ..........................

	if (!jugada_correcta) return false;

	// Si la jugada es correcta se devuelve true y se genera la jugada_propia que será la ultima que ha entrado 
	// pero añadiendo, si es el caso, el resto de piezas afectadas (por haber comido una pieza contraria, un enroque ...
	// Tambien se devuelve en "jugada_gravedad" la lista de las piezas que se ven afectadas por la gravedad.

	//TEST "jugada_propia"
	jugada_propia = jugada_propia; // la jugada no tiene más piezas implicadas


	//TEST "jugada_gravedad"
	jugada_gravedad.vaciar_jugada();
	if (test == 1) {
		pz.c_color = negra; pz.c_tipo = caballo; pz.c_pieza = PZ_caballo_rey; pz.c_columna = B; pz.c_fila = f6;
	}
	else {
		pz.c_color = negra; pz.c_tipo = alfil; pz.c_pieza = PZ_alfil_rey; pz.c_columna = C; pz.c_fila = f6;
	}
	jugada_gravedad.add_pieza_a_jugada(pz);

	
	return true;
	
}
