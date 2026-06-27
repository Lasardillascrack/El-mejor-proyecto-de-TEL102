#ifndef MAZO_H
#define MAZO_H
#include "cartas.hpp"
#include <iostream>
#include <vector>
#include <string>

class mazo{
private:
    std::vector<carta*> cartas_mazo;
public:
    mazo();
    ~mazo();
    void agregar_carta(carta* carta);
    carta* sacar_carta();
    std::vector<carta*> clonar_mazo();
    void imprimir_mazo();
    void barajar();
};


void llenar_mazo(mazo& mazo);

#endif