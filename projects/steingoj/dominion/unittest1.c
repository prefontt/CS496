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
	printf("Starting unit test 1\n");
	printf("Subject: discardCard()\n");

	int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

	int a, b, i;

	struct gameState pre;
	struct gameState post;
	initializeGame(2, k, 1, &pre);

	memcpy (&pre, &post, sizeof(struct gameState));
	
	//discardCard(handPos, p, post, trashFlag);

	/*************************************************************
	//Check that playedCards increases by 1 with trashFlag not set
	**************************************************************/
	post.hand[0][0] = copper;
	discardCard(0, 0, &post, 0); 	
	a = pre.playedCardCount + 1;
	b = post.playedCardCount;
	assertTrue(a==b, "Played card count didn't increment");
	
	/*************************************************************
	//Check that playedCards doesn't increase with trashFlag set 	
	**************************************************************/
	initializeGame(2, k, 1, &pre);
	memcpy (&pre, &post, sizeof(struct gameState));
	post.hand[0][0] = copper;
	discardCard(0, 0, &post, 1); 	
	a = pre.playedCardCount;
	b = post.playedCardCount;
	assertTrue(a==b, "Trashed card was put in played cards"); 	
	
	/*************************************************************
	//Check that handCount was decremented
	*************************************************************/
	initializeGame(2, k, 1, &pre);
	memcpy (&pre, &post, sizeof(struct gameState));
	post.hand[0][0] = copper;
	discardCard(0, 0, &post, 0);
	a = pre.handCount[0] - 1;
	b = post.handCount[0];
	assertTrue(a==b, "Hand count was not decremented");	

	/************************************************************
 	//Check if card discarded is last in array
 	************************************************************/	 
	initializeGame(2, k, 1, &pre);
	memcpy (&pre, &post, sizeof(struct gameState));
	post.hand[0][post.handCount[0]] = copper; //place copper in last position
	discardCard(post.handCount[0], 0, &post, 0);
	a = post.hand[0][post.handCount[0]];
	assertTrue(a==-1, "Last in array didn't get replaced"); 	
	/***********************************************************
 	//Check if card is last card in hand
 	***********************************************************/ 
	initializeGame(2, k, 1, &pre);
	memcpy (&pre, &post, sizeof(struct gameState));
	for(i = 0; i < post.handCount[0]; i++){ //Remove all cards in hand
		post.hand[0][i] = -1;
	}
	post.handCount[0] = 0;
	post.hand[0][0] = copper; //Add one lone card
	post.handCount[0]++; //Add to count 
	discardCard(0, 0, &post, 0);
	a = post.handCount[0];
	b = post.hand[0][0];
	assertTrue(a==0, "Remove last card didn't work");
	assertTrue(b==-1, "Last card not changed to -1");	

	/******************************************************
	//Test for non special case card discard
	******************************************************/

	initializeGame(2, k, 1, &pre);
	memcpy (&pre, &post, sizeof(struct gameState));
	discardCard(1, 0, &post, 0);
	a = post.hand[0][1];
	b = pre.hand[0][0];
	assertTrue(a==b, "Card not replaced by the one before it");
	

	//NOTE: discardCount is not incremented in the function, but if a card 
/*	
	//Check that discardCount was incremented
	a = pre.discardCount[p] + 1;
	b = post->discardCount[p];
	assertTrue(a==b, "Discard Count was not incremented");
*/


  return 0;
}
