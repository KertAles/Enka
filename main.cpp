#include "mainwindow.h"
#include "deck.h"
#include <QApplication>

MainWindow *w;
Deck drawPile, dropPile;
int direction, activePlayer; //+-1

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    w=new MainWindow;
    w->show();

    w->startGame();

    return a.exec();
}
