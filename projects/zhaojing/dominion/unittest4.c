#include <stdlib.h>
#include <stdio.h>
#include "asserttrue.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int supplycounttest(){
    int testevaluation = -1;	//initialize test evaluation status where -1 is fail and 0 is pass
    struct gameState GSvar;		//initialize gamestate
    
	//manually set GSvar for testing
	GSvar.supplyCount[copper] = 2;
	//call supplyCount for testing
    testevaluation = supplyCount(copper, &GSvar);
    asserttrue (testevaluation == 2);
	testevaluation = 0;

	//manually set GSvar for testing
	GSvar.supplyCount[silver] = 4;
	//call supplyCount for testing
    testevaluation = supplyCount(silver, &GSvar);
    asserttrue (testevaluation == 4);
	testevaluation = 0;

	//manually set GSvar for testing
	GSvar.supplyCount[gold] = 6;
	//call supplyCount for testing
	testevaluation = supplyCount(gold, &GSvar);
    asserttrue (testevaluation == 6);			//print results
	testevaluation = 0;
	
    return testevaluation;
}

int main(){return supplycounttest();}