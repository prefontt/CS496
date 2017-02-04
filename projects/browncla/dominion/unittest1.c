/*unittest1.c */
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#define FUNCTION_NAME "shuffle"
//testing int shuffle(int player, struct gameState *state)
// shuffle reorganizes the deck of the player, assumes all cards are in the deck, not
// in hand or discard pile


// Test that the deck count before and after are the same
// Test that all the same cards are still in the deck
// Test that it only affects the deck of the current player

//Own assert function
int asserttrue(int input, int number){
	if (input){
		printf("TEST %d SUCCESSFUL\n", number);
	}
	else
		printf("TEST %d FAILED\n", number);
	return 0;
}

// compare function for sorting

int cmpfunc	(const void* a, const void* b) {
  if (*(int*)a > *(int*)b)
    return 1;
  if (*(int*)a < *(int*)b)
    return -1;
  return 0;
}

/*
 * Include the following lines in your makefile:
 
unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)

Add unittest1 to all: ... line
 */

int main() {
    int success;

    int i;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    int otherPlayer = 1;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	printf("----------------- Function: %s ----------------\n", FUNCTION_NAME);

	// ----------- TEST 1: Same number of cards before and after --------------
	printf("TEST 1: Same number of cards before and after\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));


	shuffle(thisPlayer, &testG);
	asserttrue(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer], 1);


	// ----------- TEST 2: Same cards are still in the deck with right counts --------------
	printf("TEST 2: Same cards are still in the deck with right counts\n");

	qsort ((void*)(testG.deck[thisPlayer]), testG.deckCount[thisPlayer], sizeof(int), cmpfunc); 
	qsort ((void*)(	G.deck[thisPlayer]), G.deckCount[thisPlayer], sizeof(int), cmpfunc); 

	for (i = 0; i < testG.deckCount[thisPlayer]; i++){
			if (testG.deck[thisPlayer][i] != G.deck[thisPlayer][i]){

				asserttrue(0, 2);
				success = 0;
			    break;
			}
			else {
				success = 1;
			}
	}
	if (success == 1)
			asserttrue(1, 2);


	// ----------- TEST 3: Changing 3 cards and testing count  -----------
	printf("TEST 3: Changing 3 cards and testing count\n");

	G.deck[thisPlayer][2] = 8;
	G.deck[thisPlayer][1] = 3;
	G.deck[thisPlayer][4] = 9;

	memcpy(&testG, &G, sizeof(struct gameState));

	shuffle(thisPlayer, &testG);

	asserttrue(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer], 3);

	// ---------- TEST 4: Changing 3 cards and testing all cards still in deck -----------
	printf("TEST 4: Changing 3 cards and testing all cards still in deck\n");

	qsort ((void*)(testG.deck[thisPlayer]), testG.deckCount[thisPlayer], sizeof(int), cmpfunc); 
	qsort ((void*)(	G.deck[thisPlayer]), G.deckCount[thisPlayer], sizeof(int), cmpfunc); 

	for (i = 0; i < testG.deckCount[thisPlayer]; i++){
			if (testG.deck[thisPlayer][i] != G.deck[thisPlayer][i]){

				asserttrue(0, 4);
				success = 0;
			    break;
			}
			else {
				success = 1;
			}
	}
	if (success == 1)
			asserttrue(1, 4);

	// ----------- TEST 5: Testing deck of other player stays the same -----------
	printf("TEST 5: Testing deck of other player stays the same\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	
	shuffle(thisPlayer, &testG);
	for (i = 0; i < testG.deckCount[otherPlayer]; i++){
		if (testG.deck[otherPlayer][i] != G.deck[otherPlayer][i]){

				asserttrue(0, 4);
				success = 0;
			    break;
			}
			else {
				success = 1;
			}
	}
	if (success == 1)
		asserttrue(1, 5);
	return 0;
}
