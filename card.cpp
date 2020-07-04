#include "card.h"
#include "deck.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>
#include <QPixmap>

#define sizeX 65
#define sizeY 100
#define dropX 300
#define dropY 150
#define drawX 30
#define drawY 30

extern MainWindow *w;
extern int direction, activePlayer;

Card::Card(){
}

Card::Card(int col, int num)
{
    QPointF tmp(880,530);
    switch(col){
    case 0: colour='r'; break;
    case 1: colour='y'; break;
    case 2: colour='g'; break;
    case 3: colour='b'; break;
    case 4: colour='w'; break;
    }
    number=num;
    wildColour='n';//none
    isActive=0;

    addToScene(tmp,1);
    qDebug() << colour << num;
}

void Card::addToScene(QPointF pos, bool isPlayer){
    if(isPlayer){
    QString tmp;
    switch(colour){
    case 'r': tmp+="red"; break;
    case 'y': tmp+="yel"; break;
    case 'g': tmp+="gre"; break;
    case 'b': tmp+="blu"; break;
    case 'w': tmp+="wild"; break;
    }
    tmp+=QString::number(number,10);
    tmp=":/slike/carte/"+tmp+".png";
    qDebug() << tmp;
    this->setPixmap(QPixmap(tmp).scaled(sizeX,sizeY));
    }
    else {          //AI draws
        QString tmp2=":/slike/carte/back.png";
        this->setPixmap(QPixmap(tmp2).scaled(sizeX,sizeY));
    }
    this->setPos(pos);
    w->scene->addItem(this);
    //qDebug() << "Becaj je genij";
}

void Card::changePosition(QPointF pos){
    this->setPos(pos);
}

void Card::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(activePlayer%4==0){ //the player's turn
        w->players[activePlayer]->isDone=w->players[activePlayer]->checkCard(this);
        if(w->players[activePlayer]->isDone)
            qDebug() << "Correct choice";
        else qDebug() << "NO! not right!";
    }
}
