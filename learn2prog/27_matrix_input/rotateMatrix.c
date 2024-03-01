#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10

void rotate(char matrix[SIZE][SIZE]) {
  if (matrix == NULL) return;

  char tmpMatrix[SIZE][SIZE];
  for (int i = 0; i < SIZE; i++)
    for (int j = 0; j < SIZE; j++)
      tmpMatrix[i][j] = matrix[i][j];

  for (int i = 0; i < SIZE; i++)
    for (int j = 0; j < SIZE; j++)
      matrix[i][j] = tmpMatrix[SIZE - 1 - j][i];
}


int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: rotateMatrix input\n");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Could not open %s\n", argv[1]);
    return EXIT_FAILURE;
  }

  char matrix[SIZE][SIZE];
  int ch;
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      ch = fgetc(f);
      if (ch == '\n' || ch == EOF) {
        fprintf(stderr, "Invalid input: Line is too short.\n");
        return EXIT_FAILURE;
      }
      matrix[i][j] = ch;
    }
      ch = fgetc(f);
      if (ch != '\n' && ch != EOF) {
        fprintf(stderr, "Invalid input: Line is too long.\n");
        return EXIT_FAILURE;
      }
  }
  if ((ch = fgetc(f)) != EOF) {
    fprintf(stderr, "Invalid input: file is too long (read %d instead of EOF)\n", ch);
    return EXIT_FAILURE;
  }
  
  rotate(matrix);
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      printf("%c", matrix[i][j]);
    }
    printf("\n");
  }

  if (fclose(f) != 0) {
    perror("File close error.");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
