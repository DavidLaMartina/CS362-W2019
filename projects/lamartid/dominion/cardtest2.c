/*******************************************************************************
* Unit tests for Adventurer (implented in adventurer_play, called via cardEffect)
*
* Adventurer should:
*   Allow player to draw cards from deck until revealing two treasure
*   Require the player to discard non-tresaure cards drawn
*
* Consider...
*   Did the player's handCount increase by 2 (not more, not less)
*   Did the number of treasure cards in the player's hand increase by 2?
*   Was the number of cards drawn, minus 2 treasure, added to the discard pile?
*   Did state changes NOT occur for other players?
*   Did state changes occur for kingdom or victory cards?
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

#define TESTCARD "Adventurer"

// Set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1
#define SEPARATE separate('*', 80)
#define SPACE printf("\n")

int main(int argc, char *argv[]){
    int discarded = 1;
    int shuffledCards = 0;
    int num_treasure_actual, num_treasure_expected;
    int extraActions = 0;
    int extraBuys = 0;
    int cardsPlayed = 1;

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
     // Manually set top of deck so we know how many cards will need to be drawn
     int deck_counter = G.deckCount[thisPlayer];        // Keep track of top of deck
     int draw_total = 4;                                // total cards drawn (arbitrary)
     int drawnTreasure = 2;                             // requirement of adventurer
     discarded += (draw_total - drawnTreasure);         // update discard total
     G.deck[thisPlayer][deck_counter - 1] = remodel;
     G.deck[thisPlayer][deck_counter - 2] = remodel;
     G.deck[thisPlayer][deck_counter - 3] = copper;
     G.deck[thisPlayer][deck_counter - 4] = copper;

     SEPARATE;
     printf("--------------------Testing Card: %s --------------------\n", TESTCARD);
     // No choices for Smithy - 1 "total" test with multiple assertions
     printf("TEST: No choices for Adventurer\n");

     // copy game state to test case
     memcpy(&testG, &G, sizeof(struct gameState));
     cardEffect(adventurer, choice1, choice2, choice3, &testG, handPos, &bonus);

     printf("Testing state changes for active player...\n");
     printf("Hand count = %d, expected = %d", testG.handCount[thisPlayer], G.handCount[thisPlayer] + draw_total - discarded);
     assertTrue(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + draw_total - discarded);
     printf("Deck count = %d, expected = %d", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - draw_total + shuffledCards);
     assertTrue(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - draw_total);
     printf("Discard count = %d, expected = %d", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + discarded);
     assertTrue(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer] + discarded);
     num_treasure_actual = countTreasure(testG.hand[thisPlayer], testG.handCount[thisPlayer]);
     num_treasure_expected = countTreasure(G.hand[thisPlayer], G.handCount[thisPlayer]) + drawnTreasure;
     printf("Treasure cards in hand = %d, expected = %d", num_treasure_actual, num_treasure_expected);
     assertTrue(num_treasure_actual == num_treasure_expected);
     num_treasure_actual = countTreasure(testG.deck[thisPlayer], testG.deckCount[thisPlayer]);
     num_treasure_expected = countTreasure(G.deck[thisPlayer], G.deckCount[thisPlayer]) - drawnTreasure;
     printf("Treasure cards in deck = %d, expected = %d", num_treasure_expected, num_treasure_expected);
     assertTrue(num_treasure_actual == num_treasure_expected);


     printf("Testing state changes for other player...\n");
     printf("Hand count = %d, expected = %d", testG.handCount[otherPlayer], G.handCount[otherPlayer]);
     assertTrue(testG.handCount[otherPlayer] == G.handCount[otherPlayer]);
     printf("Deck count = %d, expected = %d", testG.deckCount[otherPlayer], G.deckCount[otherPlayer]);
     assertTrue(testG.deckCount[otherPlayer] == G.deckCount[otherPlayer]);
     printf("Discard count = %d, expected = %d", testG.discardCount[otherPlayer], G.discardCount[otherPlayer]);
     assertTrue(testG.discardCount[otherPlayer] == G.discardCount[otherPlayer]);
     num_treasure_actual = countTreasure(testG.hand[otherPlayer], testG.handCount[otherPlayer]);
     num_treasure_expected = countTreasure(G.hand[otherPlayer], G.handCount[otherPlayer]);
     printf("Treasure cards in hand = %d, expected = %d", num_treasure_actual, num_treasure_expected);
     assertTrue(num_treasure_actual == num_treasure_expected);
     num_treasure_actual = countTreasure(testG.deck[otherPlayer], testG.deckCount[otherPlayer]);
     num_treasure_expected = countTreasure(G.deck[otherPlayer], G.deckCount[otherPlayer]);
     printf("Treasure cards in deck = %d, expected = %d", num_treasure_expected, num_treasure_expected);
     assertTrue(num_treasure_actual == num_treasure_expected);

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
