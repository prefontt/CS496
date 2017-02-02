//Dominic Giacoppe, SF2, card test 1
//tests smithy
#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "rngs.h"
#include "createTestState.c"

void aborttest(char * msg)
{
printf("%s\n", msg);
exit(1);
//this func just prints things for me
}

int main()
{
struct gameState * current = newGame();
current = stateMaker(3, current);
current->hand[0][3] = smithy;
current->handCount[0]++; //add smithy to hand on top of the fake game state
int handSize = current->handCount[0];
printf("Current # of cards for player 0: %d\n", (*current).handCount[0]);
cardEffect(smithy, 0,0,0, current, 3, 0);
printf("Current # of cards for player 0 after smithy: %d\n", current->handCount[0]);
if(handSize+2 != current->handCount[0]) //+3 for smithy -1 after discarding smithy so +2 overall
	aborttest("Number of cards for smithy is wrong, cardtest1\n"); 
return 0;
}
