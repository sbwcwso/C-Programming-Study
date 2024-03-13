#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"



int main(int argc, char ** argv) {
  // Check command line arguments/report errors
  if (argc < 2 || argc > 3) {
    fprintf(stderr, "Usage: ./poker input_file [trials]\n");
    return EXIT_FAILURE;
  }
  int num_trials = 1;
  if (argc == 3) {
    num_trials = atoi(argv[2]);
    if (num_trials <= 0) {
        fprintf(stderr, "trials must be a positive number.");
        return EXIT_FAILURE;
    }
  }

  // Open the input file and read the hands in it
  FILE *f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("could not open file");
    return EXIT_FAILURE;
  }
  deck_t ** hands;
  size_t n_hands;
  future_cards_t fc;
  fc.decks = NULL;
  fc.n_decks = 0;
  hands = read_input(f, &n_hands, &fc);
  assert(n_hands >= 2);
  /* Create a deck with the remaining cards */
  deck_t *remaining_deck = build_remaining_deck(hands, n_hands);

  /* Create an array to count how many times each hand
   * wins, with one more element for if there was a tie
   */
  unsigned int counts[n_hands + 1];
  for (size_t i = 0; i < n_hands + 1; i++) {
    counts[i] = 0;
  }

  /* - Do each Monte Carlo trial (repeat num_trials times) */
  for(int i = 0; i < num_trials; i++) {
    /* Shuffle the deck of remaining cards */
    shuffle(remaining_deck);
    /* Assign unknown cards from the shuffled deck */
    future_cards_from_deck(remaining_deck, &fc);
    /* Use compare_hands (from Course 3) to 
     * figure out which hand won.
     */
    size_t winner = 0;
    int is_tie = 0;
    for (size_t j = 1; j < n_hands; j++) {
      int cmp = compare_hands(hands[j], hands[winner]);
      if (cmp > 0) {
        winner = j;
        is_tie = 0;
      }
      else if (cmp == 0) {
        is_tie = 1;
      }
    }
    
    /* Increment the win count for the winning 
     * hand (or for the "ties" element of the array if there was a tie).
     */
    if (is_tie) {
      counts[n_hands]++;
    } else {
      counts[winner]++;
    }
  }

  /* print results */
  for (size_t i = 0; i < n_hands; i++) {
    printf("Hand %lu won %u / %u times (%.2f%%)\n",
           i, counts[i], num_trials, 100 * counts[i] / (double)num_trials);
  }
  printf("And there were %u ties\n", counts[n_hands]);

  /* free any memory allocated, and close any open files. */
  for(size_t i = 0; i < fc.n_decks; i++) {
    free((fc.decks)[i].cards);
  }
  free(fc.decks);

  for(size_t i = 0; i < n_hands; i++) {
    free_deck(hands[i]);
  }
  free(hands);
  
  free_deck(remaining_deck);

  if (fclose(f)) {
    perror("could not close file");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
