/*******************************************************************************
* Random tester for Adventurer
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
*
* Randomize...
*   currentPlayer
*   deck & deckCount
*   hand & handCount
*   handPos
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
#define SEPARATE separate('*', 80)
#define SPACE printf("\n")

#define NUM_TESTS 500
#define MIN_TREASURE 2
#define MAX_TREASURE 10
#define MIN_DECK_COUNT 10
#define MAX_DECK_COUNT 50
#define MIN_HAND_COUNT 5
#define MAX_HAND_COUNT 10

int main(int argc, char *argv[]){
  srand(time(0));             // seed random generator

  int seed = 1000;            // Seed for game initalization
  int numPlayers = 2;         // Test one player or the other
  int k[10] = {adventurer, embargo, village, minion, mine,
               cutpurse, sea_hag, tribute, smithy, council_room};




  for (int i = 0; i < NUM_TESTS; i++){
    // Establish dependencies
    int currentPlayer;
    int handPos;
    struct gameState G, testG;  // Before and after game states

    // Non-dependent parameters
    int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int drawnTreasure = 0;
    int z = 0;
    int temphand[MAX_HAND];
    int treasure_needed = 2;  // What adventurer requires of deck
    int extraBuys = 0;
    int extraActions = 0;
    int cardsPlayed = 1;

    // Variables to track for assertions
    int otherPlayer;
    int treasureInDeck;
    int adventurer_position;
    int discarded = 1;      // At least the 1 Adventurer card will be discarded
    int shuffledCards = 0;  // No shuffle required; at least 2 treasures in deck
    int draw_total;         // Number of cards must be drawn to get 2 treasure
    int num_treasure_actual, num_treasure_expected;

    // Specific test success / failure counters



    // Start new game for every test
    initializeGame(numPlayers, k, seed, &G);

    // Randomize currentPlayer
    currentPlayer = randomRange(0, numPlayers - 1);
    if (currentPlayer == 0){
      otherPlayer = 1;
    }else{
      otherPlayer = 0;
    }
    // Randomize number of treasure
    treasureInDeck = randomRange(MIN_TREASURE, MAX_TREASURE);
    // Randomize deck count
    G.deckCount[currentPlayer] = randomRange(MIN_DECK_COUNT, MAX_DECK_COUNT);
    // Randomize a deck with given number of treasure
    randomTreasureDeck(G.deck[currentPlayer], G.deckCount[currentPlayer],
                       treasureInDeck);
    // Determine number of total cards to be drawn to reach 2 treasure
    draw_total = cardsToTreasure(G.deck[currentPlayer], G.deckCount[currentPlayer], treasure_needed);
    // Determine number of total cards that should be discarded (Adventurer + non-treasure cards drawn)
    discarded += (draw_total - treasure_needed);
    // Randomize hand count
    G.handCount[currentPlayer] = randomRange(MIN_HAND_COUNT, MAX_HAND_COUNT);
    // Randomize hand
    randomCards(G.hand[currentPlayer], G.handCount[currentPlayer]);
    // Randomize hand position of Adventurer card (and place it there)
    adventurer_position = randomRange(0, G.handCount[currentPlayer] - 1);
    G.hand[currentPlayer][adventurer_position] = adventurer;

    // Save game state before testing
    memcpy(&testG, &G, sizeof(struct gameState));

    // Execute adventurer via cardEffect
    cardEffect(adventurer, choice1, choice2, choice3, &testG, adventurer_position, &bonus);
    //adventurer_play(currentPlayer, drawnTreasure, z, temphand, &testG, adventurer_position, &bonus);

    printf("draw_total: %d, discarded: %d\n", draw_total, discarded);

    printf("Testing state changes for active player...\n");
     printf("Hand count = %d, expected = %d", testG.handCount[currentPlayer], G.handCount[currentPlayer] + draw_total - discarded);
     assertTrue(testG.handCount[currentPlayer] == G.handCount[currentPlayer] + draw_total - discarded);
     printf("Deck count = %d, expected = %d", testG.deckCount[currentPlayer], G.deckCount[currentPlayer] - draw_total + shuffledCards);
     assertTrue(testG.deckCount[currentPlayer] == G.deckCount[currentPlayer] - draw_total);
     printf("Discard count = %d, expected = %d", testG.discardCount[currentPlayer], G.discardCount[currentPlayer] + discarded);
     assertTrue(testG.discardCount[currentPlayer] == G.discardCount[currentPlayer] + discarded);
     num_treasure_actual = countTreasure(testG.hand[currentPlayer], testG.handCount[currentPlayer]);
     num_treasure_expected = countTreasure(G.hand[currentPlayer], G.handCount[currentPlayer]) + drawnTreasure;
     printf("Treasure cards in hand = %d, expected = %d", num_treasure_actual, num_treasure_expected);
     assertTrue(num_treasure_actual == num_treasure_expected);
     num_treasure_actual = countTreasure(testG.deck[currentPlayer], testG.deckCount[currentPlayer]);
     num_treasure_expected = countTreasure(G.deck[currentPlayer], G.deckCount[currentPlayer]) - drawnTreasure;
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
     for (int i = 0; i < num_cards; i++){
         if (testG.supplyCount[i] != G.supplyCount[i]){
             same_supply = false;
         }
     }
     printf("All counts identical");
     assertTrue(same_supply);
     printf("Testing changes on embargo tokens...\n");
     bool same_tokens = true;
     for (int i = 0; i < num_cards; i++){
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
  }
  return 0;
}
