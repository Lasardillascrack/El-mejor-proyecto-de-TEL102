#include "Mazo.hpp"
#include <algorithm>
#include <random>
#include <chrono>
#include <stdexcept>

Mazo::Mazo() {
    std::vector<std::string> listaPintas = {"Picas", "Diamantes", "Tréboles", "Corazones"};
    std::vector<std::string> listaValores = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "As"};
    int arregloPuntos[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};

    coleccionCartas.reserve(listaPintas.size() * listaValores.size());

    for (const auto& pintaActual : listaPintas) {
        for (size_t indice = 0; indice < listaValores.size(); ++indice) {
            coleccionCartas.push_back(Carta(pintaActual, listaValores[indice], arregloPuntos[indice]));
        }
    }
}

void Mazo::barajar() {
    unsigned semillaTiempo = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(coleccionCartas.begin(), coleccionCartas.end(), std::default_random_engine(semillaTiempo));
}

Carta Mazo::robar() {
    if (estaVacio()) {
        throw std::underflow_error("El mazo se ha quedado vacio.");
    }
    Carta cartaExtraida = coleccionCartas.back();
    coleccionCartas.pop_back(); 
    return cartaExtraida;
}

int Mazo::obtenerTamano() const {
    return static_cast<int>(coleccionCartas.size());
}

bool Mazo::estaVacio() const {
    return coleccionCartas.empty();
}
