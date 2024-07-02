#include "tablero.h"
#include "fichas.h"


tablero::tablero( int filas_, int columnas_){
    n_columnas = columnas_;
    n_filas = filas_;
    casilla cas = casilla(0, 0);
    tab= { {cas,cas,cas,cas,cas,cas,cas,cas},
    {cas,cas,cas,cas,cas,cas,cas,cas},
    {cas,cas,cas,cas,cas,cas,cas,cas},
    {cas,cas,cas,cas,cas,cas,cas,cas},
    {cas,cas,cas,cas,cas,cas,cas,cas},
    {cas,cas,cas,cas,cas,cas,cas,cas},
    {cas,cas,cas,cas,cas,cas,cas,cas},
    {cas,cas,cas,cas,cas,cas,cas,cas} };
    

}

//tablero::tablero(const int filas_, const int columnas_)// : n_filas(filas_), n_columnas(columnas_)
//{
//    n_filas = filas_;
//    n_columnas = columnas_;
//
//    // crear el tablero
//    matriz = new casilla * [filas_];
//    for (int i = 0; i < filas_; i++) {
//        matriz[i] = new casilla[columnas_];
//        for (int j = 0; j < columnas_; j++) {
//            matriz[i][j]=casilla(i,j);
//        }
//    }
//}

tablero::~tablero() {
    // Liberar la memoria del tablero
   /* int t;
    for (int i = 0; i < n_filas; ++i)
    {
        delete[] matriz[i];
    }
    delete[] matriz;*/
}



void tablero::gravedad() {
    for (int i = 0; i < n_columnas; i++) {
        for (int j = 1; j < n_filas; j++) {
            int resta = j - 1;
            while (this->tab.at(i).at(resta).ocupacion->leer_tipo() == t_NO && resta > -1) {
                resta--;
            }
            if (this->tab.at(i).at(resta+1).ocupacion->leer_tipo() == t_NO) {
                this->tab.at(i).at(resta+1).ocupacion = this->tab.at(i).at(j).ocupacion;
                Vacia v = Vacia();
                this->tab.at(i).at(j).ocupacion = &v;
            }
        }
    }

}


ficha* tablero::encontrar_rey(const ENUM_COLOR& c) const {
    ficha* aux;

    for (int i = 0; i < n_filas; i++) {
        for (int j = 0; j < n_columnas; j++) {
            aux = tab.at(i).at(j).ocupacion;
            aux->posicion = tab.at(i).at(j).ocupacion->posicion;
                if (aux->leer_color() == c && aux->leer_tipo() == rey) {

                    return aux;
                }
        }
    }
}