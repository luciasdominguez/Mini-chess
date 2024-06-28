#include "logica.h"
#include "GUI_jugada.h"


Cl_logica::Cl_logica()
{
	//Tablero_actual_= {// vector de 2 dimesiones de 8x8
	//	{ pz_0,pz_0,pz_0,pz_0,pz_0,pz_0,pz_0,pz_0 },
	//	{ pz_0,pz_0,pz_0,pz_0,pz_0,pz_0,pz_0,pz_0 },
	//	{ pz_0,pz_0,pz_0,pz_0,pz_0,pz_0,pz_0,pz_0 },
	//	{ pz_0,pz_0,pz_0,pz_0,pz_0,pz_0,pz_0,pz_0 },
	//	{ pz_0,pz_0,pz_0,pz_0,pz_0,pz_0,pz_0,pz_0 },
	//	{ pz_0,pz_0,pz_0,pz_0,pz_0,pz_0,pz_0,pz_0 },
	//	{ pz_0,pz_0,pz_0,pz_0,pz_0,pz_0,pz_0,pz_0 },
	//	{ pz_0,pz_0,pz_0,pz_0,pz_0,pz_0,pz_0,pz_0 }
	//};
	//Tablero_temp = Tablero_actual_;
}


int Cl_logica::analiza_jugada(vector<vector<PIEZA_STRU>> Tablero_actual_, GUI_jugada& jugada_propia, GUI_jugada& jugada_gravedad, bool jugada_erronea)
{
	//temporal

	int r= analiza_jugada___( Tablero_actual_,  jugada_propia, jugada_gravedad,  jugada_erronea);
	return r;


	// Se analiza si la "jugada_propia" es correcta en base a lo que contiene "Tablero_actual_" . Si no fuese correcta se devuelve 0

	auto t1 = Tablero_actual_;

	//.......................................
	//..............................

	//int control_test=partida_in.get_jugadas().size();
	int control_test = (rand() % 3) + 1;  // 

	/// control del test
	if (jugada_erronea)
		return 0;  // el parametro para testear jugada_erronea


	// ..........................



	//TEST "jugada_propia"
	jugada_propia = jugada_propia; // la jugada no tiene más piezas implicadas


	//TEST "jugada_gravedad"
	jugada_gravedad.vaciar_jugada();
	switch (control_test) {
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
		jugada_gravedad.jaque_mate = false;
		jugada_gravedad.add_pieza_a_jugada(pz);
		break;

	default:
		jugada_gravedad.jaque_mate = true;
		return 2;
	}

	//FIN TEST "jugada_gravedad"
	//return 2;
	return 1;

}

int Cl_logica::analiza_jugada___(vector<vector<PIEZA_STRU>> Tablero, GUI_jugada& jugada_propia, GUI_jugada& jugada_gravedad, bool jugada_erronea)
{
	_Tablero_actual = Tablero;
	bool ok = false;
	ENUM_TRAYECTO tipo_trayecto=TR_otro;
	//analiza posición pieza movida
	auto piezas= jugada_propia.get_lista_piezas_movidas();
	for (auto it_pz= piezas.begin(); it_pz != piezas.end(); ++it_pz)
	{// para cada pieza movida... En principio solamente debe haber una
		auto pz = (*it_pz);
		auto pz_pos_ant = busca_posicion_anterior(pz);  // donde estaba la pieza anteriormente
		auto pz_pos_des = _Tablero_actual.at(((int)pz.c_fila)-1).at(((int)pz.c_columna)-1);// quien hay en la posición destino

		int caso_destino=-1;
		if (pz_pos_des.c_color == pz.c_color)
			caso_destino = 1; //igual color
		if (pz_pos_des.c_color == blanca && pz.c_color == negra)
			caso_destino = 2; //distinto color --> come pieza
		if (pz_pos_des.c_color == negra && pz.c_color == blanca)
			caso_destino = 2; //distinto color --> come pieza
		if (pz_pos_des.c_color == color_NO)
			caso_destino = 3; //destino vacio


		if (caso_destino == 1)
			return -1; // CASO 1: salimos porque en la casilla destino hay una pieza del mismo color
			//////......................................................
		
		// ahora que se dispone de las dos posiciones de la pieza 
		// se analiza el movimiento en funcion del tipo de pieza
		int inc_f = (int)pz.c_fila - (int)pz_pos_ant.c_fila;
		int inc_c = (int)pz.c_columna - (int)pz_pos_ant.c_columna;
		tipo_trayecto = TR_otro;
		//analisis trayectoria (sera tipo torre, tipo alfil, o tipo caballo)
		if (abs(inc_f) == abs(inc_c))
			tipo_trayecto = TR_alfil;
		if(abs(inc_f)==0 || abs(inc_c) == 0)
			tipo_trayecto = TR_torre;
		if (  (abs(inc_f)==2 && abs(inc_c)==1) 
			||(abs(inc_f)==1 && abs(inc_c)==2))
			tipo_trayecto = TR_caballo;
		if (tipo_trayecto == TR_otro)
			return -2; // CASO 2: trayectoria ilegal


		// analisis de obstaculos en la trayectoria
		if (tipo_trayecto != TR_caballo)
		{
			int signo_inc_fila = 0;
			if (inc_f != 0)
				signo_inc_fila = (int)inc_f / (abs(inc_f)); // signo del incremento de la fila

			int signo_inc_columna = 0;
			if (inc_c != 0)
				signo_inc_columna = (int)inc_c / (abs(inc_c));  // signo del incremento de la columna

			int desplazamientos = max(abs(inc_f), abs(inc_c));

			for (int i = 1;i < desplazamientos;i++)
			{
				int inc_fila_i = i * signo_inc_fila;
				int inc_column_i = i * signo_inc_columna;
				int fila_origen = (int)pz_pos_ant.c_fila - 1;
				int columna_origen = (int)pz_pos_ant.c_columna - 1;

				auto pz_pos_tray = _Tablero_actual.at(fila_origen + inc_fila_i).at(columna_origen + inc_column_i);// quien hay en la posición de trayectoria
				if (pz_pos_tray.c_color != color_NO)
					return -3; // hay una pieza en la trayectoria

			}
		}
		


	
		switch (pz.c_tipo) {
			case peon:
				if (pz.c_color == blanca) {// los peones de blancas avanzan 
					if (inc_f == 1 && inc_c == 0 && caso_destino==3)  // avanza un casilla y estaba vacia
						ok = true;
					if (inc_f == 2 && inc_c == 0 && // avanza dos pasos
						caso_destino == 3 && 		// esta vacia la casilla destino	
						pz_pos_ant.c_fila == f2)			// estaba en la salida del peon 
						ok = true;
					if (inc_f == 1 && abs(inc_c) == 1 && // se avanza en diagonal
						caso_destino==2)				// comiendo pieza contraria
						ok = true;
				}
				else {  // los peones de negras retroceden
					if (inc_f == -1 && inc_c == 0 && caso_destino == 3)  // avanza un casilla y estaba vacia
							ok = true;
					if (inc_f == -2 && inc_c == 0 && // avanza dos pasos
						caso_destino == 3 && 		// esta vacia la casilla destino	
						pz_pos_ant.c_fila == f7)			// estaba en la salida del peon 
						ok = true;
					if (inc_f == -1 && abs(inc_c) == 1 && // se avanza en diagonal
						caso_destino == 2)				  // comiendo pieza contraria
						ok = true;
				};
				break;
			case torre:
				if(tipo_trayecto == TR_torre)  
					ok = true; 	break;
			case alfil:
				if (tipo_trayecto == TR_alfil)
					ok = true; 	break;
			case caballo:
				if (tipo_trayecto == TR_caballo)
					ok = true; 	break;
			case reina:
				if (tipo_trayecto == TR_torre || tipo_trayecto == TR_alfil)
					ok = true; 	break;
			case rey:
				if ((tipo_trayecto == TR_torre || tipo_trayecto == TR_alfil) && abs(inc_f)<2 && abs(inc_c) < 2)
					ok = true; 	break;
			default: 
				return 0;
		}
	}

	if (ok==true) return 1;

}

PIEZA_STRU Cl_logica::busca_posicion_anterior(PIEZA_STRU pieza_jugada) { //se devuelve la pieza en la posición anterior del tablero
	
	//// se busca la pieza en el tablero (según estaba antes de modificar el tablero)
	for (int ff = 0;ff < 8;ff++) {
		for (int cc = 0;cc < 8;cc++) {
			auto pp = _Tablero_actual.at(ff).at(cc);
			if (pp.c_pieza == pieza_jugada.c_pieza && pp.c_color == pieza_jugada.c_color) {
				//localizada la pieza en el tablero
				return pp;
			}
		}
	}// FIN de buscar la posición origen
	return pz_0; // si no se ha encontrado se devuelve pz_0
}
