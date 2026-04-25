#include <stdio.h>
#include <stdlib.h>
#include "balatro.h"

const char* rankNames[] = {"N/A", "As", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
const char* suitNames[] = {"Corazones", "Diamantes", "Treboles", "Picas"};

void buildDeck(GameState* state) {
    int index = 0;
    for (int s = 0; s < SUITS; s++) {
        for (int r = 1; r <= RANKS; r++) {
            state->deck[index].suit = s;
            state->deck[index].rank = r;
            index++;
        }
    }
}

void shuffleDeck(GameState* state) {
    for (int i = DECK_SIZE - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Card temp = state->deck[i];
        state->deck[i] = state->deck[j];
        state->deck[j] = temp;
    }
}

void calculateScore(GameState* state) {
    state->currentScore.chips = 0;
    state->currentScore.mult = 1;

    // mite del bucle es "cardsInHand"
    for (int i = 0; i < state->cardsInHand; i++) {
        int cardValue = state->hand[i].rank;
        
        if (cardValue > 10) cardValue = 10; 
        if (cardValue == 1) cardValue = 11; 
        
        state->currentScore.chips += cardValue;
        
        if (state->hand[i].rank == 1 || state->hand[i].rank >= 11) {
            state->currentScore.mult += 1; 
        }
    }
}

// Inicializa estado en cero
void initGame(GameState* state) {
    buildDeck(state);
    shuffleDeck(state);
    state->cardsDrawn = 0;
    state->cardsInHand = 0;
    calculateScore(state);
}

// Función que roba 1 carta. Devuelve 1 si pudo robar, 0 si la mano está llena.
int drawCard(GameState* state) {
    if (state->cardsInHand >= HAND_SIZE) {
        return 0; // Ya no caben mas cartas
    }
    
    // Pasa la carta del mazo a la mano
    state->hand[state->cardsInHand] = state->deck[state->cardsDrawn];
    
    // se aumenta los contadores
    state->cardsDrawn++;
    state->cardsInHand++;
    
    // Recalculamo la matematica autoaaticamente al robar
    calculateScore(state);
    return 1;
}

void renderTerminalInterface(GameState* state) {
    // para limpiar pantalla
    system("clear"); 

    printf("=== MINI BALATRO: MODO ROBAR ===\n");
    printf("Cartas en mano: %d/%d\n\n", state->cardsInHand, HAND_SIZE);
    
    for (int i = 0; i < state->cardsInHand; i++) {
        Card c = state->hand[i];
        printf(" -> [%s de %s]\n", rankNames[c.rank], suitNames[c.suit]);
    }

    int finalScore = state->currentScore.chips * state->currentScore.mult;
    
    printf("\n--- RESULTADOS MATEMATICOS ---\n");
    printf("Fichas Base:   %d\n", state->currentScore.chips);
    printf("Multiplicador: x%d\n", state->currentScore.mult);
    printf("------------------------------\n");
    printf("PUNTAJE TOTAL: %d\n\n", finalScore);
}