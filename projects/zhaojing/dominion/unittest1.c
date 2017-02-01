#include <stdlib.h>
#include <stdio.h>
#include "asserttrue.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int shuffletest(){
    int testevaluation = -1;			//initialize test evaluation status where -1 is fail and 0 is pass
    int playervar = 0;					//initialize player variable
    struct gameState GSvar;				//initialize gamestate

	//test shuffle() with deckCount of 3
    GSvar.deckCount[playervar] = 3;		//Manually adjust GSvar for testing
    GSvar.deck[playervar][0] = copper;		//Manually adjust GSvar for testing
    GSvar.deck[playervar][1] = silver;		//Manually adjust GSvar for testing
    GSvar.deck[playervar][2] = gold;		//Manually adjust GSvar for testing
    testevaluation = shuffle(playervar, &GSvar);	//call shuffle() function for testing
    if (testevaluation < 0) return testevaluation;

    //test shuffle() with deck of 0
    int testDeck[MAX_DECK] = {0};				//initialize deck
    int i;
    //For each of the cards we had, set cardSet's index of that card to 1
    for (i=0 ; i<3 ; i++) testDeck[GSvar.deck[playervar][i]] = 1;		//iterate through cards and set index to 1
    asserttrue(testDeck[copper] && testDeck[silver] && testDeck[gold]);	//check if all the cards in testDeck are set to 1 and print results
    testevaluation = 0;
    return testevaluation;
}

int main(){return shuffletest();}