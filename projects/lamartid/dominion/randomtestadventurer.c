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
#define NUM_TESTS 10
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

  // Establish dependencies
  int currentPlayer;
  int handPos;
  struct gameState G, testG;  // Before and after game states

  // Non-dependent parameters
  int drawnTreasure = 0;
  int z = 0;
  int temphand[MAX_HAND];
  int bonus = 0;

  // Variables to track for assertions
  int otherPlayer;
  int treasureInDeck;
  int adventurer_position;
  int discarded = 1;      // At least the 1 Adventurer card will be discarded
  int shuffledCards = 0;  // No shuffle required; at least 2 treasures in deck



  for (int i = 0; i < NUM_TESTS; i++){
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
    // Randomize a deck with given number of tresaur
    randomTreasureDeck(G.deck[currentPlayer], G.deckCount[currentPlayer],
                       treasureInDeck);
    // Randomize hand count
    G.handCount[currentPlayer] = randomRange(MIN_HAND_COUNT, MAX_HAND_COUNT);
    // Randomize hand
    randomCards(G.hand[currentPlayer], G.handCount[currentPlayer]);
    // Randomize hand position of Adventurer card (and place it there)
    adventurer_position = randomRange(0, G.handCount[currentPlayer] - 1);
    G.hand[currentPlayer][adventurer_position] = adventurer;

    // Save game state before testing
    memcpy(&testG, &G, sizeof(struct gameState));

    adventurer_play(currentPlayer, drawnTreasure, z, temphand, &testG, adventurer_position, &bonus);
  }
  return 0;
}
