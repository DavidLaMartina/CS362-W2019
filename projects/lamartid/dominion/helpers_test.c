/*******************************************************************************
* Program for testing out test helpers
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "test_helpers.h"

int main(int argc, char *argv[]){
  srand(time(0));

  int low = 0;
  int high = 1;
  int iter = 20;

  for (int i = 0; i < iter; i++){
    printf("%d\n", randomRange(low, high));
  }

  return 0;
}
