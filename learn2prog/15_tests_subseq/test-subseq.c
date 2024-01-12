#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <limits.h>

#define MAX_SIZE 10

size_t maxSeq(int * array, size_t n);


int main(void) {

  // test1: null array.
  if (maxSeq(NULL, 0) != 0) {
    printf("Failed test 1\n");
    return EXIT_FAILURE;
  }

  // test2: increasing sequence
  int array1[MAX_SIZE] = {INT_MIN, -100, -37, -1, 0, 1, 17, 29, 97, INT_MAX};
  for (int i = 0; i <= MAX_SIZE; i++) {
    if (maxSeq(array1, i) != i) {
      printf("Failed test 2\n");
      return EXIT_FAILURE;
    }
  }

  // test3: not strictly increasing sequence
  int array2[4] = {INT_MIN, -100, -100, INT_MAX};
  if (maxSeq(array2, 4) != 2) {
    printf("Failed test 3\n");
    return EXIT_FAILURE;
  }

  // test4: the function should return 1
  int array3[MAX_SIZE] = {INT_MAX, 97, 79, 63, 1, 0, -1, -34, -67, INT_MIN};
  for (int i = 1; i <= MAX_SIZE; i++) {
    if (maxSeq(array3, i) != 1) {
      printf("Failed test 4\n");
      return EXIT_FAILURE;
    }
  }

  // test5: the program doesn't fine discontiguous increasing sequence
  int array4[MAX_SIZE] = { 1, 2, 1, 3, 5, 7, 2, 4, 6, 9};
  if (maxSeq(array4, MAX_SIZE) != 4) {
      printf("Failed test 5\n");
    return EXIT_FAILURE;
  }

  printf("success\n");
  return EXIT_SUCCESS;
}

