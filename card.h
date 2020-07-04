#ifndef CARD_H
#define CARD_H

#include <QGraphicsPixmapItem>
#include <QPointF>

class Card : public QGraphicsPixmapItem{
    char colour;
    int number; //0-9 regular numbers; 10 - next player skips a turn;
                //11 - reverse the direction; 12 - draw 2 cards; 13 - draw 4; 14 - wild card
    char wildColour; //colour of wild cards - after it has been deployed
public:
    bool isActive;

    Card();
    Card(int colour, int number);
    void addToScene(QPointF pos, bool isPlayer);
    void changePosition(QPointF pos);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    char getColour(){return colour;}
    void setColour(char newColour){colour=newColour;}
    int getNumber(){return number;}
    void setNumber(int newNumber){number=newNumber;}
    char getWildColour(){return wildColour;}
    void setWildColour(char newColour){wildColour=newColour;}
};

#endif // CARD_H
