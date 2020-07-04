#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"
#include "deck.h"
#include <QVector>

class Weight{
public:
    char type;
    int numberOf;

    Weight(){numberOf=0;}
};

class Player
{
    QVector<Card*> hand;
    Weight weights[4];
public:
    QString name;
    bool isPlayer;
    qreal rotation;
    bool isDone;

    Player(int i);
    ~Player();

    bool hasValidCard();
    void redraw();
    void takeCards();
    void drawCard();
    bool dropCard(Card *card);
    bool checkCard(Card *card);
    void rearrangeWeights();
    void updateWeights(char col, int by);
    bool chooseCard();
    void performTurn();
};

#endif // PLAYER_H
