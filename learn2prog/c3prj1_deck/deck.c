#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "cards.h"
#include "deck.h"

// course 3
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

// course 4
void add_card_to(deck_t * deck, card_t c) {
  deck->n_cards += 1;

  card_t ** cards = deck->cards;
  cards = realloc(cards, (deck->n_cards) * sizeof(*cards));
  if (cards == NULL) {
    perror("realloc error");
    exit(EXIT_FAILURE);
  }
  deck->cards = cards;

  card_t * newcard = malloc(sizeof(*newcard));
  if (newcard == NULL) {
    perror("malloc error");
    exit(EXIT_FAILURE);
  }
  *newcard = c;
  cards[deck->n_cards - 1] = newcard;
}

card_t * add_empty_card(deck_t * deck) {
  card_t card ;
  card.suit = 0;
  card.value = 0;

  add_card_to(deck, card);
  return (deck->cards)[deck->n_cards - 1];
}

deck_t * make_deck_exclude(deck_t * excluded_cards) {
  deck_t * deck = malloc(sizeof(*deck));
  if (deck == NULL) {
    perror("malloc error");
    exit(EXIT_FAILURE);
  }
  deck->n_cards = 0;
  deck->cards = NULL;

  for (unsigned int i = 0; i < 52; i++) {
    card_t card = card_from_num(i);
    if (!deck_contains(excluded_cards, card)) {
      add_card_to(deck, card);
    }
  }

  return deck;
}

deck_t * build_remaining_deck(deck_t ** hands, size_t n_hands) {
  deck_t * excluded_cards = malloc(sizeof(*excluded_cards));
  if (excluded_cards == NULL) {
    perror("malloc error");
    exit(EXIT_FAILURE);
  }
  excluded_cards->n_cards = 0;
  excluded_cards->cards = NULL;

  for (size_t i = 0; i < n_hands; i++) {
    deck_t * hand = hands[i];
    for (size_t j = 0; j < hand->n_cards; j++) {
      card_t * card = (hand->cards)[j];
      if (!deck_contains(excluded_cards, *card)) {
        add_card_to(excluded_cards, *card);
      }
    }
  }
  deck_t * deck = make_deck_exclude(excluded_cards);
  free_deck(excluded_cards);
  return deck;
}

void free_deck(deck_t * deck) {
  if (deck == NULL) {
    return;
  }
  for (size_t i = 0; i < deck->n_cards; i++) {
    free((deck->cards)[i]);
  }
  free(deck->cards);
  free(deck);
}
