/*******************************************************************************
* Helpers functions for Dominion unit tests
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>

struct DepSet{
  int num_dep;
  char* dep_names[4];
  int dependencies[4];
};
struct ValPair{
  int actual;
  int expected;
  struct DepSet dep;
};

void assertTrue(bool expression);
void assertTrue_quiet(bool expression, char* output);

void assertEqualValPair(int actual, int expected, struct ValPair *err_arr, int *counter, struct DepSet dep);
void printValPairArr(struct ValPair *arr, int size);
void printValPairResults(struct ValPair *arr, int size, char *message);

int randomRange(int low, int high);


void separate(char c, int r);
void copyArray(int orig[], int osize, int new[], int nsize);
void printArray(int arr[], int size);
int num_compare(const void* a, const void* b);
int* newSort(int arr[], int size);
bool sameVals(int arr1[], int size1, int arr2[], int size2);
bool diffOrder(int arr1[], int size1, int arr2[], int size2);
int randomCard();
int randomNum(int low, int high);
int pickAnotherCard(int bad_card);
void consecutiveDeck(int deck[], int deck_size);

void randomCards(int deck[], int deck_size);

void randomDeck(int deck[], int deck_size);
void genericShuffle(int *arr, int size);
void consecutiveDeckSelect(int *deck, int deck_size, int card, int card_num);
void randomDeckSelect(int *deck, int deck_size, int card, int card_num);

void randomTreasureDeck(int *deck, int deck_size, int num_treasure);

int countTreasure(int *cards, int size);
int cardsToTreasure(int *cards, int size, int treasure_needed);
