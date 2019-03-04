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

#define NUM_TESTS 100
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

  // Specific test success / failure counters
  int hand_count_current_errors = 0; struct ValPair hand_count_current[NUM_TESTS];
  int deck_count_current_errors = 0; struct ValPair deck_count_current[NUM_TESTS];
  int discard_count_current_errors = 0; struct ValPair discard_count_current[NUM_TESTS];
  int treasure_in_hand_current_errors = 0; struct ValPair treasure_in_hand_current[NUM_TESTS];
  int treasure_in_deck_current_errors = 0; struct ValPair treasure_in_deck_current[NUM_TESTS];
  int hand_count_other_errors = 0; struct ValPair hand_count_other[NUM_TESTS];
  int deck_count_other_errors = 0; struct ValPair deck_count_other[NUM_TESTS];
  int discard_count_other_errors = 0; struct ValPair discard_count_other[NUM_TESTS];
  int treasure_in_hand_other_errors = 0; struct ValPair treasure_in_hand_other[NUM_TESTS];
  int treasure_in_deck_other_errors = 0; struct ValPair treasure_in_deck_other[NUM_TESTS];
  int num_buys_diff_errors = 0; struct ValPair num_buys_diff[NUM_TESTS];
  int same_supply_errors = 0;
  int same_tokens_errors = 0;
  int outpost_play_errors = 0; struct ValPair outpost_play_diff[NUM_TESTS];
  int outpost_turn_errors = 0; struct ValPair outpost_turn_diff[NUM_TESTS];
  int whose_turn_errors = 0; struct ValPair whose_turn_diff[NUM_TESTS];
  int phase_errors = 0; struct ValPair phase_diff[NUM_TESTS];
  int num_action_errors = 0; struct ValPair num_action_diff[NUM_TESTS];
  int played_card_errors = 0; struct ValPair played_card_diff[NUM_TESTS];

  for (int i = 0; i < NUM_TESTS; i++){
    // Establish dependencies
    int currentPlayer;
    struct gameState G, testG;  // Before and after game states

    // Non-dependent parameters
    int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int drawnTreasure = 0;
    int treasure_needed = 2;  // What adventurer requires of deck
    int extraBuys = 0;
    int extraActions = 0;
    int cardsPlayed = 1;

    // Variables to track for assertions
    int otherPlayer;
    int treasureInDeck;
    int adventurer_position;
    int discarded = 1;      // At least the 1 Adventurer card will be discarded
    //int shuffledCards = 0;  // No shuffle required; at least 2 treasures in deck
    int draw_total;         // Number of cards must be drawn to get 2 treasure
    int num_treasure_actual, num_treasure_expected;

    // Start new game for every test
    initializeGame(numPlayers, k, seed, &G);

    currentPlayer = randomRange(0, numPlayers - 1); // Randomize currentPlayer
    if (currentPlayer == 0){
      otherPlayer = 1;
    }else{
      otherPlayer = 0;
    }
    G.whoseTurn = currentPlayer;  // Set turn
    treasureInDeck = randomRange(MIN_TREASURE, MAX_TREASURE); // Randomize number of treasure
    G.deckCount[currentPlayer] = randomRange(MIN_DECK_COUNT, MAX_DECK_COUNT); // Randomize deck count
    randomTreasureDeck(G.deck[currentPlayer], G.deckCount[currentPlayer], treasureInDeck); // Randomize a deck with given number of treasure
    draw_total = cardsToTreasure(G.deck[currentPlayer], G.deckCount[currentPlayer], treasure_needed); // Determine number of total cards to be drawn to reach 2 treasure
    discarded += (draw_total - treasure_needed); // Determine number of total cards that should be discarded (Adventurer + non-treasure cards drawn)
    G.handCount[currentPlayer] = randomRange(MIN_HAND_COUNT, MAX_HAND_COUNT); // Randomize hand count
    randomCards(G.hand[currentPlayer], G.handCount[currentPlayer]); // Randomize hand
    adventurer_position = randomRange(0, G.handCount[currentPlayer] - 1); // Randomize hand position of Adventurer card (and place it there)
    G.hand[currentPlayer][adventurer_position] = adventurer;

    // Establish dependencies for meaningful error output
    struct DepSet dep;
    dep.num_dep = 4;
    dep.dep_names[0] = "deck count";
    dep.dep_names[1] = "cards to treasure";
    dep.dep_names[2] = "hand count";
    dep.dep_names[3] = "hand position";
    dep.dependencies[0] = G.deckCount[currentPlayer];
    dep.dependencies[1] = draw_total;
    dep.dependencies[2] = G.handCount[currentPlayer];
    dep.dependencies[3] = adventurer_position;


     //{G.deckCount[currentPlayer], draw_total, G.handCount[currentPlayer], adventurer_position};
    //dep.dep_names = {"deck count", "cards to treasure", "hand count", "hand position"};
    //dep.dependencies = {G.deckCount[currentPlayer], draw_total, G.handCount[currentPlayer], adventurer_position};
    //int num_dep = 4;
    //char* dep_names[] = {"deck count", "cards to treasure", "hand count", "hand position"};
    //int dependencies[] = {G.deckCount[currentPlayer], draw_total, G.handCount[currentPlayer], adventurer_position};


    // Save game state  & execute via cardEffect
    memcpy(&testG, &G, sizeof(struct gameState));
    cardEffect(adventurer, choice1, choice2, choice3, &testG, adventurer_position, &bonus);

    // Active player tests
    assertEqualValPair(testG.handCount[currentPlayer], G.handCount[currentPlayer] + draw_total - discarded, hand_count_current, &hand_count_current_errors, dep);
    assertEqualValPair(testG.deckCount[currentPlayer], G.deckCount[currentPlayer] - draw_total, deck_count_current, &deck_count_current_errors, dep);
    assertEqualValPair(testG.discardCount[currentPlayer], G.discardCount[currentPlayer] + discarded, discard_count_current, &discard_count_current_errors, dep);
    num_treasure_actual = countTreasure(testG.hand[currentPlayer], testG.handCount[currentPlayer]);
    num_treasure_expected = countTreasure(G.hand[currentPlayer], G.handCount[currentPlayer]) + drawnTreasure;
    assertEqualValPair(num_treasure_actual, num_treasure_expected, treasure_in_hand_current, &treasure_in_hand_current_errors, dep);
    num_treasure_actual = countTreasure(testG.deck[currentPlayer], testG.deckCount[currentPlayer]);
    num_treasure_expected = countTreasure(G.deck[currentPlayer], G.deckCount[currentPlayer]) - drawnTreasure;
    assertEqualValPair(num_treasure_actual, num_treasure_expected, treasure_in_deck_current, &treasure_in_deck_current_errors, dep);

    // Inactive player tests
    assertEqualValPair(testG.handCount[otherPlayer], G.handCount[otherPlayer], hand_count_other, &hand_count_other_errors, dep);
    assertEqualValPair(testG.deckCount[otherPlayer], G.deckCount[otherPlayer], deck_count_other, &deck_count_other_errors, dep);
    assertEqualValPair(testG.discardCount[otherPlayer], G.discardCount[otherPlayer], discard_count_other, &discard_count_other_errors, dep);
    num_treasure_actual = countTreasure(testG.hand[otherPlayer], testG.handCount[otherPlayer]);
    num_treasure_expected = countTreasure(G.hand[otherPlayer], G.handCount[otherPlayer]);
    assertEqualValPair(num_treasure_actual, num_treasure_expected, treasure_in_hand_other, &treasure_in_hand_other_errors, dep);
    num_treasure_actual = countTreasure(testG.deck[otherPlayer], testG.deckCount[otherPlayer]);
    num_treasure_expected = countTreasure(G.deck[otherPlayer], G.deckCount[otherPlayer]);
    assertEqualValPair(num_treasure_actual, num_treasure_expected, treasure_in_deck_other, &treasure_in_deck_other_errors, dep);

    // Overall game state changes
    assertEqualValPair(testG.numBuys, G.numBuys + extraBuys, num_buys_diff, &num_buys_diff_errors, dep);
    bool same_supply = true;
    for (int i = 0; i < cards_count; i++){
       if (testG.supplyCount[i] != G.supplyCount[i]){
           same_supply = false;
       }
    }
    if (!same_supply){
      same_supply_errors++;
    }
    bool same_tokens = true;
    for (int i = 0; i < cards_count; i++){
       if (testG.embargoTokens[i] != G.embargoTokens[i]){
           same_supply = false;
       }
    }
    if (!same_tokens){
      same_tokens_errors++;
    }
    assertEqualValPair(testG.outpostPlayed, G.outpostPlayed, outpost_play_diff, &outpost_play_errors, dep);
    assertEqualValPair(testG.outpostTurn, G.outpostTurn, outpost_turn_diff, &outpost_turn_errors, dep);
    assertEqualValPair(testG.whoseTurn, G.whoseTurn, whose_turn_diff, &whose_turn_errors, dep);
    assertEqualValPair(testG.phase, G.phase, phase_diff, &phase_errors, dep);
    assertEqualValPair(testG.numActions, G.numActions + extraActions, num_action_diff, &num_action_errors, dep);
    assertEqualValPair(testG.playedCardCount, G.playedCardCount + cardsPlayed, played_card_diff, &played_card_errors, dep);
  }
  printValPairResults(hand_count_current, hand_count_current_errors, "Hand count errors - current player");
  printValPairResults(deck_count_current, deck_count_current_errors, "Deck count errors - current player");
  printValPairResults(discard_count_current, discard_count_current_errors, "Discard count errors - current player");
  printValPairResults(treasure_in_hand_current, treasure_in_hand_current_errors, "Treasure in hand errors - current player");
  printValPairResults(treasure_in_deck_current, treasure_in_deck_current_errors, "Treasure in deck errors - current player");
  printValPairResults(hand_count_other, hand_count_other_errors, "Hand count errors - other player");
  printValPairResults(deck_count_other, deck_count_other_errors, "Deck count errors - other player");
  printValPairResults(discard_count_other, discard_count_other_errors, "Discard count errors - other player");
  printValPairResults(treasure_in_hand_other, treasure_in_hand_other_errors, "Treasure in hand errors - other player");
  printValPairResults(treasure_in_deck_other, treasure_in_deck_other_errors, "Treasure in deck errors - other player");
  printValPairResults(num_buys_diff, num_buys_diff_errors, "Number of buys remaining errors");
  printf("Supply errors - %d\n\n", same_supply_errors);
  printf("Tokens errors - %d\n\n", same_tokens_errors);
  printValPairResults(outpost_play_diff, outpost_play_errors, "Outposts played errors");
  printValPairResults(outpost_turn_diff, outpost_turn_errors, "Outpost turn errors");
  printValPairResults(whose_turn_diff, whose_turn_errors, "Whose turn errors: ");
  printValPairResults(phase_diff, phase_errors, "Phase errors: ");
  printValPairResults(num_action_diff, num_action_errors, "Number of actions remaining errors");
  printValPairResults(played_card_diff, played_card_errors, "Played cards errors");
  return 0;
}
