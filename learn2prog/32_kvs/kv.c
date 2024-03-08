#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"

/**
 * get key value for a single line.
 */
kvpair_t * getKeyValue(char * lineptr) {
    char * division = strchr(lineptr, '=');
    if (division == NULL) {
      fprintf(stderr, "key, value format error.");
      exit(EXIT_FAILURE);
    }
    char * lastChar = strchr(lineptr, '\n');
    if (lastChar == NULL) {
      fprintf(stderr, "lineptr format error.");
      exit(EXIT_FAILURE);
    }
    *division = '\0';
    *lastChar = '\0';

    kvpair_t * kvpair = malloc(sizeof(*kvpair));
    if (kvpair == NULL) {
      perror("malloc error");
      exit(EXIT_FAILURE);
    }
    kvpair->key = lineptr;
    kvpair->value = division + 1;
    return kvpair;
}

/**
 * append a new key value pair to a given array.
 */
void appendKeyValue(kvpair_t *** kvpairsptr, size_t * numkvpairsptr, kvpair_t * kvpair) {
    *kvpairsptr = realloc(*kvpairsptr, (++(*numkvpairsptr)) * sizeof(**kvpairsptr));
    if (*kvpairsptr == NULL) {
      perror("realloc error");
      exit(EXIT_FAILURE);
    }

    (*kvpairsptr)[*numkvpairsptr - 1] = kvpair;
}


kvarray_t * readKVs(const char * fname) {
  FILE *f = fopen(fname, "r");
  if (f == NULL) {
    perror("Could not open file");
    exit(EXIT_FAILURE);
  }

  size_t numkvpairs = 0;
  kvpair_t ** kvpairs = NULL;
  char * lineptr = NULL;
  size_t n = 0;
  while (getline(&lineptr, &n, f) > 0) {
    appendKeyValue(&kvpairs, &numkvpairs, getKeyValue(lineptr));
    lineptr = NULL;
    n = 0;
  }
  free(lineptr);

  if (fclose(f)) {
    perror("Could not close file");
    exit(EXIT_FAILURE);
  }

  kvarray_t * pairs = malloc(sizeof(*pairs));
  if (pairs == NULL) {
    perror("malloc error");
    exit(EXIT_FAILURE);
  }
  pairs->numkvpairs = numkvpairs;
  pairs->kvpairs = kvpairs;
  return pairs;
}

void freeKVs(kvarray_t * pairs) {
  for(int i = 0; i < pairs->numkvpairs; i++) {
    kvpair_t *pair = pairs->kvpairs[i];
    free(pair->key);
    free(pair);
  }
  free(pairs->kvpairs);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  for(int i = 0; i < pairs->numkvpairs; i++) {
    kvpair_t *pair = pairs->kvpairs[i]; 
    printf("key = '%s' value = '%s'\n", pair->key, pair->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {

  for(int i = 0; i < pairs->numkvpairs; i++) {
    kvpair_t *pair = pairs->kvpairs[i];
    if (strcmp(key, pair->key) == 0) {
      return pair->value;
    }
  }
  return NULL;
}
