#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

#define FILE_EXTENSION ".counts"

char * computeOutputFileName(const char * inputName) {
  char *outputName = malloc((strlen(inputName) + strlen(FILE_EXTENSION) + 1) * sizeof(*outputName));
  if (outputName == NULL) {
    perror("malloc failed");
  }
  strcpy(outputName, inputName);
  strcat(outputName, FILE_EXTENSION);
  return outputName;
}
