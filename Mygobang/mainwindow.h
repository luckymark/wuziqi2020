//
// Created by 彭琳峰 on 2020/4/21.
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
#include <QMouseEvent>

const int BoardMargin = 100;
const int BoardOneSize = 40;
const int BoardLength = 15;

enum Turns {		//枚举类型，默认人是白棋，白棋在棋盘上设为1，黑棋为-1
    White = 1, Black = -1
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

private:
    Ui::MainWindow *ui;
    int turn;//
    int Board[BoardLength][BoardLength];
    int presentRowx,presentcoly;
    bool InBoard(int xx, int yy){
        if (xx > BoardMargin + (BoardMargin-1) * BoardOneSize || xx<BoardMargin ||
            yy>BoardMargin + (BoardMargin-1) * BoardOneSize || yy < BoardMargin)
            return false;
        else
            return true;
    }
    Turns WhiteOrBlack(){
        if (turn % 2)
            return Black;
        else
            return White;
    }
};
