/*******************************************************************************
* Unit tests for isGameOver:
*   isGaveOver(struct gameState *state)
*
* The isGameOver function should:
*   return "true" (1) if the supply of province cards is 0
*   return "true" (1) if any 3 of the supply piles are 0
*   reeturn "false" (0) otherwise
*******************************************************************************/

#include "dominion.h"
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
    int seed = 1000;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};
    struct gameState G;

    SEPARATE;
    printf("TESTING isGameOver:\n");

    // --- Test 1: Supply of provinces is 0 ---
#if (NOISY_TEST == 1)
    printf("Test with 0 provinces left in supply (should be game over)");
#endif
    memset(&G, 23, sizeof(struct gameState));   // clear game state
    initializeGame(numPlayer, k, seed, &G);     // init game
    G.supplyCount[province] = 0;                // set province to 0
    assertTrue(isGameOver(&G) == 1);

    // --- Test 2: Supply of provinces NOT 0, 3 supply piles are empty
#if (NOISY_TEST == 1)
    printf("Test with 12 provinces, 3 empty supply piles (should be game over)");
#endif
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayer, k, seed, &G);
    G.supplyCount[province] = 12;
    G.supplyCount[curse] = 0;
    G.supplyCount[estate] = 0;
    G.supplyCount[duchy] = 0;
    assertTrue(isGameOver(&G) == 1);

    // --- Test 3: Supply of provinces NOT 0, 5 supply piles are empty
#if (NOISY_TEST == 1)
    printf("Test with 12 provinces, 5 empty supply piles (should be game over)");
#endif
    memset(&G, 23, sizeof(struct gameState));   // clear game state
    initializeGame(numPlayer, k, seed, &G);
    G.supplyCount[province] = 12;
    G.supplyCount[curse] = 0;
    G.supplyCount[estate] = 0;
    G.supplyCount[duchy] = 0;
    G.supplyCount[copper] = 0;
    G.supplyCount[silver] = 0;
    assertTrue(isGameOver(&G) == 1);

    // --- Test 4: Supply of pronvinces NOT 0, 0 supply piles are empty
#if (NOISY_TEST == 1)
    printf("Test with 12 provinces, 0 empty supply piles (should NOT be game over)");
#endif
    memset(&G, 23, sizeof(struct gameState));   // clear game state
    initializeGame(numPlayer, k, seed, &G);
    assertTrue(isGameOver(&G) == 0);

    SPACE;
    return 0;
}
