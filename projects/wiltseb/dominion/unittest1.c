#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>


int main(){
	struct gameState Game, TestGame;
	int numPlayers = 2;
	int testPlayer = 0;
	int seed = 10;
	int cards[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	
	//initialize game
	initializeGame(numPlayers, cards, seed, &Game);
	memcpy(&TestGame, &Game, sizeof(struct gameState));
	printf("There are %d players in Game\n", Game.numPlayers);
	printf("There are %d players in TestGame\n", TestGame.numPlayers);

	return 0;
}