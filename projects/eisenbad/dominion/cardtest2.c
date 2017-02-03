/* File: cardtest2.c
   Author: Daniel Eisenbach
   Date: 2/2/17

   Description: Tests the implementation of the dominion smithy action card. Smithy costs four coin to buy, 
   and when played lets the player draw three additional cards from the top of their deck into their hand.

   Pass Conditions:
     1. Current player receives exactly 3 cards.
     2. 3 cards come from current player's own pile.
     3. No extra coins are awarded to the current player.
     4. No state change occurs to the victory card piles or kingdom card piles.
     5. No state change occurs for other players.
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"

int main() {
  int test_pass_count = 0;

  int newCards = 3;
  int discarded = 1;
  int xtraCoins = 0;
  int shuffledCards = 0;

  int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
  int seed = 1000;  // sets the state of the current random number generator stream, bc seed > 0; used in shuffle()
  int numPlayers = 2;
  int currentPlayer = 0;
  int nextPlayer = currentPlayer + 1;
  struct gameState G, testG;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
      sea_hag, tribute, smithy, council_room};

  // initialize a game state and player cards
  initializeGame(numPlayers, k, seed, &G);

  printf("\n----------------- Testing Card: %s ----------------\n", TESTCARD);

  /**************************************** TEST 1 ****************************************************/
  printf("\nTEST 1: Current player receives exactly 3 cards\n");

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
  cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

  printf("hand count = %d, expected = %d\n", testG.handCount[currentPlayer], G.handCount[currentPlayer] + newCards - discarded);

  // assert test 1 passed
  if ((testG.handCount[currentPlayer] == G.handCount[currentPlayer] + newCards - discarded)) {
    test_pass_count++;
    printf(" >>> TEST 1 PASSED\n");
  }
  else {printf(" >>> TEST 1 FAILED\n");}

  /**************************************** TEST 2 ****************************************************/
  printf("\nTEST 2: 3 cards come from current player's own pile\n");

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
  cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

  printf("deck count = %d, expected = %d\n", testG.deckCount[currentPlayer], G.deckCount[currentPlayer] - newCards + shuffledCards);

  // assert test 2 passed
  if (
        (testG.handCount[currentPlayer] == G.handCount[currentPlayer] + newCards - discarded) &&
	(testG.deckCount[currentPlayer] == G.deckCount[currentPlayer] - newCards + shuffledCards)
  ) {
    test_pass_count++;
    printf(" >>> TEST 2 PASSED\n");
  }
  else {printf(" >>> TEST 2 FAILED\n");}

  /**************************************** TEST 3 ****************************************************/
  printf("\nTEST 3: No extra coins are awarded to the current player\n");

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
  cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

  printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);

  // assert test 3 passed
  if (testG.coins == G.coins + xtraCoins) {
    test_pass_count++;
    printf(" >>> TEST 3 PASSED\n");
  }
  else {printf(" >>> TEST 3 FAILED\n");}

  /**************************************** TEST 4 ****************************************************/
  printf("\nTEST 4: No state change occurs to the victory card piles or kingdom card piles\n");

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
  cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

  // victory cards
  printf("estate count = %d, expected = %d\n", testG.supplyCount[estate], G.supplyCount[estate]);
  printf("duchy count = %d, expected = %d\n", testG.supplyCount[duchy], G.supplyCount[duchy]);
  printf("province count = %d, expected = %d\n", testG.supplyCount[province], G.supplyCount[province]);

  // kingdom cards
  printf("adventurer count = %d, expected = %d\n", testG.supplyCount[adventurer], G.supplyCount[adventurer]);
  printf("embargo count = %d, expected = %d\n", testG.supplyCount[embargo], G.supplyCount[embargo]);
  printf("village count = %d, expected = %d\n", testG.supplyCount[village], G.supplyCount[village]);
  printf("minion count = %d, expected = %d\n", testG.supplyCount[minion], G.supplyCount[minion]);
  printf("mine count = %d, expected = %d\n", testG.supplyCount[mine], G.supplyCount[mine]);
  printf("cutpurse count = %d, expected = %d\n", testG.supplyCount[cutpurse], G.supplyCount[cutpurse]);
  printf("sea_hag count = %d, expected = %d\n", testG.supplyCount[sea_hag], G.supplyCount[sea_hag]);
  printf("tribute count = %d, expected = %d\n", testG.supplyCount[tribute], G.supplyCount[tribute]);
  printf("smithy count = %d, expected = %d\n", testG.supplyCount[smithy], G.supplyCount[smithy]);
  printf("council_room count = %d, expected = %d\n", testG.supplyCount[council_room], G.supplyCount[council_room]);

  // assert test 4 passed
  if ( 
        (testG.supplyCount[estate] == G.supplyCount[estate]) &&   
        (testG.supplyCount[duchy] == G.supplyCount[duchy]) &&
        (testG.supplyCount[province] == G.supplyCount[province]) &&
        (testG.supplyCount[adventurer] == G.supplyCount[adventurer]) &&
        (testG.supplyCount[embargo] == G.supplyCount[embargo]) &&
        (testG.supplyCount[village] == G.supplyCount[village]) &&
        (testG.supplyCount[minion] == G.supplyCount[minion]) &&
        (testG.supplyCount[mine] == G.supplyCount[mine]) &&
        (testG.supplyCount[cutpurse] == G.supplyCount[cutpurse]) &&
        (testG.supplyCount[sea_hag] == G.supplyCount[sea_hag]) &&
        (testG.supplyCount[tribute] == G.supplyCount[tribute]) &&
        (testG.supplyCount[smithy] == G.supplyCount[smithy]) &&
        (testG.supplyCount[council_room] == G.supplyCount[council_room])
  ) {
    test_pass_count++;
    printf(" >>> TEST 4 PASSED\n");
  }
  else {printf(" >>> TEST 4 FAILED\n");}

  /**************************************** TEST 5 ****************************************************/
  printf("\nTEST 5: No state change occurs for other players\n");

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
  cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

  newCards = 0;  // other players should receive no new cards
  discarded = 0;  // other players should not discard cards
  printf("next player hand count = %d, expected = %d\n", testG.handCount[nextPlayer], G.handCount[nextPlayer] + newCards - discarded);
  printf("next player deck count = %d, expected = %d\n", testG.deckCount[nextPlayer], G.deckCount[nextPlayer] - newCards + shuffledCards);

  // assert test 5 passed
  if (
        (testG.handCount[nextPlayer] == G.handCount[nextPlayer] + newCards - discarded) &&
	(testG.deckCount[nextPlayer] == G.deckCount[nextPlayer] - newCards + shuffledCards)
  ) {
    test_pass_count++;
    printf(" >>> TEST 5 PASSED\n");
  }
  else {printf(" >>> TEST 5 FAILED\n");}

  /**************************************** END OF TESTS ****************************************************/
  if (test_pass_count == 5) {printf("\n >>>>> TESTS COMPLETE. SUCCESS: All %s tests passed. <<<<<\n\n", TESTCARD);}
  else {printf("\n >>>>> TESTS COMPLETE. FAILURE: Not all %s tests passed. <<<<<\n\n", TESTCARD);}

  return 0;
}
