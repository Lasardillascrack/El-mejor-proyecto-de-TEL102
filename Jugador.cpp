#include "Jugador.hpp"
#include <algorithm>
#include <iostream>
#include <map>

Jugador::Jugador(std::string _nombreJugador) : nombreJugador(_nombreJugador) {}

std::string Jugador::obtenerNombre() const { return nombreJugador; }

void Jugador::recibirCarta(const Carta &nuevaCarta) {
  if (cartasEnMano.size() < 8) {
    cartasEnMano.push_back(nuevaCarta);
  }
}

bool Jugador::descartarPorIndice(int posicionIndice) {
  if (posicionIndice >= 0 &&
      posicionIndice < static_cast<int>(cartasEnMano.size())) {
    cartasEnMano.erase(cartasEnMano.begin() + posicionIndice);
    return true;
  }
  return false;
}

// funciones obsoletas

/*int Jugador::calcularPuntajeFichas() const {
    int sumaPuntos = 0;
    for (const auto& carta : cartasEnMano) {
        sumaPuntos += carta.obtenerPuntos();
    }
    // Si hay un Par detectado, se le da un bono base al puntaje simulando
Balatro if (detectarJugada() == "Par") { sumaPuntos += 10;
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
}*/

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

void Jugador::limpiarMano() { cartasEnMano.clear(); }

Carta Jugador::obtenerCartaEn(int indice) const {
  // Retorna la carta solicitada (asumiendo que el índice es válido)
  return cartasEnMano[indice];
}

PuntajeBalatro
Jugador::evaluarJugadaExacta(const std::vector<Carta> &jugada) const {
  std::map<int, int> contarrango;
  std::map<std::string, int> contarpinta;

  //  convertir el string de la carta a un valor numérico para ordenar
  auto obtenerRangoNumerico = [](const std::string &valor) {
    if (valor == "J")
      return 10;
    if (valor == "Q")
      return 10;
    if (valor == "K")
      return 10;
    if (valor == "As")
      return 11;
    return std::stoi(valor); // Convierte "2", "3"... a int
  };

  // Contamos frecuencias de valor y pinta
  for (const auto &carta : jugada) {
    contarrango[obtenerRangoNumerico(carta.obtenerValor())]++;
    contarpinta[carta.obtenerPinta()]++;
  }

  // El color requiere jugar exactamente 5 cartas
  bool color = (contarpinta.size() == 1 && jugada.size() == 5);

  // La escala requiere 5 cartas consecutivas
  bool escalera = false;
  if (jugada.size() == 5) {
    std::vector<int> ranks;
    for (const auto &carta : jugada)
      ranks.push_back(obtenerRangoNumerico(carta.obtenerValor()));
    std::sort(ranks.begin(), ranks.end());
    auto last = std::unique(ranks.begin(), ranks.end());
    ranks.erase(last, ranks.end());

    if (ranks.size() == 5) {
      if (ranks.back() - ranks.front() == 4)
        escalera = true;
      // Caso especial: As, 2, 3, 4, 5
      if (ranks[0] == 2 && ranks[1] == 3 && ranks[2] == 4 && ranks[3] == 5 &&
          ranks[4] == 14)
        escalera = true;
    }
  }

  // Ordenamos las frecuencias de mayor a menor (para póker, tríos, pares)
  std::vector<int> freqs;
  for (auto const &par : contarrango)
    freqs.push_back(par.second);
  std::sort(freqs.rbegin(), freqs.rend());

  // Evaluamos con la tabla exacta de Balatro
  if (color && freqs[0] == 5)
    return {"Color de 5", 160, 16};
  if (color && freqs[0] == 3 && freqs[1] == 2)
    return {"Full de Color", 140, 14};
  if (freqs[0] == 5)
    return {"Repóker", 120, 12};
  if (color && escalera)
    return {"Escalera de Color", 100, 8};
  if (freqs[0] == 4)
    return {"Póker", 60, 7};
  if (freqs[0] == 3 && freqs[1] == 2)
    return {"Full House", 40, 4};
  if (color)
    return {"Color", 35, 4};
  if (escalera)
    return {"Escalera", 30, 4};
  if (freqs[0] == 3)
    return {"Trío", 30, 3};
  if (freqs[0] == 2 && freqs.size() > 1 && freqs[1] == 2)
    return {"Doble Pareja", 20, 2};
  if (freqs[0] == 2)
    return {"Par", 10, 2};

  return {"Carta Alta", 5, 1};
}
