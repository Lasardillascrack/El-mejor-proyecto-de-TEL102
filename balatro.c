#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "balatro.h"

int main() {
    srand(time(NULL));

    GameState game;
    initGame(&game);

    // Bucle de juegola weamierd
    while (game.cardsInHand < HAND_SIZE) {
        // Mostramos el estado actual de la pantalla
        renderTerminalInterface(&game);
        
        printf("Presiona ENTER para robar una carta...");
        getchar(); // Pausa el juego esperando el teclado
        
        // Ejecutamos la acción
        drawCard(&game);
    }

    // Mostramos la pantalla final una vez más
    renderTerminalInterface(&game);
    printf("¡Mano completada! Fin del juego.\n");

    return 0;
}