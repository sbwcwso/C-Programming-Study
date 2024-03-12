#include "input.h"
#include "deck.h"
#include "future.h"
#include <stdio.h>
#include <stdlib.h>

const char * eat_white_space(const char *str) {
  while (*str != '\0' && (*str == '\n' || *str == ' ' || *str == '\t')) {
    str++;
  }

  return str;
}

deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc) {
  deck_t ** hands = NULL;
  *n_hands = 0;

  char *linep = NULL;
  size_t count = 0;
  while (getline(&linep, &count, f) > 0) {
    deck_t * hand = hand_from_string(linep, fc);
    if (hand->n_cards < 5) {
      fprintf(stderr, "A poker hand has AT LEAST 5 cards in it.\n");
      exit(EXIT_FAILURE);
    }

    *n_hands += 1;
    hands = realloc(hands, *n_hands * sizeof(*hands));
    if (hands == NULL) {
      perror("realloc error");
      exit(EXIT_FAILURE);
    }
    hands[*n_hands - 1] = hand;
  }
  free(linep);
  return hands;
}

deck_t * hand_from_string(const char * str, future_cards_t * fc) {
  deck_t * hand = malloc(sizeof(*hand));
  /* fprintf(stderr, "%s", str); */
  if (hand == NULL) {
    perror("malloc error");
    exit(EXIT_FAILURE);
  }
  hand->n_cards = 0;
  hand->cards = NULL;

  str = eat_white_space(str);
  while(*str != '\0') {
    char value_let = *str++;
    char suit_let = *str++;
    /* fprintf(stderr, "%c%c\n", value_let, suit_let); */
    if (value_let != '?') {
      card_t card = card_from_letters(value_let, suit_let);
      add_card_to(hand, card);
    }
    else {
      size_t index = suit_let - '0';
      // ?index, index may be greater than 10
      while (*str >= '0' && *str <= '9') {
        index = 10 * index + *str++ - '0';
      }
      /* fprintf(stderr, "%u\n", (int)index); */
      add_future_card(fc, index, add_empty_card(hand));
    }
    str = eat_white_space(str);
  }
  return hand;
}


