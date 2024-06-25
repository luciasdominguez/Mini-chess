#pragma once
#include "freeglut.h"
#include "GUI_Tablero.h"
#include "GUI_pieza.h"
#include "GUI_marcador.h"
#include "Juego.h"
#include "aux.h"

Juego juego;
//vector<GUI_movimiento> partida;
int n_jugadas_partida = 0;
int index_jugada_en_partida = 0;
int indice_movimientos_partida = 0;


//los callback, funciones que seran llamadas automaticamente por la glut
//cuando sucedan eventos
//NO HACE FALTA LLAMARLAS EXPLICITAMENTE
void OnDraw(void);		 //esta funcion sera llamada para dibujar
void OnTimer(int value); //esta funcion sera llamada cuando transcurra una temporizacion
void OnKeyboardDown(unsigned char key, int x, int y); //cuando se pulse una tecla	


int main(int argc, char* argv[])
{
	//Inicializar el gestor de ventanas GLUT
	//y crear la ventana
	glutInit(&argc, argv);
	glutInitWindowSize(800, 600);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Ajedrez gravitatorio");

	//habilitar luces y definir perspectiva
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(40.0, 800 / 600.0f, 0.1, 150);

	
	//Registrar los callbacks
	glutDisplayFunc(OnDraw);
	glutTimerFunc(25, OnTimer, 0);//le decimos que dentro de 25ms llame 1 vez a la funcion OnTimer()
	glutKeyboardFunc(OnKeyboardDown);

	//pasarle el control a GLUT,que llamara a los callbacks
	glutMainLoop();

	return 0;
}

void OnDraw(void)
{
	//Borrado de la pantalla	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Para definir el punto de vista
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0.0, 7.5, 35,  // posicion del ojo
		0.0, 7.5, 0.0,      // hacia que punto mira  (0,0,0) 
		0.0, 1.0, 0.0);      // definimos hacia arriba (eje Y)    

	//dibujo del tablero con las piezas en sus posiciones, los cursores...
	juego.dibuja_juego();

	/////////////////////////////////////////
	//no borrar esta linea ni poner nada despues
	glutSwapBuffers();
}

void OnKeyboardDown(unsigned char key, int x_t, int y_t)
{
	string s = getDate();
	vector<string> L;
	vector<PIEZA_STRU> lista_Piezas;
	bool en_el_final_partida = false;
	GUI_jugada jugada_final;
	vector<GUI_jugada> jugadas;
	GUI_partida partida_aux;

	if (juego.get_selector_partidas_jugadas() == modo_seleccion_partida)
	{  // operativa del teclado en estado de "seleccion_partida"
		switch (key)
		{

		case 's': // 
			juego.carga_partida_al_GUI(-1, true);
			juego.get_almacen_partidas().actualiza_objeto_json();
			exit(0);
			break;
		case 'n':  
			//Se genera la partida con el nombre del día y la hora. Contiene las posiciones iniciales de un partida normal
			juego.cargar_partida(s);
			jugadas = juego.get_partida_actual().get_jugadas();
			n_jugadas_partida = juego.get_N_jugadas_partida_actual();
			index_jugada_en_partida = n_jugadas_partida-1;
			juego.cambia_selector_partidas_jugadas();  // se cambia a "modo juego"
			juego.carga_partida_al_GUI(-1,true);
			break;
		case 'e':  // se carga una partida ejemplo (la lista de los movimientos)
			juego.cargar_partida_ejemplo();
			n_jugadas_partida = juego.get_N_jugadas_partida_actual();
			index_jugada_en_partida = n_jugadas_partida-1;
			juego.cambia_selector_partidas_jugadas();  // se canbia a "modo juego"
			juego.carga_partida_al_GUI(-1,true);
			break;

		case 'j': // se pasa a "modo juego"
			n_jugadas_partida = juego.get_N_jugadas_partida_actual();
			if (n_jugadas_partida!=0) {
				juego.cambia_selector_partidas_jugadas();
				juego.carga_partida_al_GUI(-1, true);
			}

			//////if (juego.get_partida_actual().get_jaque_mate()) {
			//////	juego.cambia_selector_partidas_jugadas();
			//////	juego.carga_partida_al_GUI(1, true);
			//////}
			break;

		case '1':  case '2':  case '3': case '4': case '5':   case '6': case '7': case '8': case '9':
			auto aux = juego.get_listado_partidas().get_nombres_partidas();
			int i = (int)key - 48;
			if (i <= aux.size()) {
				string S = aux.at(i - 1);
				string S2=S.substr(3);
				juego.cargar_partida(S2);
				n_jugadas_partida = juego.get_N_jugadas_partida_actual();
				index_jugada_en_partida = n_jugadas_partida-1;
				juego.carga_partida_al_GUI(-1, true);
			}
			else { // que suene un aviso

			};
			break;
	
		}

	}
	else  // operativa del teclado en estado de "jugadas"
	{
		int tam_partida = juego.get_partida_actual().get_jugadas().size();

		switch (key)
		{
		//case 's': // se pasa a estado de "jugadas
		//	juego.get_almacen_partidas().actualiza_objeto_json();
		//	exit(0);
		//	break;
		case 'z':
			//L = juego.get_partida_actual().get_lista_movimientos();
			//juego.get_listado_jugadas().set_nombres_jugadas(L);
			break;

		case 'n':
			//////Se genera la partida con el nombre "Nueva" con las posiciones iniciales
			////juego.cargar_partida("Nueva");
			////juego.carga_partida_al_GUI(0);
			////jugadas_partida = juego.get_partida().get_jugadas().size();
			////jugadas_partida_ahora = jugadas_partida;
			break;

		case 'p': // se pasa a estado de seleccionar partida
			juego.cambia_selector_partidas_jugadas();
			juego.carga_partida_al_GUI(1, true);
			break;

		case '-':
			//partida = juego.get_partida();
			juego.get_casilla_cursor()->reset_cursor_casilla();
			en_el_final_partida = false;
			n_jugadas_partida = juego.get_N_jugadas_partida_actual();
			if (tam_partida > 0) // error -------- se debe gestionar si no hay partida
			{
				index_jugada_en_partida--;
				if (index_jugada_en_partida < 0)  
						index_jugada_en_partida = 0;
				if (index_jugada_en_partida > (n_jugadas_partida-1)) 
						index_jugada_en_partida = (n_jugadas_partida-1);
				if (index_jugada_en_partida == (n_jugadas_partida-1)) 
						en_el_final_partida = true;
				juego.get_msg_jaque_mate()->set_ver_jaque_mate(false);
				juego.carga_partida_al_GUI(index_jugada_en_partida, en_el_final_partida);

			}

			//juego.turno_();
			//juego.gestion_nuevo_turno();
			break;

		case '+':
			//partida = juego.get_partida();
			en_el_final_partida = false;
			juego.get_casilla_cursor()->reset_cursor_casilla();
			n_jugadas_partida = juego.get_N_jugadas_partida_actual();
			if (tam_partida > 0) // error -------- se debe gestionar si no hay partida ---
			{
				index_jugada_en_partida++;
				if (index_jugada_en_partida < 0) index_jugada_en_partida = 0;
				if (index_jugada_en_partida >= (n_jugadas_partida-1)) {
					// Si se intenta ir mas alla de la ultima partida hay que 
					// cargar la ultima partida pero el turno siguiente
					en_el_final_partida = true;
					index_jugada_en_partida = n_jugadas_partida-1;
				}
	
	
				juego.carga_partida_al_GUI(index_jugada_en_partida, en_el_final_partida);

				if (juego.get_jugador_actual() == BLANCAS || juego.get_jugador_actual() == NEGRAS)
				{
					juego.get_casilla_cursor()->reset_cursor_casilla();
					juego.get_casilla_cursor()->switch_cursor_casilla();
				}

			}
			if (index_jugada_en_partida < (n_jugadas_partida-1)) {
				juego.get_casilla_cursor()->reset_cursor_casilla();
			}
			//juego.turno_();
			break;

		case '5': // activación del cursor para ir a seleccionar una pieza
			
			if ((index_jugada_en_partida == n_jugadas_partida - 1) &&  // Si estamos en una jugada que no sea la ultima (de momento) no se puede activar el cursor
				(juego.get_jugador_actual() == BLANCAS || juego.get_jugador_actual() == NEGRAS) // Si juegan BLANCAS o NEGRAS
				&& juego.get_msg_jaque_mate()->get_ver_jaque_mate() == false
				)
				{
					juego.check_pieza_movible();   // verfica si en la casilla hay una pieza movible
					if (juego.get_casilla_locked()->get_estado_locked() != ROJO)
						juego.get_casilla_cursor()->switch_cursor_casilla();
				};
			break;

		case '.':  //seleccion de pieza que se quiere mover
			if (juego.get_pieza_locked() != nullptr && juego.get_msg_jaque_mate()->get_ver_jaque_mate() == false)  // que haya una pieza
			{
				auto pz_lck = juego.get_pieza_locked();
				auto estado_locked = juego.get_casilla_locked()->get_estado_locked();
				switch (estado_locked)
				{
				case ROJO:
					if (juego.get_casilla_cursor()->get_fila() == juego.get_casilla_locked()->get_fila() &&
						juego.get_casilla_cursor()->get_columna() == juego.get_casilla_locked()->get_columna())
						// solo se puede cambiar a naranja si estoy en la casilla original que permitió el cambio a ROJO
							juego.get_casilla_locked()->set_estado_locked(NARANJA, pz_lck);
					break;
				case NARANJA:
					juego.get_casilla_locked()->set_estado_locked(ROJO, pz_lck);
				};
			};
			break;
			//juego.get_msg_jaque_mate()->set_ver_mensaje
		case '0':  // ejecución del movimiento de la pieza seleccionada previamente
			if (juego.get_pieza_locked() != nullptr && juego.get_msg_jaque_mate()->get_ver_jaque_mate()==false)  
				// Que haya una pieza locked y no sea fin por jaque mate
			{	//se carga la jugada en la posición de la partida en la que nos
				// encontremos. Los movimientos que hubieran después son borrados.
				index_jugada_en_partida = juego.get_partida_actual().get_jugadas().size()-1;
				juego.mueve_pieza_locked(index_jugada_en_partida);
				n_jugadas_partida = juego.get_partida_actual().get_jugadas().size();
				juego.get_casilla_locked()->set_estado_locked(TRANS, nullptr);
				auto j = juego.get_jugador_actual();
				juego.guarda_partida_actual();
				index_jugada_en_partida = juego.get_partida_actual().get_jugadas().size()-1;
				n_jugadas_partida = juego.get_partida_actual().get_jugadas().size();
				partida_aux = juego.get_partida_actual();
				juego.get_casilla_cursor()->reset_cursor_casilla();
				juego.carga_partida_al_GUI(-1,true);  //aqui se calcula a quien le toca el siguiente turno
				//juego.avanza_turno(); // se actualiza a quien le toca mover como turno actual

				jugada_final = juego.get_partida_actual().get_jugadas().back();
				juego.jugada_gravedad.vaciar_jugada();

				// test 
				int test = 0;
				if (j == BLANCAS) test = 1; else test = 2;
				test = 3;
				// fin test

				auto partida_act = juego.get_partida_actual();

				int resultado_jugada = juego.logica.analiza_jugada(partida_act, jugada_final, juego.jugada_gravedad, test);
				// La función ha devuelto en la primera variable todas las piezas que se han movido debido al movimiento intruducida
				// La función ha devuelto en la segunda variable todas las piezas que mueve la gravedad	
				
				switch (resultado_jugada) {
					case 0: 
						// La jugada era ilegal
						juego.jugada_gravedad.vaciar_jugada();
						juego.get_msg_jaque_mate()->set_ver_jaque_mate(false);
						break;
					case 1:
						// Si el analisis es correcto se actualiza la jugada actual (puede afectar a otras piezas)
						//.....
						// ....
						// 
						juego.get_msg_jaque_mate()->set_ver_jaque_mate(false);
						//
						break;
					case 2:
						// fin de partida por jaque mate
						//...

						// partida_act.set_jaque_mate(true);
						//juego.get_partida_actual().set_jaque_mate(true);

						partida_act = juego.get_partida_actual();
						//bbb juego.jaque_mate_partida_actual(true);
						
						//juego.get_partida_actual().get_jugadas().
						juego.carga_partida_al_GUI(1, true);

						//juego.cambia_selector_partidas_jugadas();
						//juego.
						break;
				}
		
			}
			break;

		case '*': // que juegue la gravedad

			if (juego.get_jugador_actual() == GRAVEDAD_B || juego.get_jugador_actual() == GRAVEDAD_N)
			{  // Si le toca a la gravedad ....
				lista_Piezas.clear();
				lista_Piezas = juego.jugada_gravedad.get_lista_piezas_movidas();
				index_jugada_en_partida = juego.get_partida_actual().get_jugadas().size()-1;
				jugadas = juego.get_partida_actual().get_jugadas();
				juego.add_jugada_libre(index_jugada_en_partida+1, lista_Piezas, juego.jugada_gravedad.jaque_mate);
				index_jugada_en_partida = juego.get_partida_actual().get_jugadas().size()-1;
				n_jugadas_partida = juego.get_partida_actual().get_jugadas().size();
				partida_aux = juego.get_partida_actual();
				jugadas = juego.get_partida_actual().get_jugadas();
				juego.guarda_partida_actual();
				juego.get_casilla_cursor()->reset_cursor_casilla();
				juego.get_casilla_cursor()->switch_cursor_casilla();

				juego.get_msg_jaque_mate()->set_ver_jaque_mate(juego.jugada_gravedad.jaque_mate);
				juego.carga_partida_al_GUI(-1, true);


				//juego.avanza_turno();
			}

			break;
		case '8':

			if ((index_jugada_en_partida == n_jugadas_partida - 1) &&  // Si estamos en una jugada que no sea la ultima (de momento) no se puede activar el cursor
				(juego.get_jugador_actual() == BLANCAS || juego.get_jugador_actual() == NEGRAS) // Si juegan BLANCAS o NEGRAS
				&& juego.get_msg_jaque_mate()->get_ver_jaque_mate() == false
				)
			{
				juego.get_casilla_cursor()->incrementa_posicion(0, 1);
				if (juego.get_casilla_locked()->get_estado_locked() == NARANJA)
					juego.reset_pieza_locked();
				juego.check_pieza_movible();
			}
			break;
		case '9':
			if ((index_jugada_en_partida == n_jugadas_partida - 1) &&  // Si estamos en una jugada que no sea la ultima (de momento) no se puede activar el cursor
				(juego.get_jugador_actual() == BLANCAS || juego.get_jugador_actual() == NEGRAS) // Si juegan BLANCAS o NEGRAS
				&& juego.get_msg_jaque_mate()->get_ver_jaque_mate() == false
				)
			{
				juego.get_casilla_cursor()->incrementa_posicion(-1, 1);
				if (juego.get_casilla_locked()->get_estado_locked() == NARANJA)
					juego.reset_pieza_locked();
				juego.check_pieza_movible();
			}
			break;
		case '6':
			if ((index_jugada_en_partida == n_jugadas_partida - 1) &&  // Si estamos en una jugada que no sea la ultima (de momento) no se puede activar el cursor
				(juego.get_jugador_actual() == BLANCAS || juego.get_jugador_actual() == NEGRAS) // Si juegan BLANCAS o NEGRAS
				&& juego.get_msg_jaque_mate()->get_ver_jaque_mate() == false
				)
			{
				juego.get_casilla_cursor()->incrementa_posicion(-1, 0);
				if (juego.get_casilla_locked()->get_estado_locked() == NARANJA)
					juego.reset_pieza_locked();
				juego.check_pieza_movible();
			}
			break;
		case '3':
			if ((index_jugada_en_partida == n_jugadas_partida - 1) &&  // Si estamos en una jugada que no sea la ultima (de momento) no se puede activar el cursor
				(juego.get_jugador_actual() == BLANCAS || juego.get_jugador_actual() == NEGRAS) // Si juegan BLANCAS o NEGRAS
				&& juego.get_msg_jaque_mate()->get_ver_jaque_mate() == false
				)
			{
				juego.get_casilla_cursor()->incrementa_posicion(-1, -1);
				if (juego.get_casilla_locked()->get_estado_locked() == NARANJA)
					juego.reset_pieza_locked();
				juego.check_pieza_movible();
			}
			break;
		case '2':
			if ((index_jugada_en_partida == n_jugadas_partida - 1) &&  // Si estamos en una jugada que no sea la ultima (de momento) no se puede activar el cursor
				(juego.get_jugador_actual() == BLANCAS || juego.get_jugador_actual() == NEGRAS) // Si juegan BLANCAS o NEGRAS
				&& juego.get_msg_jaque_mate()->get_ver_jaque_mate() == false
				)
			{
				juego.get_casilla_cursor()->incrementa_posicion(0, -1);
				if (juego.get_casilla_locked()->get_estado_locked() == NARANJA)
					juego.reset_pieza_locked();
				juego.check_pieza_movible();
			}
			break;
		case '1':
			if ((index_jugada_en_partida == n_jugadas_partida - 1) &&  // Si estamos en una jugada que no sea la ultima (de momento) no se puede activar el cursor
				(juego.get_jugador_actual() == BLANCAS || juego.get_jugador_actual() == NEGRAS) // Si juegan BLANCAS o NEGRAS
				&& juego.get_msg_jaque_mate()->get_ver_jaque_mate() == false
				)
			{
				juego.get_casilla_cursor()->incrementa_posicion(1, -1);
				if (juego.get_casilla_locked()->get_estado_locked() == NARANJA)
					juego.reset_pieza_locked();
				juego.check_pieza_movible();
			}
			break;

		case '4':
			if ((index_jugada_en_partida == n_jugadas_partida - 1) &&  // Si estamos en una jugada que no sea la ultima (de momento) no se puede activar el cursor
				(juego.get_jugador_actual() == BLANCAS || juego.get_jugador_actual() == NEGRAS) // Si juegan BLANCAS o NEGRAS
				&& juego.get_msg_jaque_mate()->get_ver_jaque_mate() == false
				)
			{
				juego.get_casilla_cursor()->incrementa_posicion(1, 0);
				if (juego.get_casilla_locked()->get_estado_locked() == NARANJA)
					juego.reset_pieza_locked();
				juego.check_pieza_movible();
			}
			break;

		case '7':
			if ((index_jugada_en_partida == n_jugadas_partida - 1) &&  // Si estamos en una jugada que no sea la ultima (de momento) no se puede activar el cursor
				(juego.get_jugador_actual() == BLANCAS || juego.get_jugador_actual() == NEGRAS) // Si juegan BLANCAS o NEGRAS
				&& juego.get_msg_jaque_mate()->get_ver_jaque_mate() == false
				)
			{
				juego.get_casilla_cursor()->incrementa_posicion(1, 1);
				if (juego.get_casilla_locked()->get_estado_locked() == NARANJA)
					juego.reset_pieza_locked();
				juego.check_pieza_movible();
			}
			break;

		case ' ':
			juego.generar_listado_datos_piezas_OFF();  //Para poner todas la piezas en el almacén
			break;
		}
	}
}

void OnTimer(int value)
{

	//no borrar estas lineas
	glutTimerFunc(25, OnTimer, 0);
	glutPostRedisplay();

}
