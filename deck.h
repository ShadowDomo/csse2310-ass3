#ifndef DECK_H
#define DECK_H

#include <stdlib.h>
#include <stdio.h>
#include "util.h"



typedef struct Card Card;

/** Representation of a Card. **/
struct Card {
    // the card value
    char value;

    // the next card to be drawn
    Card *nextCard;
};

/** Representation of a Deck. **/
typedef struct Deck {
    // the numbers of cards in deck
    int count;

    // the top card
    Card *topCard;

    // the last card in deck
    Card *lastCard;
} Deck;


Card *next_card(Deck *deck);
void add_card(Deck *deck, Card *card);

Deck *allocate_deck(FILE *file);
#endif