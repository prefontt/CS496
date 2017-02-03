#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1
int ERROR = 0;
#undef assert
#define assert(x) if(!(x)){printf("Assertion Error!\n"); ERROR = 1; }

int PLAYER = 0;
int NUM_PLAYERS = 4;
int LAST_ENUM_VALUE = treasure_map;
int MAXHAND = 5;
int DECK1[] = {baron, copper, council_room, copper};
int DECK2[] = {silver, gold, village, feast, baron};

void fillDeck(int *cards, int size, int player, struct gameState *state)
{
    int i;
    for (i = 0; i < size; i++){
        state->deck[player][i] = (*cards + i);
    }
	state->deckCount[player] = size;
}

void reset(struct gameState *state, int player)
{
	int i;
	//Empty hand
	for(i = 0; i < state->handCount[player]; i++){
		state->hand[player][i] = -1;
	}
	//add smithy to handPos 0
	state->hand[player][0] = smithy;
	state->handCount[player] = 1;
	//Empty deck
	for(i = 0; i < state->deckCount[player]; i++){
		state->deck[player][i] = -1;
	}
	state->deckCount[player] = 0;
	//Empty discard
	for(i = 0; i < state->discardCount[player]; i++){
		state->discard[player][i] = -1;
	}
	state->discardCount[player] = 0;
	
	state->whoseTurn = player;
}

static void handler(int sig)
{
	printf("cardtest2 SIGSEGV\n");
	exit(-1);
}

int main () {
    int returnVal;
	int player = PLAYER;
	int deck1Size = 5;
	int deck2Size = 5;
	struct gameState *state = malloc(sizeof(struct gameState));
	signal(SIGSEGV, handler);
	
	reset(state, player);
	
	//Deck1
	fillDeck(DECK1, deck1Size, player, state);
	returnVal = playSmithy(state, 0);
	assert(returnVal == 0);
	assert(state->handCount[player] == 3);
	assert(state->discardCount[player] == 1);
	assert(state->discard[player][0] == council_room);
	
	reset(state, player);
	
	//Deck2
	fillDeck(DECK2, deck2Size, player, state);
	returnVal = playSmithy(state, 0);
	assert(state->discardCount[player] == 1);
	assert(state->handCount[player] == 3);
	
	reset(state, player);
	
	//NoDeck
	returnVal = playSmithy(state, 0);
	assert(returnVal == -1);
	assert(state->discardCount[player] == 0);
	assert(state->handCount[player] == 1);
	
	free(state);
	
	if(!ERROR){
		printf("cardtest2 finished successfully\n");
	} else{
		printf("cardtest2 finished with errors\n");
	}
    return 0;
}
