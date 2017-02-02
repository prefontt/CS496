/*************************************************************************
 * Author: Lance Marks marksla
 * Date: 20170205
 * Class: CS362 Software Development II
 * Description: This is a unit test for the card Smithy - Cost 4 +3 Cards
 * **********************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "testhelperfunctions.h"

int main (int argc, char** argv) {

  //initialize gameState for testing of functions
  struct gameState testGame;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

  initializeGame(2, k, 7, &testGame);

  int result, expected;

  //Place card in player hand
  placePlayerHand(0, smithy, 0, &testGame);

  //Play Smithy
  playCard(0, -1, -1, -1, &testGame);
  printf("**Test Card Functionality - Smithy\n");

/* ----   Test 1 - 7 Cards In Hand  ---- */
  printf("*Test 1 - 7 Cards In Hand\n");
  
  expected = 7;

  //Set result to number of hand cards
  result = numHandCards(&testGame);

  assertTest(result, expected, 1);

/* ----   Test 2 - Action Count is 0 ---- */
  printf("*Test 2 - Action Count is 0\n");

  expected = 0;

  //Set result to number of actions
  result = testGame.numActions;

  assertTest(result, expected, 2);

/* ----   Test 3 - Played Pile Has 1 Card ---- */
  printf("*Test 3 - Played Pile Has 1 Card\n");

  expected = 1;

  //Set result to number of actions
  result = testGame.playedCardCount;

  assertTest(result, expected, 3);

/* ----   Test 4 - Smithy Is In Played Pile ---- */
  printf("*Test 4 - Smithy Is In Played Pile\n");

  expected = 1;

  //Set result to 1 if Smithy in Played Pile
  result = 0;
  int i;
  for (i = 0; i < testGame.playedCardCount; i++) {
    if (testGame.playedCards[i] == smithy) {
      result = 1;
    } 
  }

  assertTest(result, expected, 4);

/* ----   Test 5 - Draw Pile Has 2 Cards ---- */
  printf("*Test 5 - Draw Pile Has 2 Cards\n");
  
  expected = 2;

  //Set result to number of cards in draw pile
  result = testGame.deckCount[whoseTurn(&testGame)];

  assertTest(result, expected, 5);

/* ----   Test 6 - Smithy Cost 4 ---- */
  printf("*Test 6 - Smithy Cost 4\n");

  expected = 4;

  //Set result to cost of Smithy
  result = getCost(smithy);

  assertTest(result, expected, 6);

  printf("** Testing Complete\n");
  return 0;

}
