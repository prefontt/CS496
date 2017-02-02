#ifndef TESTHELPERFUNCTIONS_H
#define TESTHELPERFUNCTIONS_H

#include "dominion.h"

int copyArray(int *originalArray, int *copyArray, int cols);

int copy2DArray(int **originalArray, int **copyArray, int rows, int cols);

int copyGameState(struct gameState *original, struct gameState *copy);

int fillPlayerHand(int player, int card, int count, struct gameState *state);

int placePlayerHand(int player, int card, int position, struct gameState *state);

int fillPlayerDeck(int player, int card, int count, struct gameState *state);

int placePlayerDeck(int player, int card, int position, struct gameState *state);

int fillPlayerDiscard(int player, int card, int count, struct gameState *state);

int placePlayerDiscard(int player, int card, int position, struct gameState *state);

int assertTest(int result, int expected, int testNumber);

#endif
