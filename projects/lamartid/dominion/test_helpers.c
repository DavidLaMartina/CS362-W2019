/*******************************************************************************
* Helpers functions for Dominion unit tests
*******************************************************************************/

#include "test_helpers.h"
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
void randomDeck(int deck[], int deck_size){
    // Calls randomCard to populate a "deck" (array) of random cards
    for (int i = 0; i < deck_size; i++){
        deck[i] = randomCard();
    }
}
