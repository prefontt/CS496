/*************************************************************************
 * Author: Lance Marks marksla
 * Date: 20170205
 * Class: CS362 Software Development II
 * Description: This is a unit test for the function buyCard()
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
  //no buys
  //not enough coins
  //not enough cards
  //everything fine

/* ----   Test 1 - Not Enough Buys ---- */

  expected = -1;

  //Set numBuys to 0
  testGame.numBuys = 0;

  //Give player hand of gold
  testGame.coins = 15;

  //Buy a village - supplyPos 14 cost 3
  result = buyCard(14, &testGame);

  assertTest(result, expected, 1);

/* ----   Test 2 - 10 Villages Remain ---- */

  expected = 10;

  //Set result to village supplyPos 14 count
  result = testGame.supplyCount[14];

  assertTest(result, expected, 2);

/* ----   Test 3 - Not Enough Coins ---- */

  expected = -1;

  //Set numBuys to 1
  testGame.numBuys = 1;

  //Give player hand of estates
  testGame.coins = 0;

  //Buy a village - supplyPos 14 cost 3
  result = buyCard(14, &testGame);

  assertTest(result, expected, 3);

/* ----   Test 4 - 10 Villages Remain ---- */

  expected = 10;

  //Set result to village supplyPos 14 count
  result = testGame.supplyCount[14];

  assertTest(result, expected, 4);

/* ----   Test 5 - Not Enough Supply ---- */

  expected = -1;

  //Set numBuys to 1
  testGame.numBuys = 1;

  //Give player hand of gold
  testGame.coins = 15;

  //Set supply count to 0
  testGame.supplyCount[14] = 0;

  //Buy a village - supplyPos 14 cost 3
  result = buyCard(14, &testGame);

  assertTest(result, expected, 5);

/* ----   Test 6 - 0 Villages Remain ---- */

  expected = 0;

  //Set result to village supplyPos 14 count
  result = testGame.supplyCount[14];

  assertTest(result, expected, 6);


/* ----   Test 7 - All Requirements Met ---- */

  expected = 0;

  //Set numBuys to 1
  testGame.numBuys = 1;

  //Give player hand of gold
  testGame.coins = 15;

  //Set supply count to 10
  testGame.supplyCount[14] = 10;

  //Buy a village - supplyPos 14 cost 3
  result = buyCard(14, &testGame);

  assertTest(result, expected, 7);

/* ----   Test 8 - 9 Villages Remain ---- */

  expected = 9;

  //Set result to village supplyPos 14 count
  result = testGame.supplyCount[14];

  assertTest(result, expected, 8);

/* ----   Test 9 - 0 Buys Remain ---- */

  expected = 0;

  //Set result to village supplyPos 14 count
  result = testGame.numBuys;

  assertTest(result, expected, 9);

/* ----   Test 10 - 12 Coins Remain ---- */

  expected = 12;

  //Set result to village supplyPos 14 count
  result = testGame.coins;

  assertTest(result, expected, 10);

  return 0;
}
/*
int buyCard(int supplyPos, struct gameState *state) {
  int who;
  if (DEBUG){
    printf("Entering buyCard...\n");
  }

  // I don't know what to do about the phase thing.

  who = state->whoseTurn;

  if (state->numBuys < 1){
    if (DEBUG)
      printf("You do not have any buys left\n");
    return -1;
  } else if (supplyCount(supplyPos, state) <1){
    if (DEBUG)
      printf("There are not any of that type of card left\n");
    return -1;
  } else if (state->coins < getCost(supplyPos)){
    if (DEBUG) 
      printf("You do not have enough money to buy that. You have %d coins.\n", state->coins);
    return -1;
  } else {
    state->phase=1;
    //state->supplyCount[supplyPos]--;
    gainCard(supplyPos, state, 0, who); //card goes in discard, this might be wrong.. (2 means goes into hand, 0 goes into discard)
  
    state->coins = (state->coins) - (getCost(supplyPos));
    state->numBuys--;
    if (DEBUG)
      printf("You bought card number %d for %d coins. You now have %d buys and %d coins.\n", supplyPos, getCost(supplyPos), state->numBuys, state->coins);
  }

  //state->discard[who][state->discardCount[who]] = supplyPos;
  //state->discardCount[who]++;
    
  return 0;
}
*/

