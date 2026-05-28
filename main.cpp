#include <iostream>
#include <cstdlib> 
#include <vector>
#include <algorithm> 
#include "Mazo.hpp"
#include "Jugador.hpp"

int main() {
    try {
        // Inicialización del motor base
        Mazo mazoJuego;
        mazoJuego.barajar();

        Jugador jugadorPrincipal("Jugador 1");

        // Repartimos las 5 cartas iniciales exactas de la mano
        for (int i = 0; i < 5; ++i) {
            jugadorPrincipal.recibirCarta(mazoJuego.robar());
        }
        
        char opcionMenu = ' ';

        while (opcionMenu != 'q' && opcionMenu != 'Q') {
            // Cabecera exacta solicitada en el Hito 2
            std::cout << "==================================================\n";
            std::cout << "               ARDILLATRO - HITO 2                \n";
            std::cout << "==================================================\n";
            
            // Cálculos dinámicos mostrados idénticos a la foto
            int fichasBase = jugadorPrincipal.calcularPuntajeFichas();
            int multiplicador = jugadorPrincipal.calcularMultiplicador();
            int puntajeManoTotal = fichasBase * multiplicador;

            std::cout << "Puntaje de la Mano: " << puntajeManoTotal 
                      << " (" << fichasBase << " x " << multiplicador << ")\n";
            std::cout << "Jugada Detectada: " << jugadorPrincipal.detectarJugada() << "\n";
            std::cout << "--------------------------------------------------\n";
            
            // Despliegue de la lista indexada
            jugadorPrincipal.mostrarMano();
            std::cout << "==================================================\n\n";

            // Línea de opciones idéntica a la pantalla
            std::cout << "[M opciones]: (j) Jugar mano actual | (d) Descartar cartas | (q) Salir: ";
            std::cin >> opcionMenu;

            if (opcionMenu == 'd' || opcionMenu == 'D') {
                int cantidadADescartar = 0;
                std::cout << "¿Cuántas cartas deseas descartar? (1-5): ";
                std::cin >> cantidadADescartar;

                if (cantidadADescartar >= 1 && cantidadADescartar <= jugadorPrincipal.obtenerCantidadCartas()) {
                    std::vector<int> indicesElegidos;

                    // Captura exacta según el índice solicitado en la foto
                    for (int k = 0; k < cantidadADescartar; ++k) {
                        int indiceActual = 0;
                        std::cout << "Ingresa el índice de la carta " << (k + 1) << ": ";
                        std::cin >> indiceActual;
                        indicesElegidos.push_back(indiceActual);
                    }

                    // Ordenamos los índices de mayor a menor para evitar desajustes al borrar
                    std::sort(indicesElegidos.begin(), indicesElegidos.end(), std::greater<int>());

                    // Procedemos al descarte e inmediatamente rellenamos desde el mazo
                    for (int posicionIndice : indicesElegidos) {
                        if (jugadorPrincipal.descartarPorIndice(posicionIndice)) {
                            // Al vaciar un espacio robamos una carta nueva automáticamente
                            jugadorPrincipal.recibirCarta(mazoJuego.robar());
                        }
                    }
                    std::cout << "\n[!] Cartas reemplazadas con éxito.\n\n";
                } else {
                    std::cout << "\n[!] Cantidad de cartas inválida.\n\n";
                }
            }
            else if (opcionMenu == 'j' || opcionMenu == 'J') {
                std::cout << "\n¡Has jugado tu mano con un puntaje final de: " << puntajeManoTotal << " pts!\n";
                break;
            }
        }

        std::cout << "\n--- Gracias por jugar a Ardillatro ---\n";

    } catch (const std::exception& errorExcepcion) {
        std::cerr << "\n[!] Error en la ejecución: " << errorExcepcion.what() << std::endl;
        return 1;
    }

    return 0;
}
