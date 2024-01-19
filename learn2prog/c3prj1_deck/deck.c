#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "cards.h"
#include "deck.h"
void print_hand(deck_t * hand){
  for (size_t i = 0; i < hand->n_cards; i++){
    print_card(*(hand->cards[i]));
    printf(" ");
  }
}

int deck_contains(deck_t * d, card_t c) {
  for (size_t i = 0; i < d->n_cards; i++){
    card_t card_in_deck = *(d->cards[i]);
    if (card_in_deck.suit == c.suit && card_in_deck.value == c.value)
      return 1;
  }
  return 0;
}

void shuffle(deck_t * d){
  size_t d_size = d->n_cards;
  for (size_t i = 0; i < d_size - 1; i++) {
    size_t j = i + rand() / (RAND_MAX / (d_size - i) + 1);  // j in [i, n)
    card_t * temp = d->cards[i];
    d->cards[i] = d->cards[j];
    d->cards[j] = temp;
  }
}

void assert_full_deck(deck_t * d) {
  for (size_t i = 0; i < d->n_cards - 1; i++) {
    deck_t rest_of_d;
    rest_of_d.cards = d->cards + i + 1;
    rest_of_d.n_cards = d->n_cards - i - 1;
    assert(!deck_contains(&rest_of_d, *(d->cards[i])));
  }
}
