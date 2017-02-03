// Micheal Willard
// CS362 - Assignment #3
// Card Test 2
// Testing:  Adventurer


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

void asserttrue (int bln, char* msg) {
  if (bln) {
    printf("%s: PASS\n", msg);
  }
  else {
    printf("%s: FAIL\n", msg);
  }
}

#define TESTCARD "adventurer"

int main(int argc, char **argv) {
  int seed = 1000;
  int numPlayers = 2;
  struct gameState G, testG;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

  // initialize a game state and player cards
  initializeGame(numPlayers, k, seed, &G);
  printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

  //  Set Preconditions
  printf("\n >>>>> Precondition Set <<<<<\n\n");
  //  COME BACK TO THESE
  G.hand[0][0] = adventurer;
  int handCountPre = G.handCount[0];
  int deckCountPre = G.deckCount[0];
  int discardCountPre = G.discardCount[0];
  int playedCardCountPre = G.playedCardCount;


  cardEffect(adventurer, 0, 0, 0, &G, 0, 0);

  //  Check Postconditions
  //  Player should now have 2 Treasure Cards in Deck


}
