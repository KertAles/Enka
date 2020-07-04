#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "card.h"
#include "deck.h"

#include <ctime>
#include <cstdlib>
#include <QMessageBox>
#include <QDebug>
#include <QVector>
#include <QTime>

#define dropX 300
#define dropY 150

extern MainWindow *w;
extern Deck drawPile, dropPile;
extern int direction, activePlayer;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    srand(time(NULL));

    scene=new QGraphicsScene(this);
    scene->setSceneRect(ui->graphicsView->rect());
    ui->graphicsView->setScene(scene);
}

void MainWindow::init(){
    drawPile.fillDeck();
    dropPile.cards.push_back(drawPile.cards.last());
    drawPile.cards.remove(drawPile.cards.size()-1);
    direction=1;
    activePlayer=0;

    for(int i=0;i<4; i++) //makes players
        players[i] = new Player(i);
    dropPile.cards.last()->setPos(dropX,dropY);

    if(dropPile.cards.last()->getColour()=='w'){
        int randColour=rand()%4;
        switch(randColour){
        case 0: dropPile.cards.last()->setWildColour('r'); break;
        case 1: dropPile.cards.last()->setWildColour('b'); break;
        case 2: dropPile.cards.last()->setWildColour('g'); break;
        case 3: dropPile.cards.last()->setWildColour('y'); break;
        }
    }

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
    colour.setPixmap(QPixmap(tmp).scaled(30,30));
            int neki=dropPile.cards.last()->getNumber();
    tmp=QString::number(neki,10);

    tmp=":/slike/carte/"+tmp+".png";
    number.setPixmap(QPixmap(tmp).scaled(30,30));

    QPointF point;
    point.setX(dropX+100);
    point.setY(dropY);
    colour.setPos(point);
    point.setY(dropY+40);
    number.setPos(point);

    w->scene->addItem(&colour);
    w->scene->addItem(&number);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
    for(int i=0; i<4; i++)
        delete players[i];
}

void MainWindow::closeEvent(QCloseEvent *q){
    delete w;
}

void MainWindow::victory(Player *winner){
    QMessageBox::question(w,"Konec igre","Igra se je koncala, zmagal je "+ winner->name,QMessageBox::Ok);
    w->close();
}

void MainWindow::startGame(){
    init();
    int transform;
    while(1){//runs until someone wins
        transform=abs(activePlayer%4);
        players[transform]->performTurn();
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    //QGraphicsView::mousePressEvent(event);
}

void MainWindow::delay(int n)
{
    QTime dieTime= QTime::currentTime().addSecs(n);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

