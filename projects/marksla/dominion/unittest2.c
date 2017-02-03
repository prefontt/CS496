/*************************************************************************
 * Author: Lance Marks marksla
 * Date: 20170205
 * Class: CS362 Software Development II
 * Description: This is a unit test for the function fullDeckCount()
 * **********************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include "testhelperfunctions.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

int main (int argc, char** argv) {

  //initialize gameState for testing of functions
  struct gameState testGame;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

  initializeGame(2, k, 7, &testGame);

  int result, expected;

  //Setup hand and decks
  // gold = 6
  // smithy = 8
  // mine = 4
  // province = 4
  // duchy = 14
  // estate = 14
  fillPlayerHand(0, province, 10, &testGame);

  fillPlayerDeck(0, duchy, 20, &testGame);

  fillPlayerDiscard(0, estate, 20, &testGame);

  placePlayerHand(0, gold, 1, &testGame);
  placePlayerHand(0, gold, 2, &testGame);
  placePlayerHand(0, smithy, 3, &testGame);
  placePlayerHand(0, smithy, 4, &testGame);
  placePlayerHand(0, smithy, 5, &testGame);
  placePlayerHand(0, smithy, 6, &testGame);

  placePlayerDeck(0, gold, 1, &testGame);
  placePlayerDeck(0, gold, 2, &testGame);
  placePlayerDeck(0, smithy, 3, &testGame);
  placePlayerDeck(0, smithy, 4, &testGame);
  placePlayerDeck(0, smithy, 5, &testGame);
  placePlayerDeck(0, smithy, 6, &testGame);

  placePlayerDiscard(0, gold, 1, &testGame);
  placePlayerDiscard(0, gold, 2, &testGame);
  placePlayerDiscard(0, mine, 3, &testGame);
  placePlayerDiscard(0, mine, 4, &testGame);
  placePlayerDiscard(0, mine, 5, &testGame);
  placePlayerDiscard(0, mine, 6, &testGame);


/* ----   Test 1 - No Silver Cards ---- */
  
  expected = 0;

  result = fullDeckCount(0, silver, &testGame);

  assertTest(result, expected, 1);

/* ----   Test 2 - 6 Gold Cards ---- */

  expected = 6;

  result = fullDeckCount(0, gold, &testGame);

  assertTest(result, expected, 2);

/* ----   Test 3 - 8 Smithy Cards ---- */

  expected = 8;

  result = fullDeckCount(0, smithy, &testGame);

  assertTest(result, expected, 3);

/* ----   Test 4 - 4 Mine Cards ---- */
  
  expected = 4;

  result = fullDeckCount(0, mine, &testGame);

  assertTest(result, expected, 4);

/* ----   Test 5 - 4 Province Cards ---- */

  expected = 4;

  result = fullDeckCount(0, province, &testGame);

  assertTest(result, expected, 5);

/* ----   Test 6 - 14 Duchy Cards ---- */

  expected = 14;

  result = fullDeckCount(0, duchy, &testGame);

  assertTest(result, expected, 6);

/* ----   Test 7 - 14 Estate Cards ---- */

  expected = 14;

  result = fullDeckCount(0, estate, &testGame);

  assertTest(result, expected, 7);


  return 0;
}
/*
int fullDeckCount(int player, int card, struct gameState *state) {
  int i;
  int count = 0;

  for (i = 0; i < state->deckCount[player]; i++)
    {
      if (state->deck[player][i] == card) count++;
    }

  for (i = 0; i < state->handCount[player]; i++)
    {
      if (state->hand[player][i] == card) count++;
    }

  for (i = 0; i < state->discardCount[player]; i++)
    {
      if (state->discard[player][i] == card) count++;
    }

  return count;
}
*/
