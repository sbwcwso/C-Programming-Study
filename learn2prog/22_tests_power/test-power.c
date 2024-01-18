#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  if (power(x, y) != expected_ans) {
    printf("power(%u %u) != %u", x, y, expected_ans);
    exit(EXIT_FAILURE);
  }
}

int main(void) {

  run_check(0, 0, 1);
  run_check(0, 1, 0);
  run_check(0, 2, 0);
  run_check(1, 0, 1);
  run_check(1, 1, 1);
  run_check(1, 2, 1);
  run_check(1, 33, 1);
  run_check(87, 0, 1);
  run_check(87, 1, 87);
  run_check(87, 2, 7569);
  run_check(2, 3, 8);
  run_check(3, 3, 27);
  run_check(2147483648, 1, 2147483648);  // 2^31

  return EXIT_SUCCESS;
}


