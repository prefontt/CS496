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
  struct gameState G,
                   testG;
  int i,
      deckCount,
      handCount,
      deckTop,
      handTop,
      success = 1, 
      error_count = 0,
      error_total = 0, 
      seed = 0,
      tempDeck[MAX_DECK],
      k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

  seed = 1 + rand() % 10;
  // BEGIN INITIALIZATION TEST to gameState is correct
  printf("------------------------ Test drawCard Function ----------------------\n");
  // Make sure initialize game returns success, if not exit
  success = initializeGame(2, k, seed, &G);
  asserttrue(success == 0, "Failed to Initialize Game");
  if ( success == -1 ) return 1; 
  memcpy(&testG, &G, sizeof(struct gameState));

  printf("Testing call to drawCard with nonempty deck\n");
  deckCount = G.deckCount[0];
  handCount = G.deckCount[0];
  deckTop = G.deck[0][G.deckCount[0]-1];
  success = drawCard(0, &G);
  
  error_count += asserttrue(deckCount-1 == G.deckCount[0], "deckCount not decremented");
  error_count += asserttrue(handCount+1 == G.handCount[0], "handCount not incremented");
  error_count += asserttrue(deckTop == G.hand[0][G.handCount[0]-1], "Top of player1 hand is not from the top of the deck");
  if (error_count == 0)
    printf("\tAll Tests Completed Successfully: Card Draw (deck not empty)\n\n");
  else
    printf("\t%d Tests failed: Card Draw (deck not empty)\n\n)", error_count);
  
  // Empty Deck into discard
  while (G.deckCount[1] != 0) {
    G.discard[1][G.discardCount[1]] = G.deck[1][G.deckCount[1]-1];
    G.discardCount[1]++;
    G.deckCount[1]--;
  }
  memcpy(&tempDeck, &G.discard[1], sizeof(int)*MAX_DECK); 
  deckCount = G.discardCount[1];
  
  error_total += error_count;
  error_count = 0;
  printf("Testing call to drawCard with empty decki\n");
  handCount = G.handCount[1];
  
  success = drawCard(1, &G);
  
  error_count += asserttrue(success == 0, "Draw Card Failed");
  
  error_count += asserttrue(handCount + 1 == G.handCount[1], "Hand Count not incremented");
  
  error_count += asserttrue(G.discardCount[1] == 0, "Discard not cleared after deck shuffle");
  
  error_count += asserttrue(G.deckCount[1] == 9, "Deck size incorrect, should be 9");
  
  seed = 0;
  for (i = 0; i < G.deckCount[1]; i++) {
    if ( tempDeck[i] == G.deck[1][i] )
      seed++;
  }
  
  error_count += asserttrue(seed != deckCount-1, "Deck not shuffled");
  
  error_count += asserttrue(deckCount - 1 == G.deckCount[1], "Deck not decremented after draw");
  
  if (error_count == 0)
    printf("\tAll Tests Completed Successfully: Card Draw (deck empty)\n\n");
  else
    printf("\t%d Tests failed: Card Draw (deck empty)\n\n", error_count);

  error_total += error_count;
  error_count = 0;
  
  printf("Test Invalid Input (both deck and discard empty\n");
  G.discardCount[0] = 0;
  G.deckCount[0] = 0;

  success = drawCard(0, &G);

  error_count += asserttrue(success != 0, "Failed to catch invalid input");
  
  if (error_count == 0)
    printf("\tAll Tests Completed Successfully: Card Draw (invalid input)\n\n");
  else
    printf("\t%d Tests failed: Card Draw (invalid input)\n\n", error_count);

  error_total += error_count;

  if (error_total == 0)
    printf("ALL TESTS SUCCESSFUL drawCard\n");
  else
    printf("\t%d TESTS FAILED drawCard\n", error_count);



  printf("------------------------ END Test drawCard ----------------------\n");

  return 0; 
}


