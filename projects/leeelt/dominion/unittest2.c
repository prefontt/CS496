/* -----------------------------------------------------------------------
 * Author: Elton Lee
 * Date: 2-4-2017
 * unittest1.c
 * unit test for discardCard function
 * Include the following lines in your makefile:
 *
 * unittest2: unittest2.c dominion.o rngs.o
 *      gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main(){
	int i;
	int seed = 1000;
	int numPlayer = 2;
	int p;
	int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;

	printf ("TESTING discardCoins():\n");
	for (p=0; p < numPlayer; p++){
		memset(&G, 23, sizeof(struct gameState)); // clear the game state
		initializeGame(numPlayer, k, seed, &G);  // initialize a new game
		initTest(&G, p);
		printf("Testing trashFlag = 0\n");
		discardCard(1, p, &G, 0);
		printf("playedCardCount = %d, playedCardsEnum = %d,  expected %d, %d \n", G.playedCardCount, G.playedCards[0], 1, gold);
		assert(G.playedCardCount == 1 && G.playedCards[0] == gold);
	}
	printf("All tests passed!\n");
	return 0;
}

// function to initialize hand with pre-set 5 cards.
int initTest(struct gameState *G, int p){
	G->handCount[p] = 5;
	G->hand[p][0] = silver;
	G->hand[p][1] = gold;
	G->hand[p][2] = adventurer;
	G->hand[p][3] = smithy;
	G->hand[p][4] = copper;
	G->playedCardCount = 0;
	return 0;
}