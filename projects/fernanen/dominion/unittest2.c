/* -----------------------------------------------------------------------
 *	buyCards() Tescase
 * -----------------------------------------------------------------------
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int provinces,eachCard,supplyCount =0;
    int i;
    int seed = 1000;
    int numPlayer = 2;
    //int maxBonus = 10;
    int p, r, handCount;
    //int bonus;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;
    // arrays of all coppers, silvers, and golds
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    printf ("TESTING BuyCard():\n");
    for (p = 2; p < 4; p++)
    {
		memset(&G, 23, sizeof(struct gameState));   // clear the game state
		r = initializeGame(p, k, seed, &G);
		for (eachCard =0; eachCard < 25; eachCard++)
		{	
			//memset(&G, 23, sizeof(struct gameState));   // clear the game state
			//r = initializeGame(p, k, seed, &G); // initialize a new game
			printf("Testing coins: \n"); 
			G.numBuys = 100;
			G.coins = 100;  
			#if (NOISY_TEST == 1)
							printf("player = %d , numOFcoins = %d , should PASS: ",p,G.coins);
			#endif
			if(buyCard(eachCard,&G) == 0)
				printf("test PASSED!!!!! \n"); 
			else
				printf("test FAILED!!!!! \n");
			G.coins = 0; 
			#if (NOISY_TEST == 1)
							printf("player = %d ,coins :%d , shold FAIL:",p,G.coins);
			#endif
			if(buyCard(eachCard,&G) == 0)
				printf("test PASSED!!!!! \n"); 
			else
				printf("test FAILED!!!!! \n");
      //------testing empty card -----------------			
			printf("testing empty deck: \n"); 	
			G.coins = 100;
			#if (NOISY_TEST == 1)
							printf("player = %d , num of chosen card: %d , should PASS: ",p,G.supplyCount[eachCard]);
			#endif
			if(buyCard(eachCard,&G) == 0)
				printf("test PASSED!!!!! \n"); 
			else
				printf("test FAILED!!!!! \n");

			G.supplyCount[eachCard] =0;
			#if (NOISY_TEST == 1)
							printf("player = %d , num of chosen card: %d , shold FAIL:",p,G.supplyCount[eachCard]);
			#endif
			if(buyCard(eachCard,&G) == 0)
				printf("test PASSED!!!!! \n"); 
			else
				printf("test FAILED!!!!! \n"); 
		}	  
    }
    printf("All tests passed!\n");
    return 0;
}
