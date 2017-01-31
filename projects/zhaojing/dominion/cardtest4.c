#include <stdlib.h>
#include <stdio.h>
#include "asserttrue.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int main(int argc, char** argv){
	struct gameState GSvar;			//initialize gameState
	//manually set up cards and variables for testing
	GSvar.whoseTurn = 0;
	GSvar.numActions = 1;
	GSvar.handCount[0] = 1;
	GSvar.hand[0][0] = village;
	GSvar.deckCount[0] = 1;
	GSvar.deck[0][0] = province;
	GSvar.discardCount[0] = 0;
	
	//play village card for testing and print results
	playCard(0,0,0,0, &GSvar);				//play village card
	asserttrue(GSvar.numActions == 2);		//testing number of actions 
	asserttrue(GSvar.deckCount[0] == 0);	//testing deck count 
	asserttrue(GSvar.handCount[0] == 1);	//testing hand count
	asserttrue(GSvar.hand[0][0] == province);	//testing card in hand

	return 0;
}