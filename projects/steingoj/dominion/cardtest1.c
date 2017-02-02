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
	post.hand[0][0] = smithy; //card that is not smithy
	playSmithy(&post, 0);


	

	//Test that checks if discardCount is incremented by 3
	a = pre.handCount[0];
	b = post.handCount[0];


	
	printf("%d\n", a);
	printf("%d\n", b);
 
	return 0;
}	
