#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "asserttrue.h" //Custom assert macro


#define DEBUG 0
#define NOISY_TEST 1


int main () {
	printf("Starting card test 2\n");
	printf("Subject: adventurer\n");
		
	int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

	int a, b;
	
	struct gameState pre;
	struct gameState post;

	initializeGame(2, k, 1, &pre);

	memcpy (&pre, &post, sizeof(struct gameState));

	/*************************************
	//Test adventurer with all copper
	*************************************/
	
	pre.whoseTurn = 0;

	pre.deck[0][0] = copper;
	pre.deck[0][1] = copper;
	pre.deck[0][2] = copper;
	pre.deck[0][3] = copper;
	
	pre.handCount[0] = 1;
	pre.deckCount[0] = 4;
	memcpy (&pre, &post, sizeof(struct gameState));

	playAdventurer(&post);
	

	a = pre.handCount[0];
	b = post.handCount[0];

	printf("Pre: %d\n", a);	
	printf("Post: %d\n", b);


	assertTrue(a+2==b, "Hand count did not increase properly for copper");

	/***********************************
	//Test adventurer with all silver
	***********************************/	
	pre.deck[0][0] = silver;
	pre.deck[0][1] = silver;
	pre.deck[0][2] = silver;
	pre.deck[0][3] = silver;
	
	pre.handCount[0] = 0;	
	pre.deckCount[0] = 4;
	memcpy (&pre, &post, sizeof(struct gameState));

	playAdventurer(&post);

	a = pre.handCount[0];
	b = post.handCount[0];

	assertTrue(a+2==b, "Hand count did not increase properly for silver");

	/***********************************
	//Test adventurer with all gold
	***********************************/	
	pre.deck[0][0] = gold;
	pre.deck[0][1] = gold;
	pre.deck[0][2] = gold;
	pre.deck[0][3] = gold;
	pre.discardCount[0] = 0;
	pre.handCount[0] = 0;	
	pre.deckCount[0] = 4;
	memcpy (&pre, &post, sizeof(struct gameState));

	playAdventurer(&post);

	a = pre.handCount[0];
	b = post.handCount[0];

	//NOTE: RUNS IN AN INFINITE LOOP
	//assertTrue(a+2==b, "Hand count did not increase properly for gold");


	/****************************************
	//Test that cards not taken are discarded
	*******************************************/
	pre.deck[0][1] = smithy;
	pre.deck[0][2] = smithy;
	pre.deck[0][3] = copper;
	pre.deck[0][4] = copper;
	pre.deck[0][5] = copper;
	pre.deck[0][6] = copper;

	
	pre.handCount[0] = 0;	
	pre.deckCount[0] = 4;
	memcpy (&pre, &post, sizeof(struct gameState));

	playAdventurer(&post);

	a = pre.discardCount[0];
	b = post.discardCount[0];
	
	//printf("Pre: %d\n", a);	
	//printf("Post: %d\n", b);
	assertTrue(a!=b, "Cards not discarded properly");


	return 0;
}
