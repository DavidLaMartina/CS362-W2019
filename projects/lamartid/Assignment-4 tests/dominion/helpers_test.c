/*******************************************************************************
* Program for testing out test helpers
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "test_helpers.h"
#include "dominion.h"

int main(int argc, char *argv[]){
  srand(time(0));

  int deck_size = 20;
  int deck[deck_size];
  int num_treasure = 5;
  int treasure_desired = 2;

  randomTreasureDeck(deck, deck_size, num_treasure);

  printArray(deck, deck_size);

  printf("Copper is %d\n", copper);
  printf("Silver is %d\n", silver);
  printf("Gold is %d\n", gold);

  printf("There are %d treasure\n", countTreasure(deck, deck_size));

  printf("There are %d cards to get %d treasure\n",
          cardsToTreasure(deck, deck_size, treasure_desired), treasure_desired);

  return 0;
}
