/*******************************************************************************
* Unit tests for fullDeckCount:
*
* The fullDeckCount card should:
*   count the number of instances of a given card in a player's deck
*   count the number of instances of a given card in a player's hand
*   count the number of instances of a given card in a player's discard pile
*   return the total count of the given card b/w deck, hand and discard pile
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
    int numPlayer = 2;      // Test outputs for multiple players
    int pileCounts[] = {0, 5}; // Test multiple total pile counts
    int countsSize = 2;     // 2^3 total test runs (per player), given deck, hand, discard
    struct gameState G;     // Need to pass a gameState struct to fullDeckCount

    SEPARATE;
    printf("TESTING fullDeckCount:\n");
    for (int p = 0; p < numPlayer; p++){
        for (int deckIdx = 0; deckIdx < countsSize; deckIdx++){
            int deckCount = pileCounts[deckIdx];
            int num_in_deck = deckCount / 2;
            for (int handIdx = 0; handIdx < countsSize; handIdx++){
                int handCount = pileCounts[handIdx];
                int num_in_hand = handCount / 2;
                for (int discIdx = 0; discIdx < countsSize; discIdx++){
                    int discCount = pileCounts[discIdx];
                    int num_in_disc = discCount / 2;
#if (NOISY_TEST == 1)
                    printf("Test player %d with %d card of interest in deck, %d in hand, %d in discard\n", p, deckIdx, handIdx, discIdx);
#endif
                    memset(&G, 23, sizeof(struct gameState));   // clear state
                    G.deckCount[p] = deckCount;                 // set counts
                    G.handCount[p] = handCount;
                    G.discardCount[p] = discCount;
                    int card = copper;      // arbitrary card of interest
                    // Create deck, hand and discard with appropriate number of
                    // card of interest
                    consecutiveDeckSelect(G.deck[p], G.deckCount[p], card, num_in_deck);
                    consecutiveDeckSelect(G.hand[p], G.handCount[p], card, num_in_hand);
                    consecutiveDeckSelect(G.discard[p], G.discardCount[p], card, num_in_disc);

                    int expected = num_in_deck + num_in_hand + num_in_disc;
                    int count = fullDeckCount(p, card, &G);
#if (NOISY_TEST == 1)
                    printf("Expected count = %d, actual = %d...", expected, count);
#endif
                    assertTrue(expected == count);
                }
            }
        }
    }
    SPACE;
    return 0;
}
