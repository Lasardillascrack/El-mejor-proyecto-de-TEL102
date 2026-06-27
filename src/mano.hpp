#ifndef MANO_H
#define MANO_H

#include "cartas.hpp"
#include "mazo.hpp"
#include <map>
#include <algorithm>
#include <vector>
#include <string>

// Actualizamos los nombres para que calcen con mainwindow.cpp
struct PuntajeBalatro {
    std::string nombre_jugada;
    int fichas_base_jugada;
    int mult_base_jugada;
};

// Le decimos al programa que esta función SÍ recibe un vector de cartas
PuntajeBalatro evaluar_mano(const std::vector<carta*>& cartas);

#endif
