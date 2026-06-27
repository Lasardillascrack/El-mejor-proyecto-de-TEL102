
#include "mano.hpp"
#include <map>
#include <algorithm>

PuntajeBalatro evaluar_mano(const std::vector<carta*>& cartas) {
    // Valor por defecto si no se arma nada
    PuntajeBalatro resultado = {"Carta más alta", 5, 1};

    if (cartas.empty()) return resultado;

    std::map<VALOR, int> conteo_valores;
    std::map<PINTA, int> conteo_pintas;
    std::vector<int> valores_secuenciales;

    for (carta* c : cartas) {
        conteo_valores[c->get_valor()]++;
        conteo_pintas[c->get_pinta()]++;
        valores_secuenciales.push_back(c->get_valor_secuencial());
    }

    std::sort(valores_secuenciales.begin(), valores_secuenciales.end());

    // Verificar si es Color (Todas las cartas de la misma pinta - mínimo 5 cartas en Balatro, pero ajustado a la mesa)
    bool es_color = false;
    for (auto const& [pinta, cantidad] : conteo_pintas) {
        if (cantidad == (int)cartas.size() && cartas.size() >= 4) { // Ajusta el >= 4 según cuántas cartas dejes jugar
            es_color = true;
        }
    }

    // Verificar si es Escala (Consecutivas)
    bool es_escala = false;
    if (cartas.size() >= 4) {
        es_escala = true;
        for (size_t i = 1; i < valores_secuenciales.size(); ++i) {
            if (valores_secuenciales[i] != valores_secuenciales[i-1] + 1) {
                es_escala = false;
                break;
            }
        }
    }

    // Contar combinaciones repetidas
    int max_iguales = 0;
    int parejas = 0;
    int tercias = 0;

    for (auto const& [valor, cantidad] : conteo_valores) {
        if (cantidad > max_iguales) max_iguales = cantidad;
        if (cantidad == 2) parejas++;
        if (cantidad == 3) tercias++;
    }

    // Clasificación de la mano de póker (Priorizando la más fuerte primero)
    if (es_escala && es_color) {
        resultado = {"Escalera corrida", 100, 8};
    } else if (max_iguales == 4) {
        resultado = {"Póker", 60, 7};
    } else if (tercias == 1 && parejas == 1) {
        resultado = {"Full house", 40, 4};
    } else if (es_color) {
        resultado = {"Color", 35, 4};
    } else if (es_escala) {
        resultado = {"Escalera", 30, 4};
    } else if (tercias == 1) {
        resultado = {"Tercia", 30, 3};
    } else if (parejas == 2) {
        resultado = {"Doble par", 20, 2};
    } else if (parejas == 1) {
        resultado = {"Par", 10, 2};
    }

    return resultado;
}
