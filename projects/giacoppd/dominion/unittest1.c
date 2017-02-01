//Dominic Giacoppe, SF2, unit test 1
//tests update coins
#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion.c"
#include "rngs.h"
#include "rngs.c"

void aborttest(char * msg)
{
printf("%s\n", msg);
exit(1);
//this func just prints things for me
}

int main()
{
struct gameState current;
current.handCount[0] = 5; //normal setup test
current.hand[0][0] = copper;
current.hand[0][1] = silver;
current.hand[0][2] = gold;
current.hand[0][3] = baron;
current.hand[0][4] = mine;
updateCoins(0, &current, 0);
if(current.coins != 6)
	aborttest("Coins don't equal 6 unittest1");

current.handCount[1] = 6; //no money test
current.hand[1][0] = baron;
current.hand[1][1] = adventurer;
current.hand[1][2] = mine;
current.hand[1][3] = baron;
current.hand[1][4] = mine;
current.hand[1][5] = village;
updateCoins(1, &current, 0);
if(current.coins != 0)
	aborttest("No money has money unittest1");
updateCoins(1, &current, 5); //bonus test
if(current.coins != 5)
	aborttest("Bonus didn't work unittest1");
return 0;
}
