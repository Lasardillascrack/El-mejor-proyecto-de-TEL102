#ifndef JUGADOR_HPP
#define JUGADOR_HPP

#include <string>
#include <vector>
#include "Carta.hpp"

class Jugador {
private:
    std::string nombreJugador;
    std::vector<Carta> cartasEnMano; 

public:
    Jugador(std::string _nombreJugador);
    
    std::string obtenerNombre() const;
    void recibirCarta(const Carta& nuevaCarta);
    bool descartarPorIndice(int posicionIndice);
    
    // Métodos avanzados para procesar la interfaz que exige la foto 1000218954_2.jpg
    int calcularPuntajeFichas() const;
    int calcularMultiplicador() const;
    std::string detectarJugada() const;
    
    int obtenerCantidadCartas() const;
    void mostrarMano() const;
    void limpiarMano();
};

#endif
