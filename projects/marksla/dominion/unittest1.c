/*************************************************************************
 * Author: Lance Marks marksla
 * Date: 20170205
 * Class: CS362 Software Development II
 * Description: This is a unit test for the function
 * **********************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "dominion.h"
#include "rngs.h"
#include "testhelperfunctions.h"

int main (int argc, char** argv) {

  //initialize gameState for testing of functions
  struct gameState testGame;
  struct gameState beforeFunction;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

  initializeGame(2, k, 7, &testGame);

  int i, j, result, expected;

/* ----   Test 1 - No Money Cards ---- */
  
  expected = 0;

  // put 5 estates in the players hand
  fillPlayerHand(0, estate, 5, &testGame);

  updateCoins(0, &testGame, 0);

  result = testGame.coins;

  assertTest(result, expected, 1);

/* ----   Test 2 - One Copper Only ---- */

  expected = 1;

  //put 1 copper in the players hand
  placePlayerHand(0, copper, 0, &testGame);

  updateCoins(0, &testGame, 0);

  result = testGame.coins;

  assertTest(result, expected, 2);

/* ----   Test 3 - Five Coppers ---- */

  expected = 5;

  //put 5 coppers in the players hand
  fillPlayerHand(0, copper, 5, &testGame);

  updateCoins(0, &testGame, 0);

  result = testGame.coins;

  assertTest(result, expected, 3);

/* ----   Test 4 - One Silver Only ---- */
  
  expected = 2;

  // put 5 estates in the players hand
  fillPlayerHand(0, estate, 5, &testGame);

  //put 1 copper in the players hand
  placePlayerHand(0, silver, 0, &testGame);

  updateCoins(0, &testGame, 0);

  result = testGame.coins;

  assertTest(result, expected, 4);

/* ----   Test 5 - Five Silvers ---- */

  expected = 10;

  // put 5 silvers in the players hand
  fillPlayerHand(0, silver, 5, &testGame);

  updateCoins(0, &testGame, 0);

  result = testGame.coins;

  assertTest(result, expected, 5);

/* ----   Test 6 - One Gold Only ---- */
  
  expected = 3;

  // put 5 estates in the players hand
  fillPlayerHand(0, estate, 5, &testGame);

  //put 1 copper in the players hand
  placePlayerHand(0, gold, 0, &testGame);

  updateCoins(0, &testGame, 0);

  result = testGame.coins;

  assertTest(result, expected, 6);

/* ----   Test 7 - Five Golds ---- */

  expected = 15;

  // put 5 silvers in the players hand
  fillPlayerHand(0, gold, 5, &testGame);

  updateCoins(0, &testGame, 0);

  result = testGame.coins;

  assertTest(result, expected, 7);

/* ----   Test 8 - Bonus Coins ---- */

  expected = 20;

  //put 5 estates in the players hand
  fillPlayerHand(0, estate, 5, &testGame);

  updateCoins(0, &testGame, 20);

  result = testGame.coins;

  assertTest(result, expected, 8);

/* ----   Test 9 - Edge Case ---- */

  expected = 1500;

  //put 500 gold in the players hand
  fillPlayerHand(0, gold, 500, &testGame);

  updateCoins(0, &testGame, 0);

  result = testGame.coins;

  assertTest(result, expected, 9);


  return 0;
}
/*
int updateCoins(int player, struct gameState *state, int bonus)
{
  int i;
	
  //reset coin count
  state->coins = 0;

  //add coins for each Treasure card in player's hand
  for (i = 0; i < state->handCount[player]; i++)
    {
      if (state->hand[player][i] == copper)
	{
	  state->coins += 1;
	}
      else if (state->hand[player][i] == silver)
	{
	  state->coins += 2;
	}
      else if (state->hand[player][i] == gold)
	{
	  state->coins += 3;
	}	
    }	

  //add bonus
  state->coins += bonus;

  return 0;
}

*/
