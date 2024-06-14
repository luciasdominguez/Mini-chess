#pragma once
#include "freeglut.h"
#include "GUI_Tablero.h"
#include "GUI_pieza.h"
#include "GUI_marcador.h"
#include "Juego.h"

Juego juego;
//vector<GUI_movimiento> partida;
int movimientos_partida = 0;
int movimientos_partida_ahora = 0;
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
	int tam_partida = juego.get_partida().size();
	switch (key)
	{
	case 'a':  // se carga una partida ejemplo (la lista de los movimientos)
		juego.cargar_partida("P1");
		juego.carga_partida_al_GUI(0);
		movimientos_partida = juego.get_partida().size();
		movimientos_partida_ahora = juego.get_partida().size();
		break;
	case 'e':  // se carga una partida ejemplo (la lista de los movimientos)
		juego.cargar_partida_ejemplo();
		juego.carga_partida_al_GUI(0);
		movimientos_partida = juego.get_partida().size();
		movimientos_partida_ahora = juego.get_partida().size();
		break;
	case 'n': 
		//Se genera la partida con el nombre "Nueva" con las posiciones iniciales
		juego.cargar_partida("Nueva"); 
		juego.carga_partida_al_GUI(0);
		movimientos_partida = juego.get_partida().size();
		movimientos_partida_ahora = juego.get_partida().size();
		break;
	case '-':
		//partida = juego.get_partida();
		if (tam_partida >0) // error -------- se debe gestionar si no hay partida
		{
			movimientos_partida_ahora--;
			if (movimientos_partida_ahora < 1) movimientos_partida_ahora = 1;
			if (movimientos_partida_ahora > movimientos_partida) movimientos_partida_ahora = movimientos_partida;
			juego.carga_partida_al_GUI(movimientos_partida_ahora);

		}
		if (movimientos_partida_ahora < movimientos_partida) {
			juego.get_casilla_cursor()->reset_cursor_casilla();
		}
		//juego.gestion_nuevo_turno();
		break;
	case '+':
		//partida = juego.get_partida();
		if (tam_partida > 0) // error -------- se debe gestionar si no hay partida ---
		{
			movimientos_partida_ahora++;
			if (movimientos_partida_ahora < 1) movimientos_partida_ahora = 1;
			if (movimientos_partida_ahora > movimientos_partida) movimientos_partida_ahora = movimientos_partida;
			juego.carga_partida_al_GUI(movimientos_partida_ahora);
			//juego.get_jugador_actual();
		}
		if (movimientos_partida_ahora < movimientos_partida) {
			juego.get_casilla_cursor()->reset_cursor_casilla();
		}
		juego.turno_();
		break;
	case '5':
		juego.check_pieza_movible();   // verfica si en la casilla hay una pieza movible
		juego.get_casilla_cursor()->switch_cursor_casilla();
 		break;
	case '.':
		if (juego.get_pieza_locked() != nullptr)  // que haya una pieza
		{
			auto pz_lck = juego.get_pieza_locked();
			switch (juego.get_casilla_locked()->get_estado_locked())
			{
			case ROJO:
				if(juego.get_casilla_cursor()->get_fila()    == juego.get_casilla_locked()->get_fila() &&
				   juego.get_casilla_cursor()->get_columna() == juego.get_casilla_locked()->get_columna())
				   // solo se puede cambiar a naranja si estoy en la casilla original que permitió el cambio a ROJO
				   juego.get_casilla_locked()->set_estado_locked(NARANJA, pz_lck);
				break;
			case NARANJA:
				juego.get_casilla_locked()->set_estado_locked(ROJO, pz_lck);
			};
		};
		break;
	case '0':
		if (juego.get_pieza_locked() != nullptr)  // que haya una pieza locked
		{	//se carga el movimiento en la posición de la partida en la que nos
			// encontremos. Los movimientos que hubieran después son borrados.
			juego.mueve_pieza_locked(movimientos_partida_ahora);
			movimientos_partida = juego.get_partida().size();
			movimientos_partida_ahora= juego.get_partida().size();
			juego.get_casilla_locked()->set_estado_locked(TRANS,nullptr);
			auto j=juego.get_jugador_actual();
			juego.carga_partida_al_GUI(0);
		}
		break;
	case '*': // que pase turno la gravedad
		juego.avanza_siguiente_turno();
		juego.carga_partida_al_GUI(0);
		break;
	case '8':
		juego.get_casilla_cursor()->incrementa_posicion(0, 1);juego.check_pieza_movible();
		break;
	case '9':
		juego.get_casilla_cursor()->incrementa_posicion(-1, 1);juego.check_pieza_movible();
		break;
	case '6':
		juego.get_casilla_cursor()->incrementa_posicion(-1, 0);juego.check_pieza_movible();
		break;
	case '3':
		juego.get_casilla_cursor()->incrementa_posicion(-1, -1);juego.check_pieza_movible();
		break;
	case '2':
		juego.get_casilla_cursor()->incrementa_posicion(0, -1);juego.check_pieza_movible();
		break;
	case '1':
		juego.get_casilla_cursor()->incrementa_posicion(1, -1);juego.check_pieza_movible();
		break;
	case '4':
		juego.get_casilla_cursor()->incrementa_posicion(1, 0);juego.check_pieza_movible();
		break;
	case '7':
		juego.get_casilla_cursor()->incrementa_posicion(1, 1);juego.check_pieza_movible();
		break;
	case ' ':
		juego.generar_listado_datos_piezas_OFF();  //Para poner todas la piezas en el almacén
		break;
	}
}

void OnTimer(int value)
{

	//no borrar estas lineas
	glutTimerFunc(25, OnTimer, 0);
	glutPostRedisplay();

}