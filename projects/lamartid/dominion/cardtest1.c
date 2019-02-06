/*******************************************************************************
* Unit tests for Smithy (implemented in smithy_play, called via cardEffect)
*   void smithy_play(int currentPlayer, struct gameState *state, int handPos,
*   int *bonus);
*
* Smithy should:
*   Allow the player to draw 3 cards
*   Discard the smithy card itself
*
* Consider...
*   Were 3 cards drawn (not less, nore more)?
*       handCount should increase by 3
*       deckCount should decrease by 3
*   Was the smithy card discarded (removed from hand)?
*   Was the discarded smithy card sent to the discard pile? (not trash)
*       ---bug introduced in Assignment 2 to take it to trash
*   Did state changes NOT occur for other players?
*   Did state changes NOT occur to victory card and kingdom card piles?
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

#define TESTCARD "Smithy"

// Set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1
#define SEPARATE separate('*', 80)
#define SPACE printf("\n")

int main(int argc, char *argv[]){
    int newCards = 3;
    int discarded = 1;
    int shuffledCards = 1;

    int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    int otherPlayer = 1;
    int k[10] = {adventurer, embargo, village, minion, mine,
                 cutpurse, sea_hag, tribute, smithy, council_room};
    struct gameState G, testG;

    // Initialize game state
    initializeGame(numPlayers, k, seed, &G);

    SEPARATE;
    printf("--------------------Testing Card: %s --------------------\n", TESTCARD);
    // No choices for Smithy - 1 "total" test with multiple assertions
    printf("TEST 1: no choices for Smithy\n");

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    cardEffect(smithy, choice1, choice2, choice3, &testG, handPos, &bonus);

    printf("Testing state changes for active player...\n");
    printf("Hand count = %d, expected = %d", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
    assertTrue(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);
    printf("Deck count = %d, expected = %d", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
    assertTrue(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards);
    printf("Discard count = %d, expected = %d", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + discarded);
    assertTrue(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer] + discarded);

    printf("Testing state changes for other player...\n");
    printf("Hand count = %d, expected = %d", testG.handCount[otherPlayer], G.handCount[otherPlayer]);
    assertTrue(testG.handCount[otherPlayer] == G.handCount[otherPlayer]);
    printf("Deck count = %d, expected = %d", testG.deckCount[otherPlayer], G.deckCount[otherPlayer]);
    assertTrue(testG.deckCount[otherPlayer] == G.deckCount[otherPlayer]);
    printf("Discard count = %d, expected = %d", testG.discardCount[otherPlayer], G.discardCount[otherPlayer]);
    assertTrue(testG.discardCount[otherPlayer] == G.discardCount[otherPlayer]);

    SPACE;
    return 0;
}
