#ifndef BALATRO_H
#define BALATRO_H
// aca se define las pintas, cartas, manos y el tamaño de mazo standard, pero puede cambiar, por ahora lo trabajamos asi.
#define SUITS 4 
#define RANKS 13
#define HAND_SIZE 5
#define DECK_SIZE (SUITS * RANKS)
//aca se define los valores de mayor a menor de las posibles manos jugadas
#define HIGH_CARD 0
#define PAIR 1
#define TWO_PAIR 2
#define THREE_OF_A_KIND 3
#define STRAIGHT 4
#define FLUSH 5
#define FULL_HOUSE 6
#define FOUR_OF_A_KIND 7

typedef struct {
    int rank; 
    int suit; 
} Card;

typedef struct {
    int chips;
    int mult;
} Score;
typedef struct {
    Card deck[DECK_SIZE];
    Card hand[HAND_SIZE];
    Score currentScore;
    int cardsDrawn;
    int cardsInHand;
    int currentHandType; //Guarda qué mano lograste
} GameState;
void initGame(GameState* state);
int drawCard(GameState* state);
void renderTerminalInterface(GameState* state);

#endif