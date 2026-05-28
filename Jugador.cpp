#include "Jugador.hpp"
#include <iostream>
#include <map>

Jugador::Jugador(std::string _nombreJugador) : nombreJugador(_nombreJugador) {}

std::string Jugador::obtenerNombre() const { return nombreJugador; }

void Jugador::recibirCarta(const Carta& nuevaCarta) {
    if (cartasEnMano.size() < 5) {
        cartasEnMano.push_back(nuevaCarta);
    }
}

bool Jugador::descartarPorIndice(int posicionIndice) {
    if (posicionIndice >= 0 && posicionIndice < static_cast<int>(cartasEnMano.size())) {
        cartasEnMano.erase(cartasEnMano.begin() + posicionIndice);
        return true;
    }
    return false; 
}

int Jugador::calcularPuntajeFichas() const {
    int sumaPuntos = 0;
    for (const auto& carta : cartasEnMano) {
        sumaPuntos += carta.obtenerPuntos();
    }
    // Si hay un Par detectado, se le da un bono base al puntaje simulando Balatro
    if (detectarJugada() == "Par") {
        sumaPuntos += 30; 
    }
    return sumaPuntos;
}

int Jugador::calcularMultiplicador() const {
    // Si detecta un par el multiplicador sube a 2, si no, se queda en 1
    return (detectarJugada() == "Par") ? 2 : 1;
}

std::string Jugador::detectarJugada() const {
    std::map<std::string, int> frecuenciasValores;
    for (const auto& carta : cartasEnMano) {
        frecuenciasValores[carta.obtenerValor()]++;
    }
    
    for (const auto& parValores : frecuenciasValores) {
        if (parValores.second >= 2) {
            return "Par";
        }
    }
    return "Carta Alta";
}

int Jugador::obtenerCantidadCartas() const {
    return static_cast<int>(cartasEnMano.size());
}

void Jugador::mostrarMano() const {
    std::cout << "Tus Cartas en Mano:\n";
    for (int i = 0; i < static_cast<int>(cartasEnMano.size()); ++i) {
        std::cout << "  [" << i << "] ";
        cartasEnMano[i].mostrar();
        std::cout << "\n";
    }
}

void Jugador::limpiarMano() {
    cartasEnMano.clear();
}
