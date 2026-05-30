#include <iostream>
#include <cstdlib> 
#include <vector>
#include <algorithm> 
#include "Mazo.hpp"
#include "Jugador.hpp"

int main() {
    try {
        int maxNiveles = 5;

        // Calculados para ser ganables con 4 manos si se juega estratégicamente.
        int puntajesObjetivo[5] = {300, 450, 600, 800, 1000}; 

        Mazo mazoJuego;
        mazoJuego.barajar();

        Jugador jugadorPrincipal("jugador 1"); 

        // Repartimos las 8 cartas iniciales exactas de la mano
        for (int i = 0; i < 8; ++i) {
            jugadorPrincipal.recibirCarta(mazoJuego.robar());
        }

        char opcionMenu = ' ';

        for (int nivelActual = 1; nivelActual <= maxNiveles; ++nivelActual) {

            int objetivoNivel = puntajesObjetivo[nivelActual - 1];
            int puntajeAcumuladoNivel = 0;
            int manosRestantes = 4;     // Límite de jugadas estricto
            int descartesRestantes = 3; // Límite de descartes estricto

            bool nivelSuperado = false;

            while (opcionMenu != 'q' && opcionMenu != 'Q') {

                std::cout << "==================================================\n";
                std::cout << "               ARDILLATRO - HITO 2                \n";
                std::cout << "==================================================\n";

                std::cout << "NIVEL: " << nivelActual << " DE " << maxNiveles << "\n";
                std::cout << "Objetivo: " << puntajeAcumuladoNivel << " / " << objetivoNivel << " puntos.\n";
                std::cout << "Manos restantes: " << manosRestantes << " | Descartes restantes: " << descartesRestantes << "\n";
                std::cout << "--------------------------------------------------\n";

                jugadorPrincipal.mostrarMano();
                std::cout << "==================================================\n\n";

                std::cout << "[Opciones]: (j) Jugar mano | (d) Descartar | (q) Salir: ";
                std::cin >> opcionMenu;

                // opcion descartar
                if (opcionMenu == 'd' || opcionMenu == 'D') {
                    if (descartesRestantes <= 0) {
                        std::cout << "\n[!] Ya no te quedan descartes en este nivel.\n\n";
                        continue;
                    }

                    int cantidadADescartar = 0;
                    std::cout << "¿Cuántas cartas deseas descartar? (1-5): ";
                    std::cin >> cantidadADescartar;

                    if (cantidadADescartar >= 1 && cantidadADescartar <= 5 && cantidadADescartar <= jugadorPrincipal.obtenerCantidadCartas()) {
                        std::vector<int> indicesElegidos;

                        for (int k = 0; k < cantidadADescartar; ++k) {
                            int indiceActual = 0;
                            std::cout << "Ingresa el índice de la carta " << (k + 1) << ": ";
                            std::cin >> indiceActual;
                            indicesElegidos.push_back(indiceActual);
                        }

                        std::sort(indicesElegidos.begin(), indicesElegidos.end(), std::greater<int>());

                        for (int posicionIndice : indicesElegidos) {
                            if (jugadorPrincipal.descartarPorIndice(posicionIndice) && !mazoJuego.estaVacio()) {
                                jugadorPrincipal.recibirCarta(mazoJuego.robar());
                            }
                        }
                        descartesRestantes--; // Restamos 1 al límite de descartes
                        std::cout << "\n[!] Cartas reemplazadas con éxito.\n\n";
                    } else {
                        std::cout << "\n[!] Cantidad de cartas inválida.\n\n";
                    }
                }

                // opcion jugar
                else if (opcionMenu == 'j' || opcionMenu == 'J') {
                    if (manosRestantes <= 0) {
                         //por si algo falla, no debería entrar aquí por el chequeo de victoria/derrota
                         continue;
                    }

                    int cantidadAJugar = 5;
                    std::cout << "Seleccione 5 cartas a jugar (ingrese el índice):\n";

                    std::vector<Carta> cartasJugadas; 
                    std::vector<int> indicesAJugar;
                    int fichasDeCartas = 0;           

                    for (int k = 0; k < cantidadAJugar; ++k) {
                        int indiceActual = 0;
                        std::cout << "Ingresa el índice de la carta " << (k + 1) << ": ";
                        std::cin >> indiceActual;

                        indicesAJugar.push_back(indiceActual);
                        Carta cartaElegida = jugadorPrincipal.obtenerCartaEn(indiceActual);
                        cartasJugadas.push_back(cartaElegida);
                        fichasDeCartas += cartaElegida.obtenerPuntos();
                    }

                    PuntajeBalatro resultado = jugadorPrincipal.evaluarJugadaExacta(cartasJugadas);

                    int totalFichasAzules = resultado.fichasBase + fichasDeCartas;
                    int puntajeManoTotal = totalFichasAzules * resultado.multBase;

                    std::cout << "\n================ RESULTADO =====================\n";
                    std::cout << "Jugada Detectada: " << resultado.nombreMano << "\n";
                    std::cout << "Puntos de las Cartas: +" << fichasDeCartas << " fichas\n";
                    std::cout << "Matemática: " << totalFichasAzules << " Fichas x " << resultado.multBase << " Mult\n";
                    std::cout << "PUNTAJE DE ESTA MANO: " << puntajeManoTotal << "\n";
                    std::cout << "==================================================\n";

                    puntajeAcumuladoNivel += puntajeManoTotal;
                    manosRestantes--; // Restamos 1 al límite de manos

                    std::sort(indicesAJugar.begin(), indicesAJugar.end(), std::greater<int>());
                    for (int idx : indicesAJugar) {
                        jugadorPrincipal.descartarPorIndice(idx);
                    }

                    int cartasFaltantes = 7 - jugadorPrincipal.obtenerCantidadCartas();
                    for(int i = 0; i < cartasFaltantes; i++) {
                        if(!mazoJuego.estaVacio()) {
                            jugadorPrincipal.recibirCarta(mazoJuego.robar());
                        }
                    }

                    // Chequeo inmediato después de jugar
                    if (puntajeAcumuladoNivel >= objetivoNivel) {
                        nivelSuperado = true;
                        break; 
                    } else if (manosRestantes == 0) {
                        break; 
                    }
                }
            } 

            if (opcionMenu == 'q' || opcionMenu == 'Q') {
                break; 
            }

            // termino del nivel
            if (nivelSuperado) {
                std::cout << "\n>>> ¡NIVEL " << nivelActual << " COMPLETADO! <<<\n";
                if (nivelActual == maxNiveles) {
                    std::cout << "\n!!! FELICIDADES, HAS GANADO ARDILLATRO !!!\n";
                } else {
                    std::cout << "Presiona 'c' para continuar al Nivel " << (nivelActual + 1) << "... ";
                    char pausa;
                    std::cin >> pausa;
                }
            } else {
                std::cout << "\n--- GAME OVER ---\n";
                std::cout << "Te quedaste sin manos y no lograste el objetivo de " << objetivoNivel << " puntos.\n";
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
