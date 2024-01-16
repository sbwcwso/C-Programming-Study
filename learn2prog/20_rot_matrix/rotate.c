#include <stdlib.h>
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
