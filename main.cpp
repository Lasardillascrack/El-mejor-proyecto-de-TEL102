#include <iostream>
#include <cstdlib>
#include <ctime>
#include "balatro.hpp"

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    GameState game;
    initGame(&game);

    // Bucle de juego
    while (game.cardsInHand < HAND_SIZE) {
        // Mostramos el estado actual de la pantalla
        renderTerminalInterface(&game);
        
        std::cout << "Presiona ENTER para robar una carta...";
        std::cin.get(); // Pausa el juego esperando el teclado de forma nativa en C++
        
        // Ejecutamos la acción
        drawCard(&game);
    }

    // Mostramos la pantalla final una vez más
    renderTerminalInterface(&game);
    std::cout << "¡Mano completada! Fin del juego.\n";

    return 0;
}
