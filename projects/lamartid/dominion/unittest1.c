/*******************************************************************************
* Unit tests for shuffle:
*   int shuffle(int player, struct gameState *state);
*
* The shuffle function should:
*   Return -1 if the player's deck count is less than 1 (no cards in hand)
*       else sort cards in deck array to ensure determinism in shuffle
*   Randomly assign cards in deck array to newDeck array
*   Assign all elements of deck array to corresponding elements of newDeck
*
* Verify that:
*   deck count is the same before and after shuffle
*   The deck contains the exact same set of cards before and after the shuffle
*   The shuffle truly changed the order of the deck
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

int main(){
    srand(time(0));     // Seed random number generator required for random card
    int numPlayer = 2;  // Test outputs for multiple players, not just 1
    int deckCounts[] = {0, 1, 2, 52}; // deck counts to test
    int countsSize = 4;
    int shuffleThreshold = 52; // >= threshold, check reordering
    struct gameState G; // Need to pass a gameState struct to shuffle()

    /*  Manually set deck count and randomize deck
        Call shuffle
        Check deck count and values now contained in deck
        For large enough values, check that re-ordering occured */

    SEPARATE;
    printf("TESTING shuffle:\n");
    //printf("Deck counts 0, 1, 2\n");
    for (int p = 0; p < numPlayer; p++){
        for (int countIdx = 0; countIdx < countsSize; countIdx++){
            int deckCount = deckCounts[countIdx];
#if (NOISY_TEST == 1)
            printf("Test player %d with %d card(s) in deck.\n", p, deckCount);
#endif
            memset(&G, 23, sizeof(struct gameState));   // clear game state
            G.deckCount[p] = deckCount;                 // set deckCount
            randomDeck(G.deck[p], deckCount);           // randomize deck
            int oldDeck[deckCount];                     // "old" deck to compare
            copyArray(G.deck[p], deckCount, oldDeck, deckCount);
            shuffle(p, &G);
#if (NOISY_TEST == 1)
            printf("deckCount = %d, expected = %d", G.deckCount[p], deckCount);
#endif
            assertTrue(deckCount == G.deckCount[p]);
#if (NOISY_TEST == 1)
            printf("Checking equivalent deck values...");
#endif
            assertTrue(sameVals(oldDeck, deckCount, G.deck[p], G.deckCount[p]));
            /* Check shuffle */
            if (deckCount >= shuffleThreshold){
#if (NOISY_TEST == 1)
            printf("Verifying that re-ordering occured...");
#endif
            assertTrue(diffOrder(oldDeck, deckCount, G.deck[p], G.deckCount[p]));
            printArray(oldDeck, deckCount);
            printArray(G.deck[p], G.deckCount[p]);
            }
        }
    }
}
