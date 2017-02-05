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
      seed = 0,
      k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

  seed = 1 + rand() % 10;
  // BEGIN INITIALIZATION TEST to gameState is correct
  printf("------------------------ Initializing Game----------------------\n");
  // Make sure initialize game returns success, if not exit
  success = initializeGame(2, k, seed, &G);
  asserttrue(success == 0, "Failed to Initialize Game");
  if ( success == -1 ) return 1; 

  printf("----------------------- Begin Test isGameOver  ---------------------\n");
  printf("Testing isGameOver after game initialized\n");
  
  success = isGameOver(&G);

  error_count += asserttrue(success == 0, "Game Shouldn't be Over at Beginning");
 
  if (error_count == 0)
    printf("\tAll Tests Successful isGameOver after game initialized\n\n");
  else
    printf("\t%d Tests Failed isGameOver after game initialized\n\n)", error_count);

  error_total += error_count;
  error_count = 0;

  printf("Testing isGameOver provence supply 0\n");
  
  G.supplyCount[province] = 0;

  success = isGameOver(&G);

  error_count += asserttrue(success == 1, "Game should be over when province supply is 0");

  if (error_count == 0)
    printf("\tAll Tests Successful isGameOver province supply 0\n\n");
  else
    printf("\t%d Tests Failed isGameOver province supply 0\n\n", error_count);

  error_total += error_count;
  error_count = 0;


  printf("Testing isGameOver estate, duchy, village supply 0\n");

  G.supplyCount[province] = 8;
  G.supplyCount[duchy] = 0;
  G.supplyCount[estate] = 0;
  G.supplyCount[village] = 0;

  success = isGameOver(&G);

  error_count += asserttrue(success == 1, "Game should be over when 3 supplies are 0");

  if (error_count == 0)
    printf("\tAll Tests Successful, estate, duchy, village supply 0\n\n");
  else
    printf("\t%d Tests Failed, estate, duchy, village supply 0\n\n", error_count);

  error_total += error_count;
  error_count = 0;

  printf("Testing isGameOver, every cards supply 0 except province\n");
  
  for (i = curse; i < treasure_map; i++) {
    if (i != province)
      G.supplyCount[i] = 0;
  }

  success = isGameOver(&G);

  error_count += asserttrue(success == 1, "Game should be over if at least 3 supplies 0");
 
  if (error_count == 0)
    printf("\tAll Tests Successful, every cards supply 0 except province\n\n");
  else
    printf("\t%d Tests Failed, every cards supply 0 except province\n\n", error_count);

  error_total += error_count;
  error_count = 0;

  if (error_total == 0)
    printf("ALL TESTS SUCCESSFUL isGameOver\n");
  else
    printf("%d TESTS FAILED isGameOver\n", error_total);
  
  
  printf("----------------------- END Test isGameOver ---------------------\n");
  

  return 0; 
}


