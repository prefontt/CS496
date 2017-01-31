//this is the unit test for buycard()

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int checkBuyCard(int supplyPos, struct gameState *post){
	int passFlag = 0;
	//Save current gamestate in pre
	struct gameState pre;
	memcpy (&pre, post, sizeof(struct gameState));
	
	//get player turn
	int player = post->whoseTurn;
	
	//Test call with bad input
	int r;
	r=buyCard(-100, post);
	if(r == 0){
		printf("TEST FAIL. buyCard returned successfully with nonexistent card index\n");
		passFlag++;
	else{
		if(memcmp(&pre, post, sizeof(struct gameState)) == 0)
			printf("TEST PASS. Call failed with bad input and gamestate was unchanged\n");
		else{
			printf("TEST FAIL. Call failed and returned %d, but gamestate was altered\n", r);
			passFlag++;
		}	
}
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
	post->numBuys = pre.numBuys;

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
	post->supplyCount[supplyPos] = pre.supplyCount[supplyPos];

	//Test buying a card that's too expensive (smithy)
	post->coins = 3;
	int q;
	q = buyCard(supplyPos, post);
	if(q != -1){
		printf("TEST FAIL. buyCard did not return -1 when attempting to buy card that was too expensive\n");
		passFlag++;
		}
	else
		printf("TEST PASS. buyCard returned -1 when attempting to buy card that was too expensive\n");

	//set coins so next call will pass
	post->coins = 4;

	//Standard call that should return correctly so we can test results
	buyCard(supplyPos, post);

	//Test that after call, player has one more card, 4 fewer coins (since we're buying a smithy card), card in discard, and correct # of buys
	if(post->discardCount[player] == (pre.discardCount[player] + 1))
		printf("TEST PASS. Player has one more card after buy\n");
	else{
		printf("TEST FAIL. Player does not have one more card after buy\n");
		passFlag++;
	}
	if(post->coins == 0)
		printf("TEST PASS. Player had correct number of coins deducted after buy\n");
	else{
		printf("TEST FAIL. Player did not have correct number of coins deducted after buy\n");
		passFlag++;
	}

	
	if(post->discard[player][post->discardCount[player]] == supplyPos)
		printf("TEST PASS. Player had correct card added to discard\n");
	else{
		printf("TEST FAIL. Player did not have correct card added to discard\n");
		passFlag++;
	}

	
	if(post->numBuys == (pre.numBuys - 1))
		printf("TEST PASS. Correct number of buys left after call\n");
	else{
		printf("TEST FAIL. Incorrect number of buys left after call\n");
		passFlag++;
	}

	//Test that after call, all other player discard numbers are the same
	
	for(int i = 0; i < pre.numPlayers; i++){
		if(i == post->whoseTurn)
			printf("It was player %d's turn, card total should differ. Before call, it was %d. After call it is %d.\n", i, pre.discardCount[i], post->discardCount[i]);
		else{
			if(pre.discardCount[i] != post->discardCount[i]){
				printf("TEST FAIL. Before call, player %d's total: %d. After call, total is %d.\n", i, pre.discardCount[i], post->discardCount[i]);
		passFlag++;
			}

			else
				printf("TEST PASS. Before call, player %d's total: %d. After call, total is %d.\n", i, pre.discardCount[i], post->discardCount[i]);
		}
	}

	//Test that after call, supply count of card bought is one fewer

	if(post->supplyCount[supplyPos] == (pre.supplyCount[supplyPos] - 1))
		printf("TEST PASS. Correct number of supply remaining post call\n");
	else{
		printf("TEST FAIL. Incorrect number of supply remaining post call\n");
		passFlag++;
	}

	if(passFlag == 0)
		printf("ALL TESTS OK \n");
	
	return 0;

}

int main(){
	
	int deckCount = 20;
	int discardCount = 10;
	int handCount = 5;
	int supplyPos = smithy;

	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

	struct gameState G;
	G.supplyCount[smithy] = 5;
	G.coins = 5;
	G.numBuys = 1;

	checkBuyCard(smithy, &G);
	return 0;
}
