#include "tablero.h"
#include "fichas.h"


tablero::tablero( int filas_, int columnas_){
    n_columnas = columnas_;
    n_filas = filas_;
    casilla cas = casilla(0, 0);
    casillas_tablero= { {cas,cas,cas,cas,cas,cas,cas,cas},
    {cas,cas,cas,cas,cas,cas,cas,cas},
    {cas,cas,cas,cas,cas,cas,cas,cas},
    {cas,cas,cas,cas,cas,cas,cas,cas},
    {cas,cas,cas,cas,cas,cas,cas,cas},
    {cas,cas,cas,cas,cas,cas,cas,cas},
    {cas,cas,cas,cas,cas,cas,cas,cas},
    {cas,cas,cas,cas,cas,cas,cas,cas} };
    

}



tablero::~tablero() {
    // Liberar la memoria del tablero
   
}



void tablero::gravedad() {
   

}


ficha* tablero:: encontrar_rey(const ENUM_COLOR& c) const {
    ficha* aux;
    for (int i = 0; i < n_filas; i++) {
        for (int j = 0; j < n_columnas; j++) {
            aux = casillas_tablero.at(i).at(j).ocupacion;
            if (casillas_tablero.at(i).at(j).ocupacion) {
                aux->posicion = casillas_tablero.at(i).at(j).ocupacion->posicion;
                if (aux->leer_color() == c && aux->leer_tipo() == rey) {
                  //  aux->set_pos(casillas_tablero.at(i).at(j));
                    return aux;
                }
            }
        }
    }
}
casilla tablero::encontrar_pos_rey(const ENUM_COLOR& c) {
    ficha* aux;
    for (int i = 0; i < n_filas; i++) {
        for (int j = 0; j < n_columnas; j++) {
            aux = casillas_tablero.at(i).at(j).ocupacion;
            if (casillas_tablero.at(i).at(j).ocupacion) {
                aux->posicion = casillas_tablero.at(i).at(j).ocupacion->posicion;
                if (aux->leer_color() == c && aux->leer_tipo() == rey) {

                    return casillas_tablero.at(i).at(j);
                }
            }
        }
    }
}


tablero tablero::simular_gravedad() const {
    tablero tablero_con_gravedad = *this;

    for (int i = 7; i > 0; i--) {
        for (int j = 0; j < n_columnas; j++) {
            if (tablero_con_gravedad.casillas_tablero[i][j].leer_ocupacion() && !tablero_con_gravedad.casillas_tablero[i-1][j].leer_ocupacion()) {
                tablero_con_gravedad.casillas_tablero[i - 1][j].ocupacion = tablero_con_gravedad.casillas_tablero[i][j].ocupacion;
                tablero_con_gravedad.casillas_tablero[i][j].ocupacion = nullptr;
            }
        }
    }
    return tablero_con_gravedad;
}
