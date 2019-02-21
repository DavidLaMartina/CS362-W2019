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

#define NUM_TESTS 100
#define MIN_START_ACTIONS = 0
#define MAX_START_ACTIONS = 10
#define MIN_DECK_COUNT = 10
#define MAX_DECK_COUNT = 50
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
  int hand_count_other_errors = 0; struct ValPair hand_count_other[NUM_TESTS];
  int deck_count_other_errors = 0; struct ValPair deck_count_other[NUM_TESTS];
  int discard_count_other_errors = 0; struct ValPair discard_count_other[NUM_TESTS];
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
    int extraBuys = 0;
    int extraActions = 2;
    int cardsPlayed = 1;

    // Variables to track for assertions
    int otherPlayer;
    int village_position;
    int discarded = 1;      // Exactly 1 card (the Village card) should be discarded
    int draw_total = 1;     // Exactly 1 card should be drawn from deck

    // Start new game for every test
    initializeGame(numPlayers, k, seed, &G);

    currentPlayer = randomRange(0, numPlayers -1);  // Randomize currentPlayer
    if (currentPlayer == 0){
      otherPlayer = 1;
    }else{
      otherPlayer = 0;
    }
    G.whoseTurn = currentPlayer;  // Set turn
    G.handCount[currentPlayer] = randomRange(MIN_HAND_COUNT, MAX_HAND_COUNT); // Randomize hand count
    village_position = randomRange(0, G.handCount[currentPlayer] - 1);  // Randomize village position in hand

    // Establish dependencies for meaningful error output
    struct DepSet dep;
    dep.num_dep = 3;
    dep.dep_names[0] = "hand count";
    dep.dep_names[1] = "hand position";
    dep.dep_names[2] = "number of actions";
    dep.dependencies[0] = G.handCount[currentPlayer];
    dep.dependencies[1] = village_position;
    dep.dependencies[2] = G.numActions;

    // Save game state & execute via cardEffect
    memcpy(&testG, &G, sizeof(struct gameState));
    cardEffect(village, choice1, choice2, choice3, &testG, village_position, &bonus);

    // Active player tests
    assertEqualValPair(testG.handCount[currentPlayer], G.handCount[currentPlayer] + draw_total - discarded, hand_count_current, &hand_count_current_errors, dep);
    assertEqualValPair(testG.deckCount[currentPlayer], G.deckCount[currentPlayer] - draw_total, deck_count_current, &deck_count_current_errors, dep);
    assertEqualValPair(testG.discardCount[currentPlayer], G.discardCount[currentPlayer] + discarded, discard_count_current, &discard_count_current_errors, dep);

    // Inactive player tests
    assertEqualValPair(testG.handCount[otherPlayer], G.handCount[otherPlayer], hand_count_other, &hand_count_other_errors, dep);
    assertEqualValPair(testG.deckCount[otherPlayer], G.deckCount[otherPlayer], deck_count_other, &deck_count_other_errors, dep);
    assertEqualValPair(testG.discardCount[otherPlayer], G.discardCount[otherPlayer], discard_count_other, &discard_count_other_errors, dep);

    // Overall game state changes
    assertEqualValPair(testG.numBuys, G.numBuys + extraBuys, num_buys_diff, &num_buys_diff_errors, dep);
    bool same_supply = true;
    for (int i = 0; i < num_cards; i++){
       if (testG.supplyCount[i] != G.supplyCount[i]){
           same_supply = false;
       }
    }
    if (!same_supply){
      same_supply_errors++;
    }
    bool same_tokens = true;
    for (int i = 0; i < num_cards; i++){
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
  printValPairResults(hand_count_other, hand_count_other_errors, "Hand count errors - other player");
  printValPairResults(deck_count_other, deck_count_other_errors, "Deck count errors - other player");
  printValPairResults(discard_count_other, discard_count_other_errors, "Discard count errors - other player");
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
