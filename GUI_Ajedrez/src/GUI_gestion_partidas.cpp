#include "GUI_gestion_partidas.h"

GUI_gestion_partidas::GUI_gestion_partidas()
{
    string line;
    ifstream fichero_partidas("partidas.txt");
    if (fichero_partidas.is_open())
    {
        while (getline(fichero_partidas, line))
        {
            cout << line << '\n';
        }
        fichero_partidas.close();
    }
    else cout << "Fichero de partidas no se ha podido abrir";

}

bool GUI_gestion_partidas::inserta_partida(string nombre_partida, vector<GUI_movimiento> lista_movis)
{
    // se busca si existe. 
    bool partida_existe = false;
    for (auto it_in = Lista_de_partidas.begin(); it_in != Lista_de_partidas.end(); ++it_in)
    {
        string nm = (*it_in).get_nombre();
        if (nm == nombre_partida) partida_existe = true;
    }
    if (!partida_existe) {  // si no existe se inserta al final de la lista.
        GUI_partida _partida;
        _partida.set_nombre(nombre_partida);
        _partida.set_partida(lista_movis);
        Lista_de_partidas.push_back(_partida);
        return true;
    }
    else {  //Si YA existe se devuelve FALSE
        return false;
    }
 
}


void GUI_gestion_partidas::nuevo_movimiento(vector<PIEZA_STRU> posiciones)
{
}

vector<GUI_movimiento> GUI_gestion_partidas::get_or_new_partida(string _nombre)
{    // se busca la partida en la lista de partida y se devuelve si existe.
    vector<GUI_movimiento> aux;
    bool existe_la_partida=false;
    for (auto it_in = Lista_de_partidas.begin(); it_in != Lista_de_partidas.end(); ++it_in) 
    {
        if ((*it_in).get_nombre() == _nombre) {  // (*it_in) es una partida
            aux =(*it_in).get_movimientos(); // cogemos los movimientos de la partida encontrada
            existe_la_partida = true;
            return aux;
        }
    };
    // ------ si la partida no existe, se genera una partida nueva con el primer movimiento=todo al inicio
    if (!existe_la_partida) 
    {
        GUI_partida nueva_partida;
        GUI_movimiento posicion_de_salida;
        posicion_de_salida.inicio_partida(); // se generan los movimientos de la posición de salida
        nueva_partida.set_nombre(_nombre);  // se establece el nombre a la partida
        nueva_partida.add_movimiento_a_partida(posicion_de_salida);  // se añade a la partida la posición de salida
        Lista_de_partidas.push_back(nueva_partida);  // se añade a la lista de partidas
        return nueva_partida.get_movimientos();
    }
 
}

vector<GUI_movimiento> GUI_gestion_partidas::get_partida_ejemplo()
{
    GUI_partida nueva_partida;
    GUI_movimiento movimiento;
    movimiento.ejemplo_movi_01(); // se añade un movimiento
    nueva_partida.add_movimiento_a_partida(movimiento);
    movimiento.ejemplo_movi_02(); // se añade un movimiento
    nueva_partida.add_movimiento_a_partida(movimiento);
    movimiento.ejemplo_movi_03(); // se añade un movimiento
    nueva_partida.add_movimiento_a_partida(movimiento);
    movimiento.ejemplo_movi_04(); // se añade un movimiento
    nueva_partida.add_movimiento_a_partida(movimiento);

    return nueva_partida.get_movimientos();
}

