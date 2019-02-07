/*******************************************************************************
* Unit tests for Village
*   part of cardEffect
*
* Village should:
*   allow player to draw 1 card
*   give player 2 more actions
*   discard Village card after play
*
* Consider:
*   Was exactly 1 card drawn?
*   Were 2 actions added?
*   Was the game state left unchanged for the other player?
*   Was the Village card discarded (and added to discard pile)?
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

#define TESTCARD "Village"

// Set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1
#define SEPARATE separate('*', 80)
#define SPACE printf("\n")

int main(int argc, char *argv[]){
    int newCards = 1;
    int discarded = 1;
    int shuffledCards = 0;
    int extraActions = 2;
    int extraBuys = 0;
    int cardsPlayed = 0;
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
    printf("TEST: No choices for Village\n");

    // Copy game state to test case
    memcpy(&testG, &G, sizeof(struct gameState));
    cardEffect(village, choice1, choice2, choice3, &testG, handPos, &bonus);

    printf("Testing state changes for active player...\n");
    printf("Hand count = %d, expected = %d", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
    assertTrue(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);
    printf("Deck count = %d, expected = %d", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
    assertTrue(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards);
    printf("Discard count = %d, expected = %d", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + discarded);
    assertTrue(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer] + discarded);
    //printf("Remaining actions = %d, expected = %d", testG.numActions, G.numActions + extraActions);
    //assertTrue(testG.numActions == G.numActions + extraActions);

    printf("Testing state changes for other player...\n");
    printf("Hand count = %d, expected = %d", testG.handCount[otherPlayer], G.handCount[otherPlayer]);
    assertTrue(testG.handCount[otherPlayer] == G.handCount[otherPlayer]);
    printf("Deck count = %d, expected = %d", testG.deckCount[otherPlayer], G.deckCount[otherPlayer]);
    assertTrue(testG.deckCount[otherPlayer] == G.deckCount[otherPlayer]);
    printf("Discard count = %d, expected = %d", testG.discardCount[otherPlayer], G.discardCount[otherPlayer]);
    assertTrue(testG.discardCount[otherPlayer] == G.discardCount[otherPlayer]);

    printf("Testing overall game state changes...\n");
    printf("Number of buys remaining = %d, expected = %d", testG.numBuys, G.numBuys + extraBuys);
    assertTrue(testG.numBuys == G.numBuys + extraBuys);
    printf("Testing state changes on victory card and kingdom card piles...\n");
    printf("Each card's supply must have remained the same in order to pass.\n");
    bool same_supply = true;
    for (int i = 0; i < cards_count; i++){
        if (testG.supplyCount[i] != G.supplyCount[i]){
            same_supply = false;
        }
    }
    printf("All counts identical");
    assertTrue(same_supply);
    printf("Testing changes on embargo tokens...\n");
    bool same_tokens = true;
    for (int i = 0; i < cards_count; i++){
        if (testG.embargoTokens[i] != G.embargoTokens[i]){
            same_supply = false;
        }
    }
    printf("All tokens identical");
    assertTrue(same_tokens);
    printf("Outpost played = %d, expected = %d", testG.outpostPlayed, G.outpostPlayed);
    assertTrue(testG.outpostPlayed == G.outpostPlayed);
    printf("Outpost turn = %d, expected = %d", testG.outpostTurn, G.outpostTurn);
    assertTrue(testG.outpostTurn == G.outpostTurn);
    printf("Whose turn = %d, expected = %d", testG.whoseTurn, G.whoseTurn);
    assertTrue(testG.whoseTurn == G.whoseTurn);
    printf("Phase = %d, expected = %d", testG.phase, G.phase);
    assertTrue(testG.phase == G.phase);
    printf("Number of actions = %d, expected = %d", testG.numActions, G.numActions + extraActions);
    assertTrue(testG.numActions == G.numActions + extraActions);
    printf("Played cards count = %d, expected = %d", testG.playedCardCount, G.playedCardCount + cardsPlayed);
    assertTrue(testG.playedCardCount == G.playedCardCount + cardsPlayed);

    SPACE;
    return 0;
}
