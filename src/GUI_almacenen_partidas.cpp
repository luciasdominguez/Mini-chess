#pragma once
#include "GUI_almacenen_partidas.h"



GUI_gestor_partidas::GUI_gestor_partidas()
{
    string line;

    std::ifstream fichero_json_partidas("lista_de_partidas_jq_v2.json");
    string partidas_json_en_texto;

    partidas_json_en_texto.erase();
    if (fichero_json_partidas.is_open())
    {
        while (getline(fichero_json_partidas, line))
        {
            partidas_json_en_texto.append(line) ;
        }
        fichero_json_partidas.close();
        partidas_json = nlohmann::json::parse(partidas_json_en_texto);
        //cout << partidas_json_datos;

        //cout << std::setw(4) << partidas_json << '\n';  //salida con formato
    }
    else cout << "Fichero JSON de partidas no se ha podido abrir";
    
    // asignacion de cadenas a enum y viceversa. En las macros del .h estan todas las conversiones

    GUI_partida partida;

    for (auto it_part = partidas_json.begin(); it_part != partidas_json.end(); ++it_part)
    {
        auto js_partida = it_part.value();          // partida en el json
        auto js_jugadas = js_partida["jugadas"];    // jugadas de la partida en el json
        auto nombre_partida = js_partida["nombre"];
        auto jaque_mate = js_partida["jaque_mate"];
        partida.set_nombre_de_partida(nombre_partida);
        //bbb partida.set_jaque_mate(jaque_mate);
        partida.vaciar_partida();
        //---------------
        GUI_jugada nueva_jugada;
        for (auto it_mov = js_jugadas.begin(); it_mov != js_jugadas.end(); ++it_mov)
        {
            auto js_jugada = it_mov.value();
            auto numero   =   js_jugada["jugada"];
            auto jugador  =   js_jugada["jugador"]; 
            auto js_piezas=   js_jugada["piezas"];
            auto jaque_mate=  js_jugada["jaque_mate"];
            nueva_jugada.set_jugador(jugador);
            nueva_jugada.vaciar_jugada();
            nueva_jugada.jaque_mate = jaque_mate;

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
                nueva_jugada.add_pieza_a_jugada(nueva_pieza);
            }
            partida.add_jugada_a_partida(nueva_jugada);
            
        }
        // despues de recorrer todo el objeto json, ya se han cargado el almacen de partidas del juego
        almacen_de_partidas.push_back(partida);
        get_nombres_partidas();
    }
}

void GUI_gestor_partidas::actualiza_objeto_json()
{//tambien actualiza el fichero json de texto.
    json js_lista_partidas = json::array();
        json js_partida = json::object();
            json js_nombre_partida = "";
            json js_jugadas = json::array();
                json js_jugada = json::object();
                    json js_jugador = "";
                    json js_jaque_mate = false;
                    json js_n_jugada = 1;
                    json js_piezas = json::array();
                        json js_pieza=json::object();

    js_lista_partidas.clear();

    for (auto it_part = almacen_de_partidas.begin(); it_part != almacen_de_partidas.end(); ++it_part)
    {
        ////////////////////////
        //   en una partida
        /////////////////////////
        auto jugadas = (*it_part).get_jugadas();
        string nombre_partida=(*it_part).get_nombre_partida();
        js_nombre_partida = nombre_partida;

        js_jugadas.clear();
        int n_jugada = 1;
        for (auto it_jug = jugadas.begin(); it_jug != jugadas.end(); ++it_jug) 
        {   ////////////////////////
            //   en una jugada
            /////////////////////////
            
            //-- se asigna el numero de la jugada
            js_n_jugada = n_jugada;
            //--se asigna el jugador de la jugada
            auto jugador = (*it_jug).jugador;
            //-- se asigna si la jugada es mate
            bool jaque_mate = (*it_jug).jaque_mate;

            js_jugador = jugador;
            js_jaque_mate = jaque_mate;
            //--se genera la lista de piezas de la jugada
            js_piezas.clear();
            auto piezas = (*it_jug).get_lista_piezas_movidas();
            for (auto it_pieza = piezas.begin(); it_pieza != piezas.end(); ++it_pieza)
            {   ////////////////////////
                //   en una pieza
                /////////////////////////
                auto tipo_pz = (*it_pieza).c_tipo;
                auto color_pz = (*it_pieza).c_color;
                auto pieza_pz = (*it_pieza).c_pieza;
                auto fila_pz = (*it_pieza).c_fila;
                auto columna_pz = (*it_pieza).c_columna;
                js_pieza= json::object({{"tipo",tipo_pz},{"color",color_pz},{"pieza",pieza_pz},{"fila",fila_pz},{"columna",columna_pz} });
                js_piezas.push_back(js_pieza);
            }
            js_jugada = { {"jugada",js_n_jugada},{"jugador",js_jugador},{"jaque_mate",js_jaque_mate}, {"piezas",js_piezas} };
            js_jugadas.push_back(js_jugada); //objeto jugada
            //-----
            n_jugada++;
        }
        js_partida = { {"nombre",js_nombre_partida},{"jugadas",js_jugadas} ,};
        js_lista_partidas.push_back(js_partida);  //
    }
    std::ofstream fichero_json_partidas("lista_de_partidas_jq_v2.json");
    if (fichero_json_partidas.is_open())
    {
        fichero_json_partidas << std::setw(4) << js_lista_partidas << '\n';
    }
    else cout << "Fichero JSON de partidas no se ha podido abrir";
 

}

bool GUI_gestor_partidas::insert_update_partida(string nombre_partida, vector<GUI_jugada> lista_jugadas)
{
    // se busca si existe. 
    bool partida_existe = false;
    for (auto it_in = almacen_de_partidas.begin(); it_in != almacen_de_partidas.end(); ++it_in)
    {
        string nm = (*it_in).get_nombre_partida();
        if (nm == nombre_partida) partida_existe = true;
    }
    GUI_partida _partida;
    _partida.set_nombre_de_partida(nombre_partida);
    _partida.set_jugadas_de_partida(lista_jugadas);
    if (!partida_existe) {  // si no existe se inserta al final de la lista. Si esta llena se borra la primera
        if (almacen_de_partidas.size() >= 9) // si ya hay nueve partidas == est� lleno se borra la primera
            almacen_de_partidas.erase(almacen_de_partidas.begin());
        almacen_de_partidas.push_back(_partida);
        return true;
    }
    else {  //Si YA existe se devuelve FALSE y se actualiza la lista de jugadas
        almacen_de_partidas.pop_back();
        almacen_de_partidas.push_back(_partida);
        return false;
    }

}

GUI_partida GUI_gestor_partidas::get_or_new_partida(string _nombre)
{    // se busca la partida en la lista de partida y se devuelve si existe.
    vector<GUI_jugada> aux;
    bool existe_la_partida=false;

    for (auto it_in = almacen_de_partidas.begin(); it_in != almacen_de_partidas.end(); ++it_in) 
    {   // (*it_in) es una partida,
        if ((*it_in).get_nombre_partida() == _nombre) {  // si existe la partida ser� la "partida_actual"
            return (*it_in);
        }
    };
    // ------ si la partida no existe, se genera una partida nueva con el primer movimiento = todo al inicio
    if (!existe_la_partida) 
    {
        GUI_partida nueva_partida;
        GUI_jugada posicion_de_salida;
        posicion_de_salida.inicio_partida(); // se generan los movimientos de la posici�n de salida
        nueva_partida.set_nombre_de_partida(_nombre);  // se establece el nombre a la partida
        //bbb nueva_partida.set_jaque_mate(false);
        nueva_partida.add_jugada_a_partida(posicion_de_salida);  // se a�ade a la partida la posici�n de salida

        if (almacen_de_partidas.size() >= 9) // si ya hay nueve partidas == est� lleno se borra la primera
            almacen_de_partidas.erase(almacen_de_partidas.begin());

        almacen_de_partidas.push_back(nueva_partida);  // se a�ade a la lista de partidas

        return nueva_partida;
    }
 
}

vector<string> GUI_gestor_partidas::get_nombres_partidas()
{   //devuelve la lista de nombres de las partidas
    vector<string> nombres;
    nombres.clear();
    for (auto it_part = almacen_de_partidas.begin(); it_part != almacen_de_partidas.end(); ++it_part)
    {
        string s = (*it_part).get_nombre_partida();
        nombres.push_back(s);
    }
    return nombres;
}

