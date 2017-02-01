#include <stdlib.h>
#include <stdio.h>
#include "asserttrue.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int main(int argc, char** argv){
	struct gameState GSvar;					//initialize gameState
	//manually set game variables for testing 
	GSvar.whoseTurn = 0;
	GSvar.numActions = 1;
	GSvar.handCount[0] = 1;
	GSvar.hand[0][0] = adventurer;
	GSvar.deckCount[0] = 3;
	GSvar.deck[0][0] = province;
	GSvar.deck[0][1] = copper;
	GSvar.deck[0][2] = silver;
	GSvar.discardCount[0] = 0;

	//play adventurer for testing and print results
	playCard( 0, 0, 0, 0, &GSvar);			//play adventurer for testing 
	asserttrue(GSvar.handCount[0] == 0);	//testing handcount
	asserttrue(GSvar.numActions == 3);		//testing number of actions
	asserttrue(GSvar.deckCount[0] == 0);	//testing deck size
	asserttrue(GSvar.discardCount[0] == 3);	//testing discard count

	return 0;
}