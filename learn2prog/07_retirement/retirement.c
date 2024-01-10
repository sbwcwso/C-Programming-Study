#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;

void print_info(int curAge, double balance) {
  printf("Age %3d month %2d you have $%.2lf\n", curAge / 12, curAge % 12, balance);
}

double calculate_and_print_retire_info(int startAge, double balance, retire_info account) {
  for (int i = account.months; i > 0; i--) {
    print_info(startAge, balance);
    balance += balance * account.rate_of_return / 12 + account.contribution;
    startAge++;
  }
  return balance;
}

void retirement (int startAge, double initial, retire_info working, retire_info retired) {
  double balance = initial;
  balance = calculate_and_print_retire_info(startAge, balance, working);
  startAge += working.months;
  balance = calculate_and_print_retire_info(startAge, balance, retired);
}

int main(void) {
  retire_info working = {489, 1000, 0.045};
  retire_info retired = {384, -4000, 0.01};
  int startAge = 327;
  double initial = 21345;
  retirement(startAge, initial, working, retired);
  return EXIT_SUCCESS;
}
