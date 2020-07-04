#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QGraphicsScene>

#include "deck.h"
#include "player.h"
#include "icon.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    Player* players[4];
    icon colour, number;

    void delay(int n);
    void mousePressEvent(QMouseEvent* event);
    void startGame();
    void init();
    void victory(Player *winner);

private slots:

private:
    void closeEvent(QCloseEvent *q);
};

#endif // MAINWINDOW_H
