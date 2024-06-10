#pragma once
#include "ETSIDI.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>
#include "json.hpp"
#include "GUI_Pieza2.h"
#include "GUI_partida.h"

using namespace ETSIDI;
using json = nlohmann::json;




class GUI_gestion_partidas
{
    json j_partidas =
    {
        {"pi", 3.141},
        {"happy", true},
        {"name", "Niels"},
        {"nothing", nullptr},
        {
            "answer", {
                {"everything", 42}
            }
        },
        {"list", {1, 0, 2}},
        {
            "object", {
                {"currency", "USD"},
                {"value", 42.99}
            }
        }
    };

    vector<GUI_partida> Lista_de_partidas;

public:
    GUI_gestion_partidas();
    bool inserta_partida(string nombre_partida, vector<GUI_movimiento> partida);
    void nuevo_movimiento(vector<PIEZA_STRU> posiciones);
    vector<GUI_movimiento> get_or_new_partida(string nombre);
    vector<GUI_movimiento> get_partida_ejemplo();
};

