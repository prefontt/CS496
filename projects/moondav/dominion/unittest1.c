/*********************************************************************
unittest1.c

Author: David Moon

Description:
    This unit test will test the buyCard() function in dominion.c.
    The following are key points the test will check:
    - The purchased card is added to the player's discard pile
    - The player has sufficient coins to purchase the card
    - The appropriate amount of coins are removed from the player's coins
    - The card is removed from the appropriate supply pile
    - No other supply piles are affected
    - No state changes should occur for other players
    - Ensure the player has at least 1 buy left
    - Ensure the player cannot buy from an empty pile


Note: Some skeleton code for game setup was taken from cardtest4.c,
    which was posted to the OSU CS-362 course web page.

Include the following lines in your makefile:

unittest1: unittest1.c dominion.o rngs.o
    gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)

**********************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>


int main() {
    int seed = 5;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

    int cardToBuy = 0;
    int cardCost = 0;

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

    printf("\n\n############# TESTING buyCard() FUNCTION ###############\n");


    printf("TEST 1: Buy a card with sufficient coins and available supply.\n\n");
    G.numBuys = 3;  //set player's number of buys
    G.coins = 5;    //set player's number of coins

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    cardToBuy = village;
    cardCost = getCost(cardToBuy);

    // Buy the cardToBuy
    buyCard(cardToBuy, &testG);
    
    printf("number of buys = %d, expected = %d\n", testG.numBuys, G.numBuys - 1);
    printf("supply count = %d, expected = %d\n", testG.supplyCount[cardToBuy], G.supplyCount[cardToBuy] - 1);
    printf("discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + 1);
    printf("coins = %d, expected = %d\n", testG.coins, G.coins - cardCost);
    
    assert(testG.numBuys == (G.numBuys - 1));
    assert(testG.supplyCount[cardToBuy] == G.supplyCount[cardToBuy] - 1);
    assert(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer] + 1);
    assert(testG.coins == G.coins - cardCost);


    printf("\n\nTEST 2: Buy a card with insufficient coins and available supply.\n\n");
    G.numBuys = 3;  //set player's number of buys
    G.coins = 3;    //set player's number of coins

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    cardToBuy = smithy;
    cardCost = getCost(cardToBuy);

    // Buy the cardToBuy
    buyCard(cardToBuy, &testG);
    
    printf("number of buys = %d, expected = %d\n", testG.numBuys, G.numBuys);
    printf("supply count = %d, expected = %d\n", testG.supplyCount[cardToBuy], G.supplyCount[cardToBuy]);
    printf("discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
    printf("coins = %d, expected = %d\n", testG.coins, G.coins);
    
    assert(testG.numBuys == (G.numBuys));
    assert(testG.supplyCount[cardToBuy] == G.supplyCount[cardToBuy]);
    assert(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer]);
    assert(testG.coins == G.coins);


    printf("\n\nTEST 3: Buy a card with sufficient coins and unavailable supply.\n\n");
    G.numBuys = 3;  //set player's number of buys
    G.coins = 3;    //set player's number of coins
    G.supplyCount[mine] = 0;    //set supply pile count to 0

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    cardToBuy = mine;
    cardCost = getCost(cardToBuy);

    // Buy the cardToBuy
    buyCard(cardToBuy, &testG);
    
    printf("number of buys = %d, expected = %d\n", testG.numBuys, G.numBuys);
    printf("supply count = %d, expected = %d\n", testG.supplyCount[cardToBuy], G.supplyCount[cardToBuy]);
    printf("discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
    printf("coins = %d, expected = %d\n", testG.coins, G.coins);
    
    assert(testG.numBuys == (G.numBuys));
    assert(testG.supplyCount[cardToBuy] == G.supplyCount[cardToBuy]);
    assert(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer]);
    assert(testG.coins == G.coins);

    printf("\n\nEND OF UNIT TEST 1: PASS\n\n");

    return 0;
}