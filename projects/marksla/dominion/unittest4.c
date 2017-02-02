/*************************************************************************
 * Author: Lance Marks marksla
 * Date: 20170205
 * Class: CS362 Software Development II
 * Description: This is a unit test for the function isGameOver()
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
  //Tests
  //Test all Cards
  //Test province cards empty
  //Test 2 supply piles empty
  //test 3 supply piles empty
  //Test all supply piles empty except province

/* ----   Test 1 - All Kingdom Cards Full ---- */

  expected = 0;

  //Check if initialized game is over
  result = isGameOver(&testGame);

  assertTest(result, expected, 1);

/* ----   Test 2 - Province Supply Empty ---- */

  expected = 1;

  //Set Province supplyCount to 0
  testGame.supplyCount[province] = 0;

  //Check if initialized game is over
  result = isGameOver(&testGame);

  assertTest(result, expected, 2);

/* ----   Test 3 - 2 Supply Piles Empty ---- */

  expected = 0;

  //Set Province supplyCount to 8
  testGame.supplyCount[province] = 8;

  //Set smithy and village supplyCount to 0
  testGame.supplyCount[smithy] = 0;
  testGame.supplyCount[village] = 0;
  
  //Check if initialized game is over
  result = isGameOver(&testGame);

  assertTest(result, expected, 3);

/* ----   Test 4 - 3 Supply Piles Empty ---- */

  expected = 1;

  //Set estate smithy and village supplyCount to 0
  testGame.supplyCount[estate] = 0;
  testGame.supplyCount[smithy] = 0;
  testGame.supplyCount[village] = 0;
  
  //Check if initialized game is over
  result = isGameOver(&testGame);

  assertTest(result, expected, 4);

/* ----   Test 5 - All Supply Piles Empty Except Province ---- */

  expected = 1;

  //Set all supply piles empty
  int i;
  for (i = 0; i < 27; i++) {
    testGame.supplyCount[i] = 0;
  }

  //Set Province supplyCount to 8
  testGame.supplyCount[province] = 8;

  //Check if initialized game is over
  result = isGameOver(&testGame);

  assertTest(result, expected, 5);


  return 0;
}
/*
int isGameOver(struct gameState *state) {
  int i;
  int j;
	
  //if stack of Province cards is empty, the game ends
  if (state->supplyCount[province] == 0)
    {
      return 1;
    }

  //if three supply pile are at 0, the game ends
  j = 0;
  for (i = 0; i < 25; i++)
    {
      if (state->supplyCount[i] == 0)
	{
	  j++;
	}
    }
  if ( j >= 3)
    {
      return 1;
    }

  return 0;
}
*/
