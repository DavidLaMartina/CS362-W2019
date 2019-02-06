/*******************************************************************************
* Unit tests for updateCoins:
*   updateCoins(int player, struct gameState *state, int bonus)
*
* The updateCoins function should:
*   reset the coin count before updating based on hand
*   Add 1 coin to total per copper, 2 per silver, 3 per gold
*   Add whatever bonus is passed in to the function to the count
*   Update the game state's coins value
*******************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "test_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>

// Set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1
#define SEPARATE separate('*', 80)
#define SPACE printf("\n")

int main(int argc, char *argv[]){
    int numPlayer = 2;
    int player = 0;     // Just test for one player
    int seed = 1000;
    int bonus;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};
    struct gameState G;

    SEPARATE;
    printf("TESTING updateCoins:\n");

    // --- Test 1: 0 copper, silver or gold, 0 bonus ---
#if (NOISY_TEST == 1)
    printf("0 copper, silver, gold, or bonus - expected total 0");
#endif
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayer, k, seed, &G);
    G.handCount[player] = 5;        // 5 total cards
    G.hand[player][0] = estate;
    G.hand[player][1] = adventurer;
    G.hand[player][2] = gardens;
    G.hand[player][3] = remodel;
    G.hand[player][4] = smithy;
    bonus = 0;
    updateCoins(player, &G, bonus);
    assertTrue(G.coins == 0);

    // --- Test 2: 2 copper, 2 silver, 1 gold, 0 bonus ---
#if (NOISY_TEST == 1)
    printf("2 copper, 2 silver, 1 gold, 0 bonus - expected total 9");
#endif
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayer, k, seed, &G);
    G.handCount[player] = 5;        // 5 total cards
    G.hand[player][0] = copper;
    G.hand[player][1] = silver;
    G.hand[player][2] = copper;
    G.hand[player][3] = silver;
    G.hand[player][4] = gold;
    bonus = 0;
    updateCoins(player, &G, bonus);
    assertTrue(G.coins == 9);

    // --- Test 3: 2 copper, 2 silver, 1 gold, 7 bonus ---
#if (NOISY_TEST == 1)
    printf("2 copper, 2 silver, 1 gold, 7 bonus - expected total 16");
#endif
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayer, k, seed, &G);
    G.handCount[player] = 5;        // 5 total cards
    G.hand[player][0] = copper;
    G.hand[player][1] = silver;
    G.hand[player][2] = copper;
    G.hand[player][3] = silver;
    G.hand[player][4] = gold;
    bonus = 7;
    updateCoins(player, &G, bonus);
    assertTrue(G.coins == 16);

    // ---Test 4: 5 copper, 0 silver, 0 gold, 0 bonus ---
#if (NOISY_TEST == 1)
    printf("All 5 copper - expected total 5");
#endif
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayer, k, seed, &G);
    G.handCount[player] = 5;        // 5 total cards
    for (int i = 0; i < G.handCount[player]; i++){
        G.hand[player][i] = copper;
    }
    bonus = 0;
    updateCoins(player, &G, bonus);
    assertTrue(G.coins == 5);

    // ---Test 5: 0 copper, 5 silver, 0 gold, 0 bonus ---
#if (NOISY_TEST == 1)
    printf("All 5 silver - expected total 10");
#endif
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayer, k, seed, &G);
    G.handCount[player] = 5;        // 5 total cards
    for (int i = 0; i < G.handCount[player]; i++){
        G.hand[player][i] = silver;
    }
    bonus = 0;
    updateCoins(player, &G, bonus);
    assertTrue(G.coins == 10);

    // ---Test 6: All gold, 0 bonus ---
#if (NOISY_TEST == 1)
    printf("All 5 silver - expected total 15");
#endif
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayer, k, seed, &G);
    G.handCount[player] = 5;        // 5 total cards
    for (int i = 0; i < G.handCount[player]; i++){
        G.hand[player][i] = gold;
    }
    bonus = 0;
    updateCoins(player, &G, bonus);
    assertTrue(G.coins == 15);

    SPACE;
    return 0;
}
