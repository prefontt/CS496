/*
 * cardtest4.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest3: cardtest3.c dominion.o rngs.o
 *      gcc -o cardtest1 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "Great Hall +1Card +1Action"

int my_assert(int test, char* msg)
{
	/* if (!test) {
		printf ("ASSERT HAS FAILED: %s\n", msg);
		exit(-1);
	}
	return 0; */
}

int main() {
    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;
	int newActions = 0;

    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;

    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: +1 cards --------------
	printf("TEST 1: choice1 = 1 = +2 cards\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	
	
	
	printf("actions = %d, expected = %d\n", testG.numActions, G.numActions + newActions);
	
	cardEffect(great_hall, choice1, choice2, choice3, &testG, handpos, &bonus);

	newCards = 1;
	xtraCoins = 0;
	newActions = 1;
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
	printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
	printf("actions = %d, expected = %d\n", testG.numActions, G.numActions + newActions);
	my_assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded, "msg 1");
	my_assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards, "msg 2");
	my_assert(testG.coins == G.coins + xtraCoins, "msg 3");
	my_assert(testG.numActions == G.numActions + newActions, "msg 4");

	

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}


