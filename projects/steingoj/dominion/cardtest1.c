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
	printf("Starting card test 1\n");
	printf("Subject: smithy\n");
		
	int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

	int a, b;
	
	struct gameState pre;
	struct gameState post;

	initializeGame(2, k, 1, &pre);

	memcpy (&pre, &post, sizeof(struct gameState));

	
	//MAYBE REMOVE
	/*******************************************************
	//Test for when the method is called and no card exists	
	*******************************************************/
	pre.handCount[0] = 1;
	pre.deckCount[0] = 3;
	post.handCount[0] = 1;
	//post.deckCount[0] = 3;
	pre.deck[0][0] = copper;
	pre.deck[0][1] = copper;
	pre.deck[0][2] = copper;
	  
	post.hand[0][0] = smithy; //Doesn't matter what the card is named 
	post.whoseTurn = 0;
	playSmithy(&post, 0);

	//Test that checks if deckCount  is unchanged
	a = pre.deckCount[0];
	b = post.deckCount[0];
	assertTrue(a-3==b,"deckCount not changed\n");

	//printf("Pre: %d\n", a);
	//printf("Post: %d\n", b);
 
	//Test if discardCount is incremented by 1
	a = pre.discardCount[0];
	b = post.discardCount[0];
	assertTrue(a+1==b, "discardCount did not increment\n");
	

	//Test if handCount decreases by 1 
	a = pre.handCount[0];
	b = post.handCount[0];
	assertTrue(a-1==b, "handCount did not decrease\n");
	
	return 0;
}	
