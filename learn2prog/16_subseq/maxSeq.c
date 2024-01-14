#include <stddef.h>

size_t maxSeq(int * array, size_t n) {
  if (n == 0) {
    return 0;
  }
  size_t maxIncContigSubseq = 1;
  size_t currIncContigSubseq = 1;
  for (size_t i = 1; i < n; i++) {
    if (array[i] > array[i-1]) {
      ++currIncContigSubseq;
    }
    else {
      if (currIncContigSubseq > maxIncContigSubseq) {
        maxIncContigSubseq = currIncContigSubseq;
      }
      currIncContigSubseq = 1;
    }
  }

  if (currIncContigSubseq > maxIncContigSubseq) {
    maxIncContigSubseq = currIncContigSubseq;
  }

  return maxIncContigSubseq;
}
