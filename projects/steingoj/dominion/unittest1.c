#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "asserttrue.h" //Custom assert macro


#define DEBUG 0
#define NOISY_TEST 1


int checkDiscardCard(int handPos,int p, struct gameState *post, int trashFlag) {
	
	int a, b;

	struct gameState pre;
	memcpy (&pre, post, sizeof(struct gameState));
	
	discardCard(handPos, p, post, trashFlag);

	//Check that playedCards increases by 1
	if(trashFlag < 1){
		
		a = pre.playedCardCount + 1;
		b = post->playedCardCount;
		assertTrue(a==b, "Played card count didn't increment");
	}
	//No trash so playedCard should stay the same
	else{
		a = pre.playedCardCount;
		b = post->playedCardCount;
		assertTrue(a==b, "Trashed card was put in played cards"); 	
	}

	//Check that handCount was decremented
	a = pre.handCount[p] - 1;
	b = post->handCount[p];
	assertTrue(a==b, "Hand count was not decremented");	


	
	//If card is last in array or there was only one card, it is replaced with -1  
	if(handPos == pre.handCount[p] - 1 || pre.handCount[p] == 1){
		a = post->hand[p][handPos];
		assertTrue(a==-1, "Last in array or one card and didn't get replaced");
	}
	//Otherwise it's replaced by the card before it
	else{
		a = post->hand[p][handPos];
		b = pre.hand[p][pre.handCount[p] - 1];
		assertTrue(a==b, "Card not replaced by the one before it");
	}

	//NOTE: discardCount is not incremented in the function, but if a card 
	
	//Check that discardCount was incremented
	a = pre.discardCount[p] + 1;
	b = post->discardCount[p];
	assertTrue(a==b, "Discard Count was not incremented");


		return 0;
}




int main () {
	printf("Starting unit test 1\n");
	printf("Subject: discardCard()\n");

	int r, deckCount, discardCount, handCount, p, handPos, trashFlag;

	int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

	struct gameState G;




	
	r = initializeGame(2, k, 1, &G);
	assertTrue(r == 0, "Game not initialized");
		
	for (p = 0; p < 2; p++) {
    		for (deckCount = 0; deckCount < 5; deckCount++) {
      			for (discardCount = 0; discardCount < 5; discardCount++) {
				for (handCount = 0; handCount < 5; handCount++) {
					for(handPos = 0; handPos < handCount; handPos++){
					//For trashFlag set and not set	
						for(trashFlag = 0; trashFlag < 2; trashFlag++){
	  						memset(&G, 23, sizeof(struct gameState)); 
	  						r = initializeGame(2, k, 1, &G);
	  						G.deckCount[p] = deckCount;
	  						memset(G.deck[p], 0, sizeof(int) * deckCount);
	  						G.discardCount[p] = discardCount;
	  						memset(G.discard[p], 0, sizeof(int) * discardCount);
	  						G.handCount[p] = handCount;
	  						memset(G.hand[p], 0, sizeof(int) * handCount);
							G.playedCardCount = 0; //PLAYED CARDS
	  						checkDiscardCard(handPos, p,&G, trashFlag);
	  					}
					}
				}
      			}
    		}
  }
  return 0;
}
