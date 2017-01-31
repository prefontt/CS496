#include <stdlib.h>
#include <stdio.h>
#include "asserttrue.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int getcosttest(){
	int i;
	int testcost;	//this is the cost we use to evaluate the function
	
	testcost = getCost(silver); 	//manually test the cost of silver
	asserttrue(testcost == 3);
	testcost = getCost(gardens);	//manually test the cost of gardens
	asserttrue(testcost == 4);
	testcost = getCost(minion);		//manually test the cost of minion
	asserttrue(testcost == 5);
	testcost = getCost(adventurer);	//manually test the cost of adventurer
	asserttrue(testcost == 6);
	
	//test testcost against 10 invalid numbers for cost
	int invalidcost[] = {-99, -2, -1, -5, -3, 70, 99, 150, 306, 1010};		
	for(i = 0; i < 10; i++){
		testcost = getCost(invalidcost[i]);
		asserttrue(testcost == -1);
	}
	
	//compare testcost against 10 valid numbers for cost
	int validcost[] = {0, 2, 5, 8, 0, 3, 6, 6, 5, 4};
	for (i = 0; i < 10; i++) {
		testcost = getCost(i);
		asserttrue(testcost == validcost[i]);	//print results
	}
	
	return 0;
}

int main(){return getcosttest();}