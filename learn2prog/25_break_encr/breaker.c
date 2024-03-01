#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define ALPHA_SIZE 26

int * arrayMax(int * array, int n) {
  if (n == 0) {
    return NULL;
  }

  int max = array[0];
  int max_index = 0;
  for (int i = 1; i < n; i++) {
    if (array[i] > max) {
      max_index = i;
      max = array[i];
    }
  }
  return array + max_index;
}

char FindMostCommonLetter(FILE * f) {
  int counts[ALPHA_SIZE] = {0};
  int ch;
  while ( (ch = fgetc(f)) != EOF ) {
    if (isalpha(ch)) {
      counts[tolower(ch) - 'a']++;
    }
  }
  return 'a' + arrayMax(counts, ALPHA_SIZE) - counts;
}


int main(int argc, char** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: break inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE *f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Couldn't open the file.");
    return EXIT_FAILURE;
  }
  int offset = FindMostCommonLetter(f) - 'e';
  if (offset < 0) {
    offset += 26;
  }
  printf("%d\n", offset);

  if (fclose(f) != 0) {    
    perror("Failed to close the input file!");    
    return EXIT_FAILURE;  
  }

  return EXIT_SUCCESS;
}

