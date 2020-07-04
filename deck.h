#ifndef DECK_H
#define DECK_H

#include "card.h"
#include "deck.h"
#include <QVector>

class Deck
{
public:
    QVector<Card*> cards;
    Deck();
    ~Deck();
    void fillDeck();
    void refillDeck(Deck drop);
    void shuffle();
};

#endif // DECK_H
