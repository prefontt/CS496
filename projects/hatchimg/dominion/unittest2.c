//this is the unit test for buycard()

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

void assertValues(int a, int b){

	if(a == b)
		printf("TEST PASS");
	else
		printf("TEST FAIL");

}
int checkBuyCard(int supplyPos, struct gameState *post){
	int passFlag = 0;
	//Save current gamestate in pre
	struct gameState pre;
	memcpy (&pre, post, sizeof(gameState));

	//Test buying with no buys
	post->numBuys = 0;
	int x;
	x = buyCard(supplyPos, post);
	if(x != -1){
		printf("TEST FAIL. buyCard did not return -1 with 0 buys\n");
		passFlag++;
		}
	else
		printf("TEST PASS. buyCard returned -1 when called with 0 buys\n");

	//reset numBuys before performing next test
	post->numBuys = pre->numBuys;

	//Test buying with no supply left
	post->supplyCount[supplyPos] = 0;
	int y;
	y = buyCard(supplyPos, post);
	if(y != -1){
		printf("TEST FAIL. buyCard did not return -1 with 0 of card type remaining\n");
		passFlag++;
		}
	else
		printf("TEST PASS. buyCard returned -1 when called with 0 of card type remaining\n");

	//reset supply total before performing next test
	post->supplyCount[supplyPos] = pre->supplyCount[supplyPos];

	//Test buying a card that's too expensive
	
	//Standard call that should return correctly so we can test results

	//Test that after call, player has one more card, x fewer coins, card in hand, and correct # of buys

	//Test that after call, all other player discard numbers are the same
	
	for(int i = 0; i < pre->numPlayers; i++){
		if(i == post->whoseTurn)
			printf("It was player %d's turn, card total should differ. Before call, it was %d. After call it is %d.\n", i, pre->discardCount[i], post->discardCount[i]);
		else{
			if(pre->discardCount[i] != post->discardCount[i]
				printf("TEST FAIL. Before call, player %d's total: %d. After call, total is %d.\n", i, pre->discardCount[i], post->discardCount[i]);
			else
				printf("TEST PASS. Before call, player %d's total: %d. After call, total is %d.\n", i, pre->discardCount[i], post->discardCount[i]);
		}
	}

	//Test that after call, supply count of card bought is one fewer

	if(post->supplyCount[supplyPos] == (pre->supplyCount[supplyPos] - 1))
		printf("TEST PASS. Correct number of supply remaining post call\n");
	else
		printf("TEST FAIL. Incorrect number of supply remaining post call\n");

	if(passFlag == 0)
		printf("ALL TESTS OK \n");
	
	return 0;

}
