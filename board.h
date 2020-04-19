//
// Created by hw730 on 2020/4/19.
//

#ifndef CHESSAIUPD_BOARD_H
#define CHESSAIUPD_BOARD_H



#include"chessglobalconst.h"
#include"chesslib.h"
#include"chessglobalvariable.h"
#include"chessstruct.h"
#include"alphabeta.h"
#include <QtWidgets/QWidget>

class Board : public QWidget
{
Q_OBJECT
public:
    explicit Board (QWidget *parent = nullptr);
//    int TURN = 0;//0 player 1 computer
    int status = 0;//0 unknown 1 player win 2 computer win
    Points AIStep;
    QPushButton* _button;
    //board
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    QPoint getChesspiece(QPoint);
    //button
    void setButton();
    void reload();
signals:
public slots:

};


#endif //CHESSAIUPD_BOARD_H
