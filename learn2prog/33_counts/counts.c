#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"
counts_t * createCounts(void) {
  counts_t * counts = malloc(sizeof(*counts));
  if (counts == NULL) {
    perror("malloc error");
    exit(EXIT_FAILURE);
  }
  counts->unkonwCount = 0;
  counts->countsArray = NULL;
  counts->countNum = 0;
  return counts;
}
void addCount(counts_t * c, const char * name) {
  if (name == NULL) {
    c->unkonwCount++;
    return;
  }
  one_count_t ** countsArray = c->countsArray;
  // name exist already
  for(int i = 0; i < c->countNum; i++) {
    if (strcmp(countsArray[i]->name, name) == 0) {
      countsArray[i]->count += 1;
      return;
    }
  }
  // name does not exist
  (c->countNum)++;
  countsArray = realloc(countsArray, c->countNum * sizeof(*countsArray));
  if (countsArray == NULL) {
    perror("realloc error");
    exit(EXIT_FAILURE);
  }
  one_count_t * oneCount = malloc(sizeof(*oneCount));
  if (oneCount == NULL) {
    perror("malloc error");
    exit(EXIT_FAILURE);
  }
  char *newName = malloc((strlen(name) + 1) * sizeof(*newName));
  if (newName == NULL) {
    perror("malloc error");
    exit(EXIT_FAILURE);
  }
  strcpy(newName, name);

  oneCount->name = newName;
  oneCount->count = 1;
  countsArray[c->countNum - 1] = oneCount;

  c->countsArray = countsArray;
}

void printCounts(counts_t * c, FILE * outFile) {
  one_count_t ** countsArray = c->countsArray;
  for(int i = 0; i < c->countNum; i++) {
    fprintf(outFile, "%s: %d\n", countsArray[i]->name, countsArray[i]->count);
  }
  if (c->unkonwCount > 0) {
    fprintf(outFile, "<unknown> : %d\n", c->unkonwCount);
  }
}

void freeCounts(counts_t * c) {
  one_count_t ** countsArray = c->countsArray;
  for(int i = 0; i < c->countNum; i++) {
    free(countsArray[i]->name);
    free(countsArray[i]);
  }
  free(countsArray);
  free(c);
}
