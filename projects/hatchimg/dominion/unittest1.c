//This is the unit test for shuffle()

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
int checkShuffle(int player, struct gameState *post){

	//Save current gamestate in pre
	struct gameState pre;
	memcpy (&pre, post, sizeof(gameState));

	//ensure that after call to shuffle(), deck size is unchanged but order is different
	shuffle(player, post);
	assert(post->deckCount[player] == pre->deckCount[player]);
	
	for(int i = 0; i < post->deckCount[player]; i++){
		if(post->deck[player][i] == pre->deck[player][i])
			if(i == (post->deckCount[player] - 1))
				printf("TEST FAIL");
		else
			printf("TEST PASS");
	}

	//check that 

	//test that shuffle fails and returns -1 if deckcount of player > 1
	int x;
	post->deckCount[player] = 0;
	x = shuffle(player, post);
	assert(x == -1);



}
