/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   unittest1.c
 * Author: corwinperren
 *
 * Created on February 1, 2017, 9:02 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int testing_assert(int expression);

int main(int argc, char** argv) {
    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy};

    initializeGame(2, k, 65432, &G);

    //If province cards are empty or are least three supply piles are, game end
    //else game is not over. 1 is game end, 0 is game continues
    
    unsigned int min_players = 2;
    unsigned int max_players = MAX_PLAYERS;
    unsigned int max_hand = MAX_HAND;
    unsigned int max_copper = 60;
    unsigned int max_silver = 40;
    unsigned int max_gold = 30;
    unsigned int arbitrary_bonus_max = 1000;
    
    
    
    return (EXIT_SUCCESS);
}

int testing_assert(int expression) {
    if (expression) {
        printf("TEST SUCEEDED!\n");
        return 1;
    } else {
        printf("TEST FAILED!\n");
        return 0;
    }
}
