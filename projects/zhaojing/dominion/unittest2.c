#include <stdlib.h>
#include <stdio.h>
#include "asserttrue.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int main(int argc, char ** argv){
	printf("******begin unit test on isGameOver()******\n");
	
	//initialize game
	struct gameState G;
	int result, randomVar = 0;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	randomVar = rand() % 10;
	result = initializeGame(2, k, randomVar, &G);
	int i, j;
	
	//test for whether game ends when there are province and supply cards
	printf("testing non-empty province and supply stacks\n");
	G.supplyCount[province] == 5;
	for(i = 0; i < 25; i++) G.supplyCount[i] = 1;
	result = isGameOver(&G);
	asserttrue(result == 0);
	
	//test for whether game ends when only province stack is empty
	printf("testing empty province stack\n");
	G.supplyCount[province] == 0;
	for(i = 0; i < 25; i++) G.supplyCount[i] = 1;
	result = isGameOver(&G);
	asserttrue(result == 1);
	
	//test for whether game ends when only 3 supply piles are empty
	printf("testing empty supply stacks\n");
	G.supplyCount[province] == 3;
	for(i = 0; i < 25; i++) G.supplyCount[i] = 0;
	result = isGameOver(&G);
	asserttrue(result == 1);
	
	//test for whether game ends when both province and supply are empty
	printf("testing empty province and supply stacks\n");
	G.supplyCount[province] == 0;
	for(i = 0; i < 25; i++) G.supplyCount[i] = 0;
	result = isGameOver(&G);
	asserttrue(result == 1);
	
	printf("******end unit test on isGameOver()******\n");
	return 0;
}