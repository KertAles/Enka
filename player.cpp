#include "player.h"
#include "deck.h"
#include "mainwindow.h"

#include <QVector>
#include <windows.h>
#include <QDebug>
#include <QAbstractButton>
#include <QMessageBox>
#include <cmath>

#define dropX 300
#define dropY 150

#define beginX 20
#define beginY 400
#define skipX 75
#define skipY 110

extern MainWindow *w;
extern Deck drawPile, dropPile;
extern int direction, activePlayer;


Player::Player(int n){
    rotation=((n*90)*3.14)/180; //rotation of cards
    if(n==0)
        isPlayer=1;
    else isPlayer=0;

    weights[0].type='r';
    weights[1].type='b';
    weights[2].type='g';
    weights[3].type='y';

    switch(n){
    case 0: name="Kralj"; break;
    case 1: name="kozina"; break;
    case 2: name="becaj"; break;
    case 3: name="horjulska princesa"; break;
    }

    int i=7;
    while(i --> 0)
    drawCard();

    if(n==0)
        redraw();
}

Player::~Player(){
    Card *tmp;
    for(int i=0; i<hand.size(); i++){
        tmp=hand[i];
        delete tmp;
    }
}

void Player::drawCard(){
    hand.push_back(drawPile.cards.last());
        drawPile.cards.remove(drawPile.cards.size()-1);
    if(drawPile.cards.isEmpty())        //refills empty draw pile
        drawPile.refillDeck(dropPile);
    if(!isPlayer){
        updateWeights(hand.last()->getColour(), 1);
    }
}

bool Player::dropCard(Card *card){
    int i;
    bool neki=0;
    i=hand.indexOf(card);
    if(i!=-1){                   //just in case card isn't in the hand
        card->setPos(dropX,dropY);
        neki=1;
        dropPile.cards.last()->setVisible(0);
        dropPile.cards.push_back(hand[i]);
        hand.remove(i);

        QString tmp;
        char col=dropPile.cards.last()->getColour();
        if(col=='w')
            col=dropPile.cards.last()->getWildColour();
        switch(col){
        case 'r': tmp+="red"; break;
        case 'y': tmp+="yel"; break;
        case 'g': tmp+="gre"; break;
        case 'b': tmp+="blu"; break;
        }
        tmp=":/slike/carte/"+tmp+".png";
        w->colour.setPixmap(QPixmap(tmp).scaled(30,30));
                int neki=dropPile.cards.last()->getNumber();
        tmp=QString::number(neki,10);

        tmp=":/slike/carte/"+tmp+".png";
        w->number.setPixmap(QPixmap(tmp).scaled(30,30));

        qDebug() << dropPile.cards.last()->getColour();
        if(hand.isEmpty()){      //point of the game is to have no cards left
            w->victory(this);
        }
    }
    return neki;
}

bool Player::checkCard(Card *card){
    char col = card->getColour();
    int num = card->getNumber();
    bool isLegal=0;

    if(col==dropPile.cards.last()->getColour() ||
            num==dropPile.cards.last()->getNumber() ||
            col==dropPile.cards.last()->getWildColour()){  //selected card is a valid choice
        isLegal=dropCard(card);
        if(!isPlayer){  //AI weights update
            updateWeights(col, -1);
        }
        if(card->getNumber()==10){
            if(direction==1)
                direction=-1;
            else direction=1;
        }
    }
    else if(card->getColour()=='w'){ //is wild card
        if(isPlayer){/*
            QMessageBox msgBox;
            msgBox.setText("Colour choice");
            msgBox.setInformativeText("Which colour will the wild card be?");

            QAbstractButton *redButton;
            redButton->setText("Red");
            msgBox.addButton(redButton, QMessageBox::AcceptRole);

            QAbstractButton *blueButton;
            blueButton->setText("Blue");
            msgBox.addButton(blueButton, QMessageBox::AcceptRole);

            QAbstractButton *greenButton;
            greenButton->setText("Green");
            msgBox.addButton(greenButton, QMessageBox::AcceptRole);

            QAbstractButton *yellowButton;
            yellowButton->setText("Yellow");
            msgBox.addButton(yellowButton, QMessageBox::AcceptRole);

            msgBox.setIcon(QMessageBox::Question);
            msgBox.exec();

            QString wildColour;
            if(msgBox.clickedButton()==redButton){
                wildColour="red"; card->setWildColour('r');}
            else if(msgBox.clickedButton()==blueButton){
                wildColour="blu"; card->setWildColour('b');}
            else if(msgBox.clickedButton()==greenButton){
                wildColour="gre"; card->setWildColour('g');}
            else if(msgBox.clickedButton()==yellowButton){
                wildColour="yel"; card->setWildColour('y');}*/
            card->setWildColour('r');
        }
        else{ //AI chooses the colour
            card->setWildColour(weights[0].type);
        }
        isLegal=dropCard(card);
    }
    return isLegal;
}

void Player::rearrangeWeights(){
    Weight tmp;
    for(int i=0; i<4; i++)
        for(int j=i; j<3; j++)
            if(weights[j].numberOf<weights[j+1].numberOf){
                tmp=weights[j];
                weights[j]=weights[j+1];
                weights[j+1]=tmp;
            }
}

void Player::updateWeights(char col, int by){ //by = +-1
    for(int i=0; i<4; i++){
        if(weights[i].type==col){
            weights[i].numberOf+=by;
        }
    }
    rearrangeWeights();
}

bool Player::chooseCard(){ //for the AI
    bool isFinished;
    for(int i=0; i<4; i++)
        for(int j=0; j<hand.size(); j++){
            if(weights[i].type==hand[j]->getColour()) //tries the card colour with the highest weight first, etc.
                isFinished=checkCard(hand[j]);
                if(isFinished){//the card chosen has been put down
                    j=120;
                    i=4;
                }
        }
    if(!isFinished){
        for(int j=0; j<hand.size(); j++)
            if(hand[j]->getColour()=='w')   //looks for wild cards
                isFinished=checkCard(hand[j]);
    }
    return isFinished;
}

void Player::performTurn(){
    Card* topCard=dropPile.cards.last();
    if(topCard->getNumber()==11 && topCard->isActive){ //skip turn
        topCard->isActive=0;
    }
    else{
        if(topCard->getNumber()==12 && topCard->isActive){ //draw 2
            topCard->isActive=0;
            drawCard(); drawCard();
        }
        else{
            if(topCard->getNumber()==14 && topCard->isActive){ //draw 4
                topCard->isActive=0;
                drawCard(); drawCard(); drawCard(); drawCard();
            }
            else{
                if(isPlayer){
                    redraw();
                    if(hasValidCard()){
                        while(!isDone){
                            w->delay(1);
                        }
                    }
                    else{
                        drawCard();
                        checkCard(hand.last());
                    }
                    isDone=0;
                    redraw();
                }
                else{
                    if(!chooseCard()) //is able to find a card that is legal
                        drawCard();
                    checkCard(hand.last());
                    qDebug() << name << hand.size();
                    w->delay(2);
                }
            }
        }
    }
    activePlayer+=direction;
}

void Player::redraw(){
    QPointF tmp;
    int ghetto;
    tmp.setX(beginX); tmp.setY(beginY);
    for(int i=0; i<2; i++)
        for(int j=0; j<10; j++){
            tmp.setX(beginX+skipX*j); tmp.setY(beginY+skipY*i);
            ghetto=i*10+j;
            if(ghetto<hand.size())
                hand[ghetto]->setPos(tmp);
            else i=2;
        }
}

bool Player::hasValidCard(){
    for(int i=0; i<hand.size(); i++){
        if(hand[i]->getColour()==dropPile.cards.last()->getColour() ||
                hand[i]->getNumber()==dropPile.cards.last()->getNumber() ||
                hand[i]->getColour()==dropPile.cards.last()->getWildColour())  //selected card is a valid choice
            return 1;
    }
    return 0;
}
