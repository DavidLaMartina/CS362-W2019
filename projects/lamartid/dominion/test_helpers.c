/*******************************************************************************
* Helpers functions for Dominion unit tests
*******************************************************************************/

#include "test_helpers.h"
#include "rngs.h"
#include "dominion.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>

void assertTrue(bool expression){
    // Outputs text based on expression's truthiness
    if (expression){
        printf("...TEST SUCCESSFULLY COMPLETED\n");
    }else{
        printf("...TEST FAILED\n");
    }
}
void assertTrue_quiet(bool expression, char* output){
    // Only outputs if the expression is false
    if (!expression){
        printf("%s...TEST FAILED\n", output);
    }
}
void separate(char c, int r){
    // Prints row of identical characters and newline
    char sep[r];
    for (int i = 0; i < r; i++){
        sep[i] = c;
    }
    printf("%s\n", sep);
}
void copyArray(int orig[], int osize, int new[], int nsize){
    // Copies values from one array to another
    if (osize != nsize){
        return;
    }
    for (int i = 0; i < osize; i++){
        new[i] = orig[i];
    }
}
void printArray(int arr[], int size){
    for (int i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}
int num_compare(const void* a, const void* b) {
	// Returns "true" if a greater than b; false otherwise
	if (*(int*)a > *(int*)b)
		return 1;
	if (*(int*)a < *(int*)b)
		return -1;
	return 0;
}
int* newSort(int arr[], int size){
	// Copies array and performs qsort - NEED TO FREE
	int *newArr = malloc(size * sizeof(int));
	for (int i = 0; i < size; i++){
		newArr[i] = arr[i];
	}
	qsort(newArr, size, sizeof(int), num_compare);
	return newArr;
}
bool sameVals(int arr1[], int size1, int arr2[], int size2){
    // Returns true if arrays have exact same values (dpucliates matter)
	if (size1 != size2){
		return false;
	}
	int* arr1_sort = newSort(arr1, size1);
	int* arr2_sort = newSort(arr2, size2);
	for (int i = 0; i < size1; i++){
		if (arr1_sort[i] != arr2_sort[i]){
			free(arr1_sort);
			free(arr2_sort);
			return false;
		}
	}
	free(arr1_sort);
	free(arr2_sort);
	return true;
}
bool diffOrder(int arr1[], int size1, int arr2[], int size2){
    // Returns true if arrays are differently ordered
	if (size1 != size2){
		return false;
	}
	for (int i = 0; i < size1; i++){
		if (arr1[i] != arr2[i]){
			return true;
		}
	}
	return false;
}
int randomCard(){
    // Uses the cards_count variable from dominion_helpers to produce a random
    // integer between 0 and cards_count
    return (rand() % (cards_count + 1));
}
int randomNum(int low, int high){
    return (rand() % (high + 1 - low) + low);
}
int pickAnotherCard(int bad_card){
    // Generates "another" card when the card chosen by random card isn't
    // acceptable.
    int good_card = bad_card + 1;
    if (good_card >= cards_count){
        good_card = 0;
    }
    return good_card;
}
void consecutiveDeck(int deck[], int deck_size){
    // Builds a deck of "consecutive" card values, starting at '0' and ending
    // at the last card. If the deck_size is larger than cards_count,
    // the build will start over at 0.
    int next_card = 0;
    for (int i = 0; i < deck_size; i++){
        deck[i] = next_card;
        next_card++;
        if (next_card >= cards_count){
            next_card = 0;
        }
    }
}
void randomDeck(int deck[], int deck_size){
    // Calls randomCard to populate a "deck" (array) of random cards
    for (int i = 0; i < deck_size; i++){
        deck[i] = randomCard();
    }
}
void genericShuffle(int *arr, int size){
    // Re-orders array of cards
    // Source: https://stackoverflow.com/questions/6127503/shuffle-array-in-c
    if (size > 1){
        size_t i;
        for (i = 0; i < size - 1; i++){
            size_t j = i + rand() / (RAND_MAX / (size - i) + 1);
            int t = arr[j];
            arr[j] = arr[i];
            arr[i] = t;
        }
    }
}
void consecutiveDeckSelect(int *deck, int deck_size, int card, int card_num){
    // Populates card array with specific number of occurences of specific card,
    // along with consuecutive selection of other cards that CANNOT be the card
    // of interest
    int next_card = 0;
    if (deck_size < card_num){
        return;
    }
     int i;
     for (i = 0; i < card_num; i++){
         deck[i] = card;
     }
     for (i; i < deck_size; i++){
         if (next_card == card){
             next_card++;
         }
         if (next_card >= cards_count){
             next_card = 0;
         }
         deck[i] = next_card;
     }
}
void randomDeckSelect(int *deck, int deck_size, int card, int card_num){
    // Populates card array with specific number of occurences of specific card,
    // along with randomized selection of other cards that CANNOT be the card
    // of interest
    if (deck_size < card_num){
        return;
    }
    int i;
    for (i = 0; i < card_num; i++){
        deck[i] = card;
    }
    for (i; i < deck_size; i++){
        deck[i] = randomCard();
        if (deck[i] == card){
            deck[i] = pickAnotherCard(deck[i]);
        }
    }
    genericShuffle(deck, deck_size);
}
