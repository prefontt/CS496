#include <stdlib.h>
#include <stdio.h>
#include "asserttrue.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int whoseturntest(){
    int testevaluation = -1;		//initialize test evaluation status where -1 is fail and 0 is pass
    int playervar = 0;				//initialize player variable
    struct gameState GSvar;			//initialize gamestate
    int randomnumber = 4;			//set random number to 4 
	
    // Create card variables (arbitrarily using cards from the deck)
    int cardvar[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	//initialize game
    testevaluation = initializeGame(2, cardvar, randomnumber, &GSvar);
    asserttrue (testevaluation == 0);
    //call whoseTurn() for testing
    testevaluation = whoseTurn(&GSvar);
    //check player turn and print results
    asserttrue (testevaluation == 0);
    testevaluation = 0;
    return testevaluation;
}

int main(){return whoseturntest();}