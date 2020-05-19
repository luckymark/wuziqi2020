//
// Created by ≈Ì¡’∑Â on 2020/4/21.
//

#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include<QPushButton>
#include<QLabel>
#include<QPainter>
#include<QMouseEvent>
#include<QPoint>
#include<cmath>
#include <QMainWindow>
#include<qmessagebox.h>
#include <QMouseEvent>
#include <QDialog>
#include "AI.h"

#define PLAYING 1
#define UNPLAYING 0
const int BoardMargin = 100;
const int BoardOneSize = 40;
const int BoardLength = 15;

struct GAME{
    int gamesatus;
    int winner;
};


namespace Ui {
    class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

    signals:

public slots:
    void printWinnerInformation();

private:
    Ui::MainWindow *ui;
    QDialog *dialog;
    AI computer;
    GAME game;
    int board[BoardLength][BoardLength];
    int presentRowy,presentcolx;
    //∫Ø ˝
    void initChessBoard();
    void checkIfWin(const int i, const int j,const int obj);
};
