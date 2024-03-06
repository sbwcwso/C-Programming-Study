#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}

//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

// This function will read files in line and append it to the original result.
void readInLine(char *** linesPtr, size_t * lineNumPtr, FILE * f) {
  char * currentLine = NULL;
  size_t currentLineSize = 0;
  while (getline(&currentLine, &currentLineSize, f) >= 0) {
    *linesPtr = realloc(*linesPtr, (++(*lineNumPtr)) * sizeof(**linesPtr));
    if (*linesPtr == NULL) {
      perror("realloc failed.");
      exit(EXIT_FAILURE);
    }

    (*linesPtr)[*lineNumPtr - 1] = currentLine;
    currentLine = NULL;
    currentLineSize = 0;
  }
  free(currentLine);
}

void printAndFree(char ** lines, size_t lineNum) {
  for (size_t i = 0; i < lineNum; i++) {
    printf("%s", lines[i]);
    free(lines[i]);
  }
  free(lines);
}

void handleFile(FILE *f) {
  char **lines = NULL;
  size_t lineNum = 0;

  readInLine(&lines, &lineNum, f);
  sortData(lines, lineNum);
  printAndFree(lines, lineNum);
}

int main(int argc, char ** argv) {
  if (argc == 1) {
    handleFile(stdin);
  }
  else {
    char ** fileNamePtr = argv + 1;
    while (*fileNamePtr != NULL) {
      FILE * f = fopen(*(fileNamePtr++), "r");
      if (f == NULL) {
        perror("Could not open file");
        return EXIT_FAILURE;
      }

      handleFile(f);

      if (fclose(f)) {
        perror("Could not close file");
        return EXIT_FAILURE;
      }
    }
  }
  return EXIT_SUCCESS;
}
