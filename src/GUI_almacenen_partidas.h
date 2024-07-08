#pragma once
#include "ETSIDI.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>
#include "json.hpp"
#include "GUI_Pieza2.h"
#include "GUI_partida.h"
#include "listado_partidas.h"
#include <fstream>
#include <json.hpp>
using json = nlohmann::json;


NLOHMANN_JSON_SERIALIZE_ENUM(ENUM_JUGADOR,
    {
      { BLANCAS,   "BLANCAS" },
      { NEGRAS,   "NEGRAS" },
      { GRAVEDAD_N,   "GRAVEDAD_N" },
      { GRAVEDAD_B,   "GRAVEDAD_B" }
    })

NLOHMANN_JSON_SERIALIZE_ENUM(ENUM_TIPO,
    {
      { peon,   "peon" },
      { torre,   "torre" },
      { caballo,   "caballo" },
      { alfil,   "alfil" },
      { reina,   "reina" },
      { rey,   "rey" }
    })

NLOHMANN_JSON_SERIALIZE_ENUM(ENUM_COLOR,
    {
        { blanca,   "blanca" },
        { negra,    "negra" }
    })

NLOHMANN_JSON_SERIALIZE_ENUM(ENUM_COLUMNA,
    {
        { A, "A" },
        { B, "B" },
        { C, "C" },
        { D, "D" },
        { E, "E" },
        { F, "F" },
        { G, "G" },
        { H, "H" },
        { C_ND, "C_ND" }
    })


NLOHMANN_JSON_SERIALIZE_ENUM(ENUM_FILA,
    {
        { f1, "f1" },
        { f2, "f2" },
        { f3, "f3" },
        { f4, "f4" },
        { f5, "f5" },
        { f6, "f6" },
        { f7, "f7" },
        { f8, "f8" },
        { f_ND, "f_ND" },
    })

NLOHMANN_JSON_SERIALIZE_ENUM(ENUM_PIEZA,
    {
        { PZ_peon_rey, "PZ_peon_rey" },
        { PZ_rey,                   "PZ_rey" },
        { PZ_reina,                 "PZ_reina" },
        { PZ_peon_reina,            "PZ_peon_reina" },
        { PZ_peon_torre_rey,        "PZ_peon_torre_rey" },
        { PZ_peon_torre_reina,      "PZ_peon_torre_reina" },
        { PZ_peon_caballo_rey,      "PZ_peon_caballo_rey" },
        { PZ_peon_caballo_reina,    "PZ_peon_caballo_reina" },
        { PZ_peon_alfil_rey,        "PZ_peon_alfil_rey" },
        { PZ_peon_alfil_reina,      "PZ_peon_alfil_reina" },
        { PZ_caballo_rey,           "PZ_caballo_rey" },
        { PZ_caballo_reina,         "PZ_caballo_reina" },
        { PZ_alfil_rey,             "PZ_alfil_rey" },
        { PZ_alfil_reina,           "PZ_alfil_reina" },
        { PZ_torre_rey,             "PZ_torre_rey" },
        { PZ_torre_reina,           "PZ_torre_reina" }
    })
// json string to enum


class GUI_gestor_partidas
{
    vector<GUI_partida> almacen_de_partidas;  //limitado a 9 partidas
    GUI_partida partida_i;
    json partidas_json;

public:
    GUI_gestor_partidas(); // lee del json la lista de partidas
    bool insert_update_partida(string nombre_partida, vector<GUI_jugada> partida);
    void actualiza_objeto_json();
    GUI_partida get_or_new_partida(string nombre);
    vector<string> get_nombres_partidas();
};

