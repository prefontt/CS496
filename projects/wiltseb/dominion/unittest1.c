#include "dominion.h"
#include "dominion_helpers.h"
#include "domtests.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


int main(){
	struct gameState TestGame1;
	int numPlayers = 2;
	int seed = 10;
	int cards[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	int p1InitCoins, p2InitCoins, p1CurrCoins, p2CurrCoins;
	int testFlag = 0;
	int player1 = 0;
	int player2 = 1;
	int i;
	int c;
	int numCardsAdded;
	int initP1HandCt, currP1HandCt;
	
	//initialize games
	initializeGame(numPlayers, cards, seed, &TestGame1);

	
	//store initial coin count for both players
	updateCoins(player1, &TestGame1, 0);
	p1InitCoins = p1CurrCoins = TestGame1.coins;
	
	//Get initial coins for p2
	updateCoins(player2, &TestGame1, 0);
	p2InitCoins = p2CurrCoins = TestGame1.coins;
	
	/*
	 * TEST 1: ENSURE UPDATE COINS CORRECTLY ADDS NEW TREASURE CARDS TO COIN COUNT TO PLAYER 1
	 */
	testFlag = 0;
	
	printf("INITIALIZING TEST 1...\n");

	//Adds 1 gold to p1
	gainCard(gold, &TestGame1, 2, 0);
	updateCoins(player1, &TestGame1, 0);
	p1CurrCoins = TestGame1.coins;
	assertTrue(p1CurrCoins == p1InitCoins + 3, "Player 1 added 1 gold (3 coins)", p1CurrCoins, p1InitCoins + 3, &testFlag);
	
	//Adds 1 copper to p1
	gainCard(silver, &TestGame1, 2, 0);
	updateCoins(player1, &TestGame1, 0);
	p1CurrCoins = TestGame1.coins;
	assertTrue(p1CurrCoins == p1InitCoins + 5, "Player 1 added 1 silver (2 coins)", p1CurrCoins, p1InitCoins + 5, &testFlag);
	
	//Adds 1 copper to p1
	gainCard(copper, &TestGame1, 2, 0);
	updateCoins(player1, &TestGame1, 0);
	p1CurrCoins = TestGame1.coins;
	assertTrue(p1CurrCoins == p1InitCoins + 6, "Player 1 added 1 copper (1 coin)", p1CurrCoins, p1InitCoins + 6, &testFlag);

	checkTest(testFlag, 1);
	
	/*
	 * TEST 2: ENSURE UPDATE COINS CORRECTLY ADDS BONUS TO COIN COUNT
	 */
	testFlag = 0;
	
	//Update player1's coins with 2 bonus coins
	printf("INITIALIZING TEST 2...\n");
	
	//Get initial coin values and set current coins accordingly
	updateCoins(player1, &TestGame1, 0);
	p1InitCoins = p1CurrCoins = TestGame1.coins;
	updateCoins(player2, &TestGame1, 0);
	p2InitCoins = p2CurrCoins = TestGame1.coins;
	
	//Update coins for player 1 with 2 bonus coins
	updateCoins(player1, &TestGame1, 2);
	p1CurrCoins = TestGame1.coins;
	assertTrue(p1CurrCoins == p1InitCoins + 2, "Player 1 gets 2 bonus coins", p1CurrCoins, p1InitCoins + 2, &testFlag);

	checkTest(testFlag, 2);
	
	/*
	 * TEST 3: ENSURE UPDATE COINS FOR PLAYER 1 DOES NOT AFFECT COIN COUNT FOR PLAYER 2
	 */
	testFlag = 0;
	
	printf("INITIALIZING TEST 3...\n");
	//Update coins for both players
	updateCoins(player2, &TestGame1, 0);
	p2CurrCoins = TestGame1.coins;
	assertTrue(p2InitCoins == p2CurrCoins, "Player 2's coin count should not change", p2CurrCoins, p2InitCoins, &testFlag);
	
	checkTest(testFlag, 3);

	/*
	 * TEST 4: ENSURE ADDING NON-TREASURE CARDS DOES NOT AFFECT COIN COUNT
	 */
	testFlag = 0;
	printf("INITIALIZING TEST 4...\n");
	
	//establish initial coint count
	updateCoins(player1, &TestGame1, 0);
	p1InitCoins = TestGame1.coins;
	
	//Add one of each possible non-treasure card to hand
	initP1HandCt = TestGame1.handCount[player1];
	numCardsAdded = 0;
	for (i = 0; i < treasure_map+1; i++){
		//do not add treasure, and make sure card exists in supply to add
		if ((i != gold && i != silver && i != copper) && (TestGame1.supplyCount[i] > 0)){
			gainCard(i, &TestGame1, 2, player1);
			numCardsAdded += 1;
		}
	}

	//Make sure all but 3 treasure cards were added to hand (precondition)
	currP1HandCt = TestGame1.handCount[player1];
	assertTrue(currP1HandCt == (initP1HandCt + numCardsAdded), "Added all but treasure cards", currP1HandCt, initP1HandCt + numCardsAdded, &testFlag);
	
	//update coins after all non-treasure cards are added
	updateCoins(player1, &TestGame1, 0);
	p1CurrCoins = TestGame1.coins;
	assertTrue(p1InitCoins == p1CurrCoins, "Adding non treasure cards does not affect coin count", p1CurrCoins, p1InitCoins, &testFlag);
	
	
	checkTest(testFlag, 4);
	return 0;
}