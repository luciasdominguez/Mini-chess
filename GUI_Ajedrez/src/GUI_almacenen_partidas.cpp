#include "GUI_almacenen_partidas.h"
#include <fstream>
#include <json.hpp>
using json = nlohmann::json;


GUI_almacenen_partidas::GUI_almacenen_partidas()
{
    string line;
    ifstream fichero_text("nada.txt");
    if (fichero_text.is_open())
    {
        while (getline(fichero_text, line))
        {
            cout << line << '\n';
        }
        fichero_text.close();
    }
    else cout << "Fichero de test no se ha podido abrir";


    std::ifstream fichero_partidas("partida_ejemplo_0.json");
    string partidas_json;
    json partidas_json_datos;
    partidas_json.erase();
    if (fichero_partidas.is_open())
    {
        while (getline(fichero_partidas, line))
        {
            partidas_json.append(line) ;
        }
        fichero_partidas.close();
        partidas_json_datos = nlohmann::json::parse(partidas_json);
        //cout << partidas_json_datos;
        cout << std::setw(4) << partidas_json_datos << '\n';  //salida con formato
    }
    else cout << "Fichero JSON de partidas no se ha podido abrir";
    
    // asignacion de cadenas a enum y viceversa. En las macros del .h estan todas las conversiones
    //json E_J_f1 = f1; assert(E_J_f1 == "f1");  // la cademna f1 se la asigna el tipo f1
    //json J_E_f1 = "f1"; assert(J_E_f1.template get<ENUM_FILA>() == J_E_f1);
    GUI_partida partida;
    vector<GUI_movimiento> movimientos;

    for (auto it_part = partidas_json_datos.begin(); it_part != partidas_json_datos.end(); ++it_part)
    {
        auto js_partida = it_part.value();
        auto js_movimientos = js_partida["movimientos"];
        auto nombre_partida = js_partida["nombre"];
        partida.set_nombre(nombre_partida);
        //---------------
        GUI_movimiento nuevo_movimiento;
        for (auto it_mov = js_movimientos.begin(); it_mov != js_movimientos.end(); ++it_mov)
        {
            auto js_movimiento = it_mov.value();
            auto numero   =   js_movimiento["movi"];
            auto jugador  =   js_movimiento["jugador"]; 
            auto js_piezas=   js_movimiento["piezas"];
            nuevo_movimiento.set_jugador(jugador);
            nuevo_movimiento.vaciar_movimiento();
            PIEZA_STRU nueva_pieza;
            for (auto it_pz = js_piezas.begin(); it_pz != js_piezas.end(); ++it_pz)
            {
                auto js_pieza   = it_pz.value();
                auto tipo       = js_pieza["tipo"];
                auto color      = js_pieza["color"];
                auto pieza      = js_pieza["pieza"];
                auto fila       = js_pieza["fila"];
                auto columna    = js_pieza["columna"];
                nueva_pieza.c_color     = color;
                nueva_pieza.c_tipo      = tipo;
                nueva_pieza.c_pieza     = pieza;
                nueva_pieza.c_fila      = fila;
                nueva_pieza.c_columna   = columna;
                nuevo_movimiento.add_pieza_a_movimiento(nueva_pieza);
            }
            partida.add_movimiento_a_partida(nuevo_movimiento);
            
        };
        almacen_de_partidas.push_back(partida);
    }





    //using json = nlohmann::json;



   //j_partidas["nombre"]= almacen_de_partidas.

 

}

bool GUI_almacenen_partidas::inserta_partida(string nombre_partida, vector<GUI_movimiento> lista_movis)
{
    // se busca si existe. 
    bool partida_existe = false;
    for (auto it_in = almacen_de_partidas.begin(); it_in != almacen_de_partidas.end(); ++it_in)
    {
        string nm = (*it_in).get_nombre();
        if (nm == nombre_partida) partida_existe = true;
    }
    if (!partida_existe) {  // si no existe se inserta al final de la lista.
        GUI_partida _partida;
        _partida.set_nombre(nombre_partida);
        _partida.set_partida(lista_movis);
        almacen_de_partidas.push_back(_partida);
        return true;
    }
    else {  //Si YA existe se devuelve FALSE
        return false;
    }
 
}


void GUI_almacenen_partidas::nuevo_movimiento(vector<PIEZA_STRU> posiciones)
{
}

vector<GUI_movimiento> GUI_almacenen_partidas::get_or_new_partida(string _nombre)
{    // se busca la partida en la lista de partida y se devuelve si existe.
    vector<GUI_movimiento> aux;
    bool existe_la_partida=false;
    for (auto it_in = almacen_de_partidas.begin(); it_in != almacen_de_partidas.end(); ++it_in) 
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
        almacen_de_partidas.push_back(nueva_partida);  // se añade a la lista de partidas
        return nueva_partida.get_movimientos();
    }
 
}

vector<GUI_movimiento> GUI_almacenen_partidas::get_partida_ejemplo()
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

