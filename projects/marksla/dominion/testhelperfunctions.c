/*************************************************************************
 * Author: Lance Marks marksla
 * Date: 20170205
 * Class: CS362 Software Development II
 * Description: This is a set of helper functions for test suite
 * **********************************************************************/
#include "testhelperfunctions.h"
#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

// rows equals MAX_PLAYERS dimension, cols equals MAX_DECK or MAX_HAND
int copyArray(int *copyArray, int *originalArray, int cols) {
  int i, j;

    for (j = 0; j < cols; j++) {
      copyArray[j] = originalArray[j];
    }

  return 1;
}

int copy2DArray(int **originalArray, int **copyArray, int rows, int cols) {
  int i, j;

      for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
          copyArray[i][j] = originalArray[i][j];
        }
      }

  return 1;
}

int copyGameState(struct gameState *copy, struct gameState *original) {
  
  copy->numPlayers = original->numPlayers;

  copyArray(copy->supplyCount,original->supplyCount,27);    // 1 D array, 27 cards in game

  copyArray(copy->embargoTokens,original->embargoTokens,27);

  copy->outpostPlayed = original->outpostPlayed;

  copy->whoseTurn = original->whoseTurn;

  copy->phase = original->phase;

  copy->numActions = original->numActions;

  copy->coins = original->coins;

  copy->numBuys = original->numBuys;

  copy2DArray(copy->hand,original->hand,original->numPlayers,500);

  copyArray(copy->handCount,original->handCount,original->numPlayers);

  copy2DArray(copy->deck,original->deck,original->numPlayers,500);

  copyArray(copy->deckCount,original->deckCount,original->numPlayers);

  copy2DArray(copy->discard,original->discard,original->numPlayers,500);

  copyArray(copy->discardCount,original->discardCount,original->numPlayers);

  copyArray(copy->playedCards,original->playedCards,500);

  copy->playedCardCount = original->playedCardCount;

  return 1;

}

int fillPlayerHand(int player, int card, int count, struct gameState *state) {
  int i;

  for (i = 0; i < count; i++) {
    state->hand[player][i] = card;
  }

  state->handCount[player] = count;

  return 1;
}

int placePlayerHand(int player, int card, int position, struct gameState *state) {
  state->hand[player][position] = card;
  return 1;
}

int fillPlayerDeck(int player, int card, int count, struct gameState *state) {
  int i;

  for (i = 0; i < count; i++) {
    state->deck[player][i] = card;
  }

  state->deckCount[player] = count;

  return 1;
}

int placePlayerDeck(int player, int card, int position, struct gameState *state) {
  state->deck[player][position] = card;
  return 1;
}

int fillPlayerDiscard(int player, int card, int count, struct gameState *state) {
  int i;

  for (i = 0; i < count; i++) {
    state->discard[player][i] = card;
  }

  state->discardCount[player] = count;

  return 1;
}

int placePlayerDiscard(int player, int card, int position, struct gameState *state) {
  state->discard[player][position] = card;
  return 1;
}

int assertTest(int result, int expected, int testNumber) {
  if (result == expected) {
    printf("TEST %d SUCCESSFULLY COMPLETED\n",testNumber);
    return 1;
  } else {
    printf("TEST %d FAILED\n",testNumber);
    return 0;
  }
}

