/*******************************************************************************
* Unit tests for Smithy
*   int shuffle(int player, struct gameState *state);
*
*
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

#define TESTCARD "UNDECIDED"

// Set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1
#define SEPARATE separate('*', 80)
#define SPACE printf("\n")

int main(int argc, char *argv[]){
    SEPARATE;
    printf("--------------------Testing Card: %s --------------------\n", TESTCARD);
    // No choices for Smithy - 1 "total" test with multiple assertions
    printf("TEST 2: PLACEHOLD\n");
}
