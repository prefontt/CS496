#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


int main(){
	struct gameState TestGame1, TestGame2, TestGame3;
	int numPlayers = 2;
	int seed = 10;
	int cards[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	int p1InitCoins, p2InitCoins, p1CurrCoins, p2CurrCoins;
	
	//initialize games
	initializeGame(numPlayers, cards, seed, &TestGame1);
	memcpy(&TestGame2, &TestGame1, sizeof(struct gameState));
	memcpy(&TestGame3, &TestGame1, sizeof(struct gameState));

	printf("There are %d players in the game\n", TestGame1.numPlayers);
	
	/*
	 * TEST 1: ENSURE UPDATE COINS CORRECTLY ADDS NEW TREASURE CARDS TO COIN COUNT
	 */
	printf("TEST 1: ENSURE UPDATE COINS CORRECTLY ADDS NEW TREASURE CARDS TO COIN COUNT\n");
	//Get initial coins for p1
	updateCoins(0, &TestGame1, 0);
	p1InitCoins = TestGame1.coins;
	printf("Initial coin count in player 1's hand: %d\n", p1InitCoins);

	//Get initial coins for p2
	updateCoins(1, &TestGame1, 0);
	p2InitCoins = TestGame1.coins;
	printf("Initial coin count in player 2's hand: %d\n", p2InitCoins);
	
	//Adds 1 gold, 1 silver, 1 copper to Player 1's hand (total of 6 coins)
	gainCard(gold, &TestGame1, 2, 0);
	gainCard(silver, &TestGame1, 2, 0);
	gainCard(copper, &TestGame1, 2, 0);
	
	//Update coins for both players
	updateCoins(0, &TestGame1, 0);
	p1CurrCoins = TestGame1.coins;
	updateCoins(1, &TestGame1, 0);
	p2CurrCoins = TestGame1.coins;
	
	printf("Expect coin count for p1: %d\nActual: %d\n", p1InitCoins + 6, p1CurrCoins);
	printf("Expected coin count for p2: %d\nActual: %d\n", p2InitCoins, p2CurrCoins);
	
	/*
	 * TEST 2: ENSURE UPDATE COINS CORRECTLY ADDS BONUS TO COIN COUNT
	 */
	 
	//Update player2's coins with 2 bonus coins
	printf("TEST 2: ENSURE UPDATE COINS CORRECTLY ADDS BONUS TO COIN COUNT\n");
	
	//Get initial coin values and set current coins accordingly
	updateCoins(0, &TestGame2, 0);
	p1InitCoins, p1CurrCoins = TestGame2.coins;
	updateCoins(1, &TestGame2, 0);
	p2InitCoins, p2CurrCoins = TestGame2.coins;
	
	updateCoins(1, &TestGame2, 2);
	p2CurrCoins = TestGame2.coins;
	printf("Expect coin count for p1: %d\nActual: %d\n", p1InitCoins, p1CurrCoins);
	printf("Expected coin count for p2: %d\nActual: %d\n", p2InitCoins + 2, p2CurrCoins);
	
	
	return 0;
}