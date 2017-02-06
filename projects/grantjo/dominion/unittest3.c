#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dominion.h"
#include "rngs.h"

int asserttrue(int condition, char* message)
{
  if (!condition) {
    printf("\tError: %s\n", message);
    return 1;
  }

  return 0;
}


int main(int argc, char** argv) 
{
  struct gameState G;
  int i = 0,
      success = 1, 
      error_count = 0,
      error_total = 0,
      copper_count = 0,
      silver_count = 0,
      gold_count = 0, 
      seed = 0,
      k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

  seed = 1 + rand() % 10;
  // BEGIN INITIALIZATION TEST to gameState is correct
  printf("------------------------ Initializing Game----------------------\n");
  // Make sure initialize game returns success, if not exit
  success = initializeGame(2, k, seed, &G);
  asserttrue(success == 0, "Failed to Initialize Game");
  if ( success == -1 ) return 1; 

  printf("----------------------- Begin Test updateCoins ---------------------\n");
  printf("Testing updateCoins Player1 first draw ( no bonus, only copper )\n");
  for (i = 0; i < G.handCount[0]; i++) {
    if (G.hand[0][i] == copper)
      copper_count++;
    else if (G.hand[0][i] == silver)
      silver_count += 2;
    else if (G.hand[0][i] == gold)
      gold_count += 3;
  }

  success = updateCoins(0, &G, 0);
  
  error_count += asserttrue(success == 0, "updateCoins call returns status failed");
  error_count += asserttrue(G.coins == copper_count, "Coin Count incorrect, should only contain copper");
  error_count += asserttrue(G.coins <= 7 && G.coins >= 2, "Coin count OUT OF RANGE, should be 2 <= coins <= 7");
  error_count += asserttrue(silver_count == 0, "Silver greater than 0");
  error_count += asserttrue(gold_count == 0, "Gold greater than 0");
 
  if (error_count == 0)
    printf("\tAll Tests Successful updateCoins Player 1 first draw (no bonus, only copper)\n\n");
  else
    printf("\t%d Tests Failed updateCoins Player 1 first draw (no bonus, only copper\n\n)", error_count);

  error_total += error_count;
  error_count = 0;

  printf("Testing updateCoins Player 2 three of each currency ( no bonus )\n");
  
  copper_count = 0;
  silver_count = 0;
  gold_count = 0;

  G.handCount[1] = 0;
  // Fill Player 2 Hand with 3 of each currency
  for (i = 0; i < 3; i++) {
    G.hand[1][i] = copper;
    G.handCount[1]++;
  }  
  // Add some non-currency cards inbetween
  G.hand[1][i] = smithy;
  G.hand[1][i] = estate;
  G.handCount[1] += 2;
  i += 2;

  for (; i < 8; i++) {
    G.hand[1][i] = silver;
    G.handCount[1]++;
  }
 
  // Add some non-currency cards inbetween
  G.hand[1][i] = sea_hag;
  G.hand[1][i] = province;
  G.handCount[1] += 2;
  i += 2;

  for (; i < 13; i++) {
    G.hand[1][i] = gold;
    G.handCount[1]++;
  }
   
  for (i = 0; i < G.handCount[1]; i++) {
    if (G.hand[1][i] == copper)
      copper_count++;
    else if (G.hand[1][i] == silver)
      silver_count += 2;
    else if (G.hand[1][i] == gold)
      gold_count += 3;
  }

  success = updateCoins(1, &G, 0);
  
  error_count += asserttrue(success == 0, "updateCoins call returns status failed");
  error_count += asserttrue(G.coins == copper_count + gold_count + silver_count, "Coin Count incorrect");
  error_count += asserttrue(copper_count == 3, "Expected copper to total 3");
  error_count += asserttrue(silver_count == 6, "Expected silver to total 6");
  error_count += asserttrue(gold_count == 9, "Expected gold to total 9");

  if (error_count == 0)
    printf("\tAll Tests Successful updateCoins Player 2 three of each currency (no bonus)\n\n");
  else
    printf("\t%d Tests Failed updateCoins Player 2 three of each currency  (no bonus)\n\n", error_count);

  error_total += error_count;
  error_count = 0;


  printf("Testing updateCoins Player 1 One of every non-currency card plus 5 bonus\n");

  copper_count = 0;
  silver_count = 0;
  gold_count = 0;

  G.handCount[0] = 0;
  for (i = curse; i < treasure_map; i++) {
    if (i < copper || i > gold) {
      G.hand[0][G.handCount[0]] = i;
      G.handCount[0]++;
    }  
  }
  
  for (i = 0; i < G.handCount[0]; i++) {
    if (G.hand[0][i] == copper)
      copper_count++;
    else if (G.hand[0][i] == silver)
      silver_count += 2;
    else if (G.hand[0][i] == gold)
      gold_count += 3;
  }

  success = updateCoins(0, &G, 5);

  error_count += asserttrue(success == 0, "updateCoins call returns status failed");
  error_count += asserttrue(G.coins == 5, "Coin Cunt Incorrect, expected 5 from bonus");
  error_count += asserttrue(copper_count == 0, "Expected copper to total 0");
  error_count += asserttrue(silver_count == 0, "Expected silver to total 0");
  error_count += asserttrue(gold_count == 0, "Expected gold to total 0");

  if (error_count == 0)
    printf("\tAll Tests Successful, Player 1 One of every non-currency card plus 5 bonus\n\n");
  else
    printf("\t%d Tests Failed, Player 1 One of every non-currency card plus 5 bonus\n\n", error_count);

  error_total += error_count;
  error_count = 0;

  if (error_total == 0)
    printf("ALL TESTS SUCCESSFUL updateCoins\n");
  else
    printf("%d TESTS FAILED updateCoins\n", error_total);
  
  
  printf("----------------------- END Test updateCoins ---------------------\n");
  

  return 0; 
}


