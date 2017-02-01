#include <stdlib.h>
#include <stdio.h>
#include "asserttrue.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int main(int argc, char** argv){
	struct gameState GSvar;			//initialize gameState
	//manually set game variables for testing
	GSvar.whoseTurn = 0;
	GSvar.numActions = 1;
	GSvar.handCount[0] = 1;
	GSvar.hand[0][0] = smithy;
	GSvar.deckCount[0] = 3;
	GSvar.deck[0][0] = copper;  
	GSvar.deck[0][1] = copper;  
	GSvar.deck[0][2] = copper;  
	GSvar.discardCount[0] = 0;
	
	//play smithy card for testing and print results 
	playCard(0,0,0,0,&GSvar);				//play smithy card
	asserttrue(GSvar.handCount[0] == 3);	//testing hand count
	asserttrue(GSvar.deckCount[0] == 0);	//testing deck count 
	//testing each card in hand
	asserttrue(GSvar.hand[0][0] == copper);
	asserttrue(GSvar.hand[0][1] == copper);
	asserttrue(GSvar.hand[0][2] == copper);
	asserttrue(GSvar.numActions == 0);		//testing action count
	
	return 0;
}