/* cardtest1.c
Card tested: Smithy

Basic requirements:
-- Decreases hand count + discard count + deck count by 1
-- Increases playedCardCount by 1
-- Adds card previously at handPos to playedCards
-- Removes card previously at handPos from hand
-- Does not change game state except for current player

-- Increases hand count by 2 (3 cards drawn - 1 Smithy card played)
-- Decreases discard count + deck count by 3
-- 3 cards are added to Hand and 3 cards are removed from Discard + Deck
-- The 3 cards added to hand are the 3 cards removed from discard + deck
*/


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define CARD_NAME "Smithy"
#define NOISY_TEST 1

/* Function to test general requirements that apply to most cards and Deck+Hand+Discard scenarios:
-- Decreases hand count + discard count + deck count by 1
-- Increases playedCardCount by 1
-- Adds card previously at handPos to playedCards
-- Removes card previously at handPos from hand
-- Does not change game state except for current player
 */

void testGeneralRequirements(int caseCount, char* casename, int* testCount, int* r_main,
    int card, int choice1, int choice2, int choice3, int handPos, int* bonus,
    struct gameState* G, struct gameState* preG) 
{
    int count1, count2, r, i;
    struct gameState preG_mod;
    int player = G->whoseTurn;

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Successful execution\n", caseCount, casename, ++(*testCount));
    r = cardEffect(card, choice1, choice2, choice3, G, handPos, bonus);
    asserttrue(r==0, r_main); 
    if (NOISY_TEST) {
        printf("Before execution:\n");
        printCurrentPlayer(player, preG);
        printf("After execution:\n");
        printCurrentPlayer(player, G);
    }   

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Hand count + Discard count + Deck count decreased by 1\n", caseCount, casename, ++(*testCount));
    count1 = preG->handCount[player] + preG->discardCount[player] + preG->deckCount[player];
    count2 = G->handCount[player] + G->discardCount[player] + G->deckCount[player];
    asserttrue(count1=count2-1, r_main);
    if (NOISY_TEST) printf("Count before: %d\nCount after: %d\n", count1, count2);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Played card count increased by 1\n", caseCount, casename, ++(*testCount));
    count1 = preG->playedCardCount;
    count2 = G->playedCardCount;
    asserttrue(count2==count1+1, r_main);
    if (NOISY_TEST) printf("Played count before: %d\nPlayed count after: %d\n", count1, count2);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Card at handPos added to playedCards\n", caseCount, casename, ++(*testCount));
    asserttrue(G->playedCards[G->playedCardCount-1] == preG->hand[player][handPos], r_main);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Card at handPos removed from current player's hand\n", caseCount, casename, ++(*testCount));
    count1 = getNumCardsHand(player, card, preG);
    count2 = getNumCardsHand(player, card, G);
    asserttrue(count2==count1-1, r_main);
    if (NOISY_TEST) printf("Card at handPos: %s\nCard count before: %d\nCard count after: %d\n", 
        getCardName(preG->hand[player][handPos]), count1, count2);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Game state unchanged except for played card and current player\n", caseCount, casename, ++(*testCount));
    memcpy(&preG_mod, G, sizeof(struct gameState));
    preG_mod.handCount[player] = G->handCount[player];  // make current player's hand, deck, discard before execution equal after execution
    for (i=0; i<MAX_HAND; i++) preG_mod.hand[player][i] = G->hand[player][i];
    preG_mod.deckCount[player] = G->deckCount[player];
    for (i=0; i<MAX_DECK; i++) preG_mod.deck[player][i] = G->deck[player][i];
    preG_mod.discardCount[player] = G->discardCount[player];
    for (i=0; i<MAX_DECK; i++) preG_mod.discard[player][i] = G->discard[player][i];
    preG_mod.playedCardCount = G->playedCardCount;
    for (i=0; i<MAX_DECK; i++) preG_mod.playedCards[i] = G->playedCards[i];
    asserttrue(memcmp(G, &preG_mod, sizeof(struct gameState))==0, r_main);
}



/*********************************************************************/
/* Main */
int main() {
    int seed = 1000;
    struct gameState G, preG, G_mod, preG_mod;
    int numPlayer = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine, 
      remodel, smithy, village, baron, great_hall};
    int r_main = 0;
    int testCount = 0, caseCount = 0;

    int handPos = 0;
    int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;  // dummy parameters; won't be used for this card
    int player, card, i, j;
    int count1, count2;

    char* casename;

    printf("**********************************************************\n");
    printf("BEGIN testing %s\n", CARD_NAME);
    

    // /*-------------------------------------------------------------------------*/
    // casename = "3+ cards in Deck, empty Discard";
    // caseCount++;
    // initializeGame(numPlayer, k, seed, &G);
    // player = G.whoseTurn;
    // G.hand[player][handPos] = smithy; // make current card smithy
    // card = G.hand[player][handPos];  // card previously at handPos
    // assert(G.deckCount[player] >=3); // Deck should have 5 cards after initialization
    // memcpy(&preG, &G, sizeof(struct gameState));  // save gameState to preG

    // /*********/
    // testGeneralRequirements(caseCount, casename, &testCount, &r_main,
    //     card, choice1, choice2, choice3, handPos, &bonus,
    //     &G, &preG);

    // /*********/
    // printf("---------CASE %d: %s -- TEST %d: Hand count increased by 2\n", caseCount, casename, ++testCount);
    // count1 = preG.handCount[player];
    // count2 = G.handCount[player];
    // asserttrue(count2==count1+2, &r_main);
    // if (NOISY_TEST) printf("Hand count before: %d\nHand count after: %d\n", count1, count2);

    // /*********/
    // printf("---------CASE %d: %s -- TEST %d: Discard count + Deck count decreased by 3\n", caseCount, casename, ++testCount);
    // count1 = preG.handCount[player];
    // count2 = G.handCount[player];
    // asserttrue(count2==count1+2, &r_main);
    // if (NOISY_TEST) printf("Discard count + Deck count before: %d\nDiscard count + Deck count after: %d\n", count1, count2);

    // /*********/
    // printf("---------CASE %d: %s -- TEST %d: 3 new cards added to Hand\n", caseCount, casename, ++testCount);
    // assert(G.handCount[player] >= 3);  // hand should have 3+ cards
    // memcpy(&G_mod, &G, sizeof(struct gameState));  // make a copy of G & preG that can be modified
    // memcpy(&preG_mod, &preG, sizeof(struct gameState));
    // // What cards were added to Hand?
    // for (i=0; i<G_mod.handCount[player]; i++) {
    //     if (G_mod.hand[player][i] == smithy) {
    //         G_mod.hand[player][i] = -1;  // cross out Smithy as it'd be moved to played
    //     }
    //     for (j=0; j<preG_mod.handCount[player]; j++) {
    //         if (G_mod.hand[player][i] == preG_mod.hand[player][j] && G_mod.hand[player][i] != -1) {
    //             G_mod.hand[player][i] = -1;  // cross out cards that appear in both G_mod.hand and preG_mod.hand
    //             preG_mod.hand[player][j] = -1;
    //             break;
    //         }
    //     }
    // }
    // // Added cards are those uncrossed in G_mod.hand
    // count1 = 0;
    // for (i=0; i<G_mod.handCount[player]; i++) {
    //     if (G_mod.hand[player][i] > 0) {
    //         count1++;  // how many new cards in Hand?
    //         if (NOISY_TEST) printf("Card added to Hand #%d: %s\n", count1, getCardName(G_mod.hand[player][i]));
    //     }
    // }
    // asserttrue(count1==3, &r_main);


    // /*********/
    // printf("---------CASE %d: %s -- TEST %d: 3 cards removed from Deck+Discard\n", caseCount, casename, ++testCount);    
    //  // What cards were removed from Deck?
    // for (i=0; i<preG_mod.deckCount[player]; i++) {
    //     for (j=0; j<G_mod.deckCount[player]; j++) {
    //         if (preG_mod.deck[player][i] == G_mod.deck[player][j] && preG_mod.deck[player][i] != -1) {
    //             preG_mod.deck[player][i] = -1;
    //             G_mod.deck[player][j] = -1;
    //             break;
    //         }
    //     }
    //     for (j=0; j<G_mod.discardCount[player]; j++) {
    //         if (preG_mod.deck[player][i] == G_mod.discard[player][j] && preG_mod.deck[player][i] != -1) {
    //             preG_mod.deck[player][i] = -1;
    //             G_mod.discard[player][j] = -1;
    //             break;
    //         }
    //     }
    // }
    // // What cards were removed from Discard?
    // for (i=0; i<preG_mod.discardCount[player]; i++) {
    //     for (j=0; j<G_mod.discardCount[player]; j++) {
    //         if (preG_mod.discard[player][i] == G_mod.discard[player][j] & preG_mod.discard[player][i] != -1) {
    //             preG_mod.discard[player][i] = -1;
    //             G_mod.discard[player][j] = -1;
    //             break;
    //         }
    //     }
    //     for (j=0; j<G_mod.deckCount[player]; j++) {
    //         if (preG_mod.discard[player][i] == G_mod.deck[player][j] & preG_mod.discard[player][i] != -1) {
    //             preG_mod.discard[player][i] = -1;
    //             G_mod.deck[player][j] = -1;
    //             break;
    //         }
    //     }
    // }
    // // // What cards were removed from Deck?
    // // for (i=0; i<preG_mod.deckCount[player]; i++) {
    // //     for (j=0; j<G_mod.deckCount[player]; j++) {
    // //         if (preG_mod.deck[player][i] == G_mod.deck[player][j] && preG_mod.deck[player][i] != -1) {
    // //             preG_mod.deck[player][i] = -1;
    // //             G_mod.deck[player][j] = -1;
    // //             break;
    // //         }
    // //     }
    // // }
    // // // What cards were removed from Discard?
    // // for (i=0; i<preG_mod.discardCount[player]; i++) {
    // //     for (j=0; j<G_mod.discardCount[player]; j++) {
    // //         if (preG_mod.discard[player][i] == G_mod.discard[player][j] & preG_mod.discard[player][i] != -1) {
    // //             preG_mod.discard[player][i] = -1;
    // //             G_mod.discard[player][j] = -1;
    // //             break;
    // //         }
    // //     }
    // // }
    // // Added cards are those uncrossed in preG_mod.deck and preG_mod.discard
    // count2 = 0;
    // for (i=0; i<preG_mod.deckCount[player]; i++) {
    //     if (preG_mod.deck[player][i] > 0) {
    //         count2++;
    //         if (NOISY_TEST) printf("Card removed from Deck #%d: %s\n", count1, getCardName(G_mod.deck[player][i]));
    //     }
    // }
    // for (i=0; i<preG_mod.discardCount[player]; i++) {
    //     if (preG_mod.discard[player][i] > 0) {
    //         count2++;
    //         if (NOISY_TEST) printf("Card removed from Discard #%d: %s\n", count1, getCardName(G_mod.discard[player][i]));
    //     }
    // }
    // asserttrue(count2==3, &r_main);


    // /*********/
    // printf("---------CASE %d: %s -- TEST %d: Cards added to Hand were the same as cards removed from Deck+Discard\n", caseCount, casename, ++testCount); 
    // // What cards added to Hand are not removed from Deck+Discard?
    // for (i=0; i<G_mod.handCount[player]; i++) {
    //     for (j=0; j<preG_mod.deckCount[player]; j++) {
    //         if (G_mod.hand[player][i] == preG_mod.deck[player][j] && G_mod.hand[player][i] != -1) {
    //             G_mod.hand[player][i] = -1;
    //             preG_mod.deck[player][j] = -1;
    //             count1--;
    //             count2--;
    //         }
    //     }
    //     for (j=0; j<preG_mod.discardCount[player]; j++) {
    //         if (G_mod.hand[player][i] == preG_mod.discard[player][j] && G_mod.hand[player][i] != -1) {
    //             G_mod.hand[player][i] = -1;
    //             preG_mod.discard[player][j] = -1;
    //             count1--;
    //             count2--;
    //         }
    //     }
    // }
    // // What cards added to Hand are not removed from Deck+Discard?
    // for (j=0; j<preG_mod.deckCount[player]; j++) {
    //     for (i=0; i<G_mod.handCount[player]; i++) {
    //          if (G_mod.hand[player][i] == preG_mod.deck[player][j] && G_mod.hand[player][i] != -1) {
    //             G_mod.hand[player][i] = -1;
    //             preG_mod.deck[player][j] = -1;
    //             count1--;
    //             count2--;
    //         }           
    //     }
    // }
    // for (j=0; j<preG_mod.discardCount[player]; j++) {
    //     for (i=0; i<G_mod.handCount[player]; i++) {
    //          if (G_mod.hand[player][i] == preG_mod.discard[player][j] && G_mod.hand[player][i] != -1) {
    //             G_mod.hand[player][i] = -1;
    //             preG_mod.discard[player][j] = -1;
    //             count1--;
    //             count2--;
    //         }           
    //     }
    // }
    // asserttrue(count1==0 && count2==0, &r_main);
    // if (NOISY_TEST) {
    //     if (count1>0) {
    //         printf("Cards added to Hand but not removed from Deck+Discard: ");
    //         for (i=0; i<G_mod.handCount[player]; i++) {
    //             if (G_mod.hand[player][i] > 0) printf("%s\t", getCardName(G_mod.hand[player][i]));
    //         }
    //     }
    //     if (count2>0) {
    //         printf("Cards removed from Deck+Discard but not added to Hand: ");
    //         for (j=0; j<G_mod.deckCount[player]; j++) {
    //             if (preG_mod.deck[player][j] > 0) printf("%s\t", getCardName(preG_mod.deck[player][j]));
    //         }
    //         for (j=0; j<G_mod.discardCount[player]; j++) {
    //             if (preG_mod.discard[player][j] > 0) printf("%s\t", getCardName(preG_mod.discard[player][j]));
    //         }
    //     }
    // }


    /*-------------------------------------------------------------------------*/
    casename = "2 cards in Deck, non-empty Discard";  // to test shuffle portion
    caseCount++;
    initializeGame(numPlayer, k, seed, &G);
    player = G.whoseTurn;
    G.hand[player][handPos] = smithy; // make current card smithy
    card = G.hand[player][handPos];  // card previously at handPos

    /* Construct Deck with 2 cards, Discard with 4 cards */
    G.deckCount[player] = 2;
    G.deck[player][0] = gold;
    G.deck[player][1] = silver;
    G.discardCount[player] = 4;
    G.discard[player][0] = adventurer;
    G.discard[player][1] = council_room;
    G.discard[player][2] = feast;
    G.discard[player][3] = gardens;

    memcpy(&preG, &G, sizeof(struct gameState));  // save gameState to preG

    /*********/
    testGeneralRequirements(caseCount, casename, &testCount, &r_main,
        card, choice1, choice2, choice3, handPos, &bonus,
        &G, &preG);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Hand count increased by 2\n", caseCount, casename, ++testCount);
    count1 = preG.handCount[player];
    count2 = G.handCount[player];
    asserttrue(count2==count1+2, &r_main);
    if (NOISY_TEST) printf("Hand count before: %d\nHand count after: %d\n", count1, count2);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Discard count + Deck count decreased by 3\n", caseCount, casename, ++testCount);
    count1 = preG.handCount[player];
    count2 = G.handCount[player];
    asserttrue(count2==count1+2, &r_main);
    if (NOISY_TEST) printf("Discard count + Deck count before: %d\nDiscard count + Deck count after: %d\n", count1, count2);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: 3 new cards added to Hand\n", caseCount, casename, ++testCount);
    assert(G.handCount[player] >= 3);  // hand should have 3+ cards
    memcpy(&G_mod, &G, sizeof(struct gameState));  // make a copy of G & preG that can be modified
    memcpy(&preG_mod, &preG, sizeof(struct gameState));
    // What cards were added to Hand?
    for (i=0; i<G_mod.handCount[player]; i++) {
        if (G_mod.hand[player][i] == smithy) {
            G_mod.hand[player][i] = -1;  // cross out Smithy as it'd be moved to played
        }
        for (j=0; j<preG_mod.handCount[player]; j++) {
            if (G_mod.hand[player][i] == preG_mod.hand[player][j] && G_mod.hand[player][i] != -1) {
                G_mod.hand[player][i] = -1;  // cross out cards that appear in both G_mod.hand and preG_mod.hand
                preG_mod.hand[player][j] = -1;
                break;
            }
        }
    }
    // Added cards are those uncrossed in G_mod.hand
    count1 = 0;
    for (i=0; i<G_mod.handCount[player]; i++) {
        if (G_mod.hand[player][i] > 0) {
            count1++;  // how many new cards in Hand?
            if (NOISY_TEST) printf("Card added to Hand #%d: %s\n", count1, getCardName(G_mod.hand[player][i]));
        }
    }
    asserttrue(count1==3, &r_main);


    /*********/
    printf("---------CASE %d: %s -- TEST %d: 3 cards removed from Deck+Discard\n", caseCount, casename, ++testCount);    
    // What cards were removed from Deck?
    for (i=0; i<preG_mod.deckCount[player]; i++) {
        for (j=0; j<G_mod.deckCount[player]; j++) {
            if (preG_mod.deck[player][i] == G_mod.deck[player][j] && preG_mod.deck[player][i] != -1) {
                preG_mod.deck[player][i] = -1;
                G_mod.deck[player][j] = -1;
                break;
            }
        }
    }
    for (i=0; i<preG_mod.deckCount[player]; i++) {
        for (j=0; j<G_mod.discardCount[player]; j++) {
            if (preG_mod.deck[player][i] == G_mod.discard[player][j] && preG_mod.deck[player][i] != -1) {
                preG_mod.deck[player][i] = -1;
                G_mod.discard[player][j] = -1;
                break;
            }
        }
    }
    // What cards were removed from Discard?
    for (i=0; i<preG_mod.discardCount[player]; i++) {
        for (j=0; j<G_mod.discardCount[player]; j++) {
            if (preG_mod.discard[player][i] == G_mod.discard[player][j] & preG_mod.discard[player][i] != -1) {
                preG_mod.discard[player][i] = -1;
                G_mod.discard[player][j] = -1;
                break;
            }
        }
    }
    for (i=0; i<preG_mod.discardCount[player]; i++) {
        for (j=0; j<G_mod.discardCount[player]; j++) {
            if (preG_mod.discard[player][i] == G_mod.discard[player][j] & preG_mod.discard[player][i] != -1) {
                preG_mod.discard[player][i] = -1;
                G_mod.discard[player][j] = -1;
                break;
            }
        }
    }

    printCurrentPlayer(player, &G_mod);
    printCurrentPlayer(player, &preG_mod);
    // // preG_mod.deck:
    // printf("\npreG_mod.deck:\n");
    // int card_temp;
    // char* card_str_temp;
    // for (i=0; i<preG_mod.deckCount[player]; i++){
    //     card_temp = preG_mod.deck[player][i];
    //     if (card_temp == -1) card_str_temp = "-1"; else card_str_temp = getCardName(card_temp);
    //     printf("%s\t", card_str_temp);
    // }
    // // preG_mod.discard:
    // printf("\npreG_mod.discard:\n");
    // for (i=0; i<preG_mod.discardCount[player]; i++){
    //     card_temp = preG_mod.discard[player][i];
    //     if (card_temp == -1) card_str_temp = "-1"; else card_str_temp = getCardName(card_temp);
    //     printf("%s\t", card_str_temp);
    // }

    // // Added cards are those uncrossed in preG_mod.deck and preG_mod.discard
    // count2 = 0;
    // for (i=0; i<preG_mod.deckCount[player]; i++) {
    //     if (preG_mod.deck[player][i] != -1) {
    //         count2++;
    //         if (NOISY_TEST) printf("Card removed from Deck #%d: %s\n", count1, getCardName(G_mod.deck[player][i]));
    //     }
    // }
    // for (i=0; i<preG_mod.discardCount[player]; i++) {
    //     if (preG_mod.discard[player][i] != -1) {
    //         count2++;
    //         if (NOISY_TEST) printf("Card removed from Discard #%d: %s\n", count1, getCardName(G_mod.discard[player][i]));
    //     }
    // }
    asserttrue(count2==3, &r_main);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Cards added to Hand were the same as cards removed from Deck+Discard\n", caseCount, casename, ++testCount); 
    // What cards added to Hand are not removed from Deck+Discard?
    for (i=0; i<G_mod.handCount[player]; i++) {
        for (j=0; j<preG_mod.deckCount[player]; j++) {
            if (G_mod.hand[player][i] == preG_mod.deck[player][j] && G_mod.hand[player][i] != -1) {
                G_mod.hand[player][i] = -1;
                preG_mod.deck[player][j] = -1;
                count1--;
                count2--;
            }
        }
        for (j=0; j<preG_mod.discardCount[player]; j++) {
            if (G_mod.hand[player][i] == preG_mod.discard[player][j] && G_mod.hand[player][i] != -1) {
                G_mod.hand[player][i] = -1;
                preG_mod.discard[player][j] = -1;
                count1--;
                count2--;
            }
        }
    }
    // What cards added to Hand are not removed from Deck+Discard?
    for (j=0; j<preG_mod.deckCount[player]; j++) {
        for (i=0; i<G_mod.handCount[player]; i++) {
             if (G_mod.hand[player][i] == preG_mod.deck[player][j] && G_mod.hand[player][i] != -1) {
                G_mod.hand[player][i] = -1;
                preG_mod.deck[player][j] = -1;
                count1--;
                count2--;
            }           
        }
    }
    for (j=0; j<preG_mod.discardCount[player]; j++) {
        for (i=0; i<G_mod.handCount[player]; i++) {
             if (G_mod.hand[player][i] == preG_mod.discard[player][j] && G_mod.hand[player][i] != -1) {
                G_mod.hand[player][i] = -1;
                preG_mod.discard[player][j] = -1;
                count1--;
                count2--;
            }           
        }
    }
    asserttrue(count1==0 && count2==0, &r_main);
    if (NOISY_TEST) {
        if (count1>0) {
            printf("Cards added to Hand but not removed from Deck+Discard: ");
            for (i=0; i<G_mod.handCount[player]; i++) {
                if (G_mod.hand[player][i] > 0) printf("%s\t", getCardName(G_mod.hand[player][i]));
            }
            printf("\n");
        }
        if (count2>0) {
            printf("Cards removed from Deck+Discard but not added to Hand: ");
            for (j=0; j<G_mod.deckCount[player]; j++) {
                if (preG_mod.deck[player][j] > 0) printf("%s\t", getCardName(preG_mod.deck[player][j]));
            }
            for (j=0; j<G_mod.discardCount[player]; j++) {
                if (preG_mod.discard[player][j] > 0) printf("%s\t", getCardName(preG_mod.discard[player][j]));
            }
            printf("\n");
        }
    }


    /*-------------------------------------------------------------------------*/
    /******** Result */
    printf("---------\n");
    printf("Card %s passed %d/%d checks.\n", CARD_NAME, r_main, testCount);
    printf("END testing %s\n", CARD_NAME);
    printf("**********************************************************\n");
}

