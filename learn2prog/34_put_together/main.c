#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  FILE *f = fopen(filename, "r");
  if (f == NULL) {
    perror("Could not open file");
    exit(EXIT_FAILURE);
  }

  counts_t *c = createCounts();

  char * lineptr = NULL;
  size_t n = 0;
  while (getline(&lineptr, &n, f) > 0) {
    char * newline = strchr(lineptr, '\n');
    *newline = '\0';
    addCount(c, lookupValue(kvPairs, lineptr));
  }
  free(lineptr);

  if (fclose(f)) {
    perror("Could not close file");
    exit(EXIT_FAILURE);
  }

  return c;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if (argc < 3) {
    fprintf(stderr, "Usage: ./count_values kvs1.txt list1a.txt [list1b.txt ...]");
    return EXIT_FAILURE;
  }

 //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kvPairs = readKVs(argv[1]);
 //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++)
    {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
      counts_t *c = countFile(argv[i], kvPairs);

    //compute the output file name from argv[i] (call this outName)
      char * outName = computeOutputFileName(argv[i]);
    //open the file named by outName (call that f)
      FILE * f = fopen(outName, "w");
      if (f == NULL) {
        perror("could not open file");
        return EXIT_FAILURE;
      }
    //print the counts from c into the FILE f
      printCounts(c, f);

    //close f
      if (fclose(f)) {
        perror("could close file");
        return EXIT_FAILURE;
      }

    //free the memory for outName and c
      free(outName);
      freeCounts(c);
    }



 //free the memory for kv
  freeKVs(kvPairs);

  return EXIT_SUCCESS;
}
