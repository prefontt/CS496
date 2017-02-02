#include "dominion.h"
#include "dominion_helpers.h"
#include "domtests.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>




int main(){
	struct gameState TestGame1, TestGame2, TestGame3;
	int numPlayers = 2;
	int seed = 10;
	int cards[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	int p1InitHandCt, p2InitHandCt, p1CurrHandCt, p2CurrHandCt;
	int p1InitDiscardCt, p2InitDiscardCt, p1CurrDiscardCt, p2CurrDiscardCt;
	int p1InitDeckCt, p2InitDeckCt, p1CurrDeckCt, p2CurrDeckCt;
	int testFlag = 0;
	int player1 = 0;
	int player2 = 1;
	int initSupplyCt[treasure_map+1];
	int i;
	
	//initialize games
	initializeGame(numPlayers, cards, seed, &TestGame1);
	memcpy(&TestGame2, &TestGame1, sizeof(struct gameState));
	memcpy(&TestGame3, &TestGame1, sizeof(struct gameState));
	
	
	//Get initial count of hand, discard, deck
	p1InitHandCt = p1CurrHandCt = TestGame1.handCount[player1];
	p2InitHandCt = p2CurrHandCt = TestGame1.handCount[1];
	p1InitDiscardCt = p1CurrDiscardCt = TestGame1.discardCount[player1];
	p2InitDiscardCt = p2CurrDiscardCt = TestGame1.discardCount[1];
	p1InitDeckCt = p1CurrDeckCt = TestGame1.deckCount[player1];
	p2InitDeckCt = p2CurrDeckCt = TestGame1.deckCount[1];
	
	//Copy initial supply count
	for (i = 0; i < treasure_map+1; i++){
		initSupplyCt[i] = TestGame1.supplyCount[i];
	}
	
	printf("INITIATING TEST 1...\n");
	/*
	 * TEST 1: GAIN CARDS TO EACH PILE
	 */
	//int gainCard(int supplyPos, struct gameState *state, int toFlag, int player)
	  //added card for [whoseTurn] current player:
	  // toFlag = 0 : add to discard
      // toFlag = 1 : add to deck
      // toFlag = 2 : add to hand
	
	testFlag = 0;
	//Player 1 gains a mine to his discard pile
	gainCard(mine, &TestGame1, 0, player1);
	
	//Update current hand, deck, discard count
	p1CurrHandCt = TestGame1.handCount[player1];
	p1CurrDeckCt = TestGame1.deckCount[player1];
	p1CurrDiscardCt = TestGame1.discardCount[player1];
	
	printf("Gaining one mine to discard pile----------------\n");
	assertTrue((p1InitHandCt == p1CurrHandCt), "Player1 hand count", p1CurrHandCt, p1InitHandCt, &testFlag);
	assertTrue((p1InitDeckCt == p1CurrDeckCt), "Player1 deck count", p1CurrDeckCt, p1InitDeckCt, &testFlag);
	assertTrue((p1InitDiscardCt + 1 == p1CurrDiscardCt), "Player1 discard count", p1CurrDiscardCt, p1InitDiscardCt + 1, &testFlag);
	
	//Player 1 gains a smithy to his deck
	gainCard(smithy, &TestGame1, 1, player1);
	
	//Update current hand, deck, discard count
	p1CurrHandCt = TestGame1.handCount[player1];
	p1CurrDeckCt = TestGame1.deckCount[player1];
	p1CurrDiscardCt = TestGame1.discardCount[player1];
	
	//deck and discard pile should have 1 more card in them
	printf("Gaining one smithy to deck----------------\n");
	assertTrue((p1InitHandCt == p1CurrHandCt), "Player1 hand count", p1CurrHandCt, p1InitHandCt, &testFlag);
	assertTrue((p1InitDeckCt + 1 == p1CurrDeckCt), "Player1 deck count", p1CurrDeckCt, p1InitDeckCt + 1, &testFlag);
	assertTrue((p1InitDiscardCt + 1 == p1CurrDiscardCt), "Player1 discard count", p1CurrDiscardCt, p1InitDiscardCt + 1, &testFlag);
	
	//Player 1 gains an adventurer to his hand
	gainCard(adventurer, &TestGame1, 2, player1);
	
	//Update current hand, deck, discard count
	p1CurrHandCt = TestGame1.handCount[player1];
	p1CurrDeckCt = TestGame1.deckCount[player1];
	p1CurrDiscardCt = TestGame1.discardCount[player1];
	
	//deck and discard pile should have 1 more card in them
	printf("Gaining one adventurer to hand----------------\n");
	assertTrue((p1InitHandCt + 1 == p1CurrHandCt), "Player1 hand count", p1CurrHandCt, p1InitHandCt + 1, &testFlag);
	assertTrue((p1InitDeckCt + 1 == p1CurrDeckCt), "Player1 deck count", p1CurrDeckCt, p1InitDeckCt + 1, &testFlag);
	assertTrue((p1InitDiscardCt + 1 == p1CurrDiscardCt), "Player1 discard count", p1CurrDiscardCt, p1InitDiscardCt + 1, &testFlag);

	checkTest(testFlag, 1);

	printf("INITIATING TEST 2...\n");
	/*
	 * TEST 2: CHECK MOST RECENT CARD IN EACH PILE IS CORRECT
	 */
	testFlag = 0;
	assertTrue(TestGame1.discard[player1][p1CurrDiscardCt-1] == mine, "Last card added to hand is adventurer", TestGame1.discard[player1][p1CurrHandCt-1], mine, &testFlag);
	assertTrue(TestGame1.deck[player1][p1CurrDeckCt-1] == smithy, "Last card added to hand is adventurer", TestGame1.deck[player1][p1CurrDeckCt-1], smithy, &testFlag);
	assertTrue(TestGame1.hand[player1][p1CurrHandCt-1] == adventurer, "Last card added to hand is adventurer", TestGame1.hand[player1][p1CurrHandCt-1], adventurer, &testFlag);

	checkTest(testFlag, 2);
	
	printf("INITIATING TEST 3...\n");
	/*
	 * TEST 3: CHECK SUPPLY COUNT FOR EACH CARD
	 */
	testFlag = 0;
	assertTrue(TestGame1.supplyCount[mine] == initSupplyCt[mine]-1, "Mine supply has decreased", TestGame1.supplyCount[mine], initSupplyCt[mine]-1, &testFlag);
	assertTrue(TestGame1.supplyCount[smithy] == initSupplyCt[smithy]-1, "Smithy supply has decreased", TestGame1.supplyCount[smithy], initSupplyCt[smithy]-1, &testFlag);
	assertTrue(TestGame1.supplyCount[adventurer] == initSupplyCt[adventurer]-1, "Mine supply has decreased", TestGame1.supplyCount[adventurer], initSupplyCt[adventurer]-1, &testFlag);

	checkTest(testFlag, 3);
	
	printf("INITIATING TEST 4...\n");
	/*
	 * TEST 4: ENSURE NO CHANGES IN PLAYER 2 PILES
	 */
	testFlag = 0;
	//Update current hand, deck, discard count
	p1CurrHandCt = TestGame1.handCount[player2];
	p1CurrDeckCt = TestGame1.deckCount[player2];
	p1CurrDiscardCt = TestGame1.discardCount[player2];
	
	assertTrue((p2InitHandCt == p2CurrHandCt), "Player1 hand count", p2CurrHandCt, p2InitHandCt, &testFlag);
	assertTrue((p2InitDeckCt == p2CurrDeckCt), "Player1 deck count", p2CurrDeckCt, p2InitDeckCt, &testFlag);
	assertTrue((p2InitDiscardCt == p2CurrDiscardCt), "Player1 discard count", p2CurrDiscardCt, p2InitDiscardCt, &testFlag);

	checkTest(testFlag, 4);

	return 0;
}