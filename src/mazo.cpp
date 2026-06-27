#include "cartas.hpp"
#include "mazo.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>

mazo::mazo(){}
void mazo::agregar_carta(carta* carta){
    cartas_mazo.push_back(carta);
}
carta* mazo::sacar_carta() {
    // se validaa que el mazo no esté vacío, para evitar un crash
    if (cartas_mazo.empty()) {
        std::cout << "El mazo esta vacio!" << std::endl;
        return nullptr; 
    }
    
    // 2. Guardamos el puntero de la última carta usando back()
    carta* carta_robada = cartas_mazo.back(); 
    
    // 3. Eliminamos ese espacio del final del vector usando pop_back()
    cartas_mazo.pop_back(); 
    
    // 4. Entregamos el puntero
    return carta_robada; 
}
std::vector<carta*> mazo::clonar_mazo(){
    std::vector<carta*> clon;
    for (carta* c : cartas_mazo) {
        clon.push_back(c->clonar()); // Clona la carta reservando memoria nueva
    }
    return clon;
}
void mazo::imprimir_mazo(){
    for (size_t i= 0;i<cartas_mazo.size();i++){
        std::cout << cartas_mazo[i]->get_description() << std::endl;
    }
}
void mazo::barajar() {
    // 1. Obtenemos una "semilla" aleatoria real basada en el hardware de tu compu
    std::random_device rd; 
    
    // 2. Usamos esa semilla para inicializar el motor generador (Mersenne Twister)
    std::mt19937 generador(rd()); 
    
    // 3. La función shuffle desordena el vector desde el inicio hasta el final
    std::shuffle(cartas_mazo.begin(), cartas_mazo.end(), generador);
}
mazo::~mazo() {
    for (size_t i = 0; i < cartas_mazo.size(); i++) {
        delete cartas_mazo[i];
    }
    cartas_mazo.clear();
}

void llenar_mazo(mazo& mazo_juego) {
    //Metemos todas las opciones en arreglos
    PINTA todasLasPintas[] = {PINTA::CORAZON, PINTA::TREBOL, PINTA::DIAMANTE, PINTA::PICA};
    VALOR todosLosValores[] = {VALOR::DOS, VALOR::TRES, VALOR::CUATRO, VALOR::CINCO, 
                               VALOR::SEIS, VALOR::SIETE, VALOR::OCHO, VALOR::NUEVE, 
                               VALOR::DIEZ, VALOR::J, VALOR::K, VALOR::Q, VALOR::As};
    // Fichas base en el mismo orden que los VALOR (El 2 da 2, el As da 11)
    int fichasBaseArr[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};

    // un for que recorre lo que creamos y genera los objetos de cartas facilmente
    for (int p = 0; p < 4; p++) {           // Recorre las 4 pintas
        for (int v = 0; v < 13; v++) {      // Recorre los 13 valores
            
            // Creamos la carta dinámicamente y la mandamos a la bóveda
            carta_normal* nuevaCarta = new carta_normal(todasLasPintas[p], todosLosValores[v], fichasBaseArr[v]);
            mazo_juego.agregar_carta(nuevaCarta);
            
        }
    }
}
