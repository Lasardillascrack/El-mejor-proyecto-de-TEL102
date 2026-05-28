#ifndef MAZO_HPP
#define MAZO_HPP

#include <vector>
#include "Carta.hpp"

class Mazo {
private:
    std::vector<Carta> coleccionCartas; 

public:
    Mazo(); 
    void barajar();
    Carta robar();
    int obtenerTamano() const;
    bool estaVacio() const;
};

#endif
