#ifndef JUGADOR_HPP
#define JUGADOR_HPP

#include <string>
#include <vector>
#include "Carta.hpp"

struct PuntajeBalatro {
    std::string nombreMano;
    int fichasBase;
    int multBase;
};

class Jugador {
private:
    std::string nombreJugador;
    std::vector<Carta> cartasEnMano; 

public:
    Jugador(std::string _nombreJugador);

    std::string obtenerNombre() const;
    void recibirCarta(const Carta& nuevaCarta);
    bool descartarPorIndice(int posicionIndice);

    Carta obtenerCartaEn(int indice) const; // Permite extraer una carta específica para jugarla
    PuntajeBalatro evaluarJugadaExacta(const std::vector<Carta>& jugada) const; //evaluador

    int obtenerCantidadCartas() const;
    void mostrarMano() const;
    void limpiarMano();
};
#endif
