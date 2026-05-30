#include "Carta.hpp"
#include <iostream>

Carta::Carta(std::string _tipoPinta, std::string _textoValor, int _puntos)
    : tipoPinta(_tipoPinta), textoValor(_textoValor), puntos(_puntos) {}

std::string Carta::obtenerPinta() const { return tipoPinta; }
std::string Carta::obtenerValor() const { return textoValor; }
int Carta::obtenerPuntos() const { return puntos; }

void Carta::mostrar() const { std::cout << textoValor << " de " << tipoPinta; }
