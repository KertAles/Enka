#include "deck.h"
#include "card.h"

#include <mainwindow.h>
#include <QVector>
#include <QPointF>
#include <QDebug>

extern MainWindow *w;

void Deck::fillDeck(){
    int i=0, j=0;
    for(int k=0; k<2; k++){
        for(i=0; i<4; i++)               //4 colours
            for(j=0; j<13; j++){         //13 types
                cards.push_back(new Card(i,j));
            }
    }
    for(i=0; i<4; i++)               //4 * 2 Wild cards
        for(j=13; j<15; j++){
            cards.push_back(new Card(4,j));
        }
    shuffle();
    qDebug() << cards.size();
}

void Deck::shuffle(){
    int switchWith, sajz=cards.size();
    Card* tmp;
    for(int i=0; i<2; i++)          //through the pile twice
        for(int j=0; j<sajz; j++){
            switchWith=rand()%sajz; //switch with random index
            tmp=cards[j];
            cards[j]=cards[switchWith];
            cards[switchWith]=tmp;
        }
}


void Deck::refillDeck(Deck drop){
    Card* tmp;
    tmp=drop.cards.last();           //remembers the last card on the drop pile, is added to the empty drop deck
    while(!(drop.cards.isEmpty())){  //dropDeck isn't empty
        cards.push_back(drop.cards.last());
        drop.cards.remove(drop.cards.size()-1);
    }

    drop.cards.push_back(tmp);
    QPointF point(880,530);
    for(int i=0; i<cards.size(); i++){
        cards[i]->setPos(point);
        cards[i]->setVisible(1);
    }
    shuffle();
}

Deck::~Deck(){
    Card *tmp;
    for(int i=0; i<cards.size(); i++){
        tmp=cards[i];
        delete tmp;
    }
}
Deck::Deck(){
}
