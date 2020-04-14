//
// Created by hw730 on 2020/4/9.
//

#ifndef CHESSFINAL_BOARD_H
#define CHESSFINAL_BOARD_H

#include"chessglobalconst.h"
#include <QtWidgets/QWidget>

struct boardStatus{
    ll status,score;
};
struct Points{
    int x,y;
};

struct decision{
    Points pos[MAX_CHOICE];
    ll score[MAX_CHOICE];
};

class Board : public QWidget
        {
    Q_OBJECT
public:
            explicit Board (QWidget *parent = nullptr);

    int R = 0,R1 = 0;
    QPoint q[CHESS_HEIGHT * CHESS_LENGTH];
    QPoint q1[CHESS_HEIGHT * CHESS_LENGTH];
    int col[CHESS_HEIGHT * CHESS_LENGTH];

    int board[CHESS_HEIGHT][CHESS_LENGTH];
    ll chess_6_type[4][4][4][4][4][4];
    int dir[8][2] = {{0,1},{1,0},{1,1},{1,-1},{-1,0},{0,-1},
                     {-1,1},{-1,-1}};
    int TURN = 0;//0 player 1 computer
    int status = 0;//0 unknown 1 player win 2 computer win
    Points AIStep;

    QPushButton* _button;


    //board
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    QPoint getChesspiece(QPoint);


    //AI
    void AI(int (&board)[CHESS_HEIGHT][CHESS_LENGTH]);
    ll alphaBetaSearch(int (&board)[CHESS_HEIGHT][CHESS_LENGTH], int depth, ll alpha, ll beta);
    decision findPoints(int (&board)[CHESS_HEIGHT][CHESS_LENGTH]);
    bool judgePoints(int x,int y);
    boardStatus evaluateBoard(int (&board)[CHESS_HEIGHT][CHESS_LENGTH]);
    void copychess(int (&board)[CHESS_HEIGHT][CHESS_LENGTH],int (&sameBoard)[CHESS_HEIGHT][CHESS_LENGTH]);
    void revBoard(int (&board)[CHESS_HEIGHT][CHESS_LENGTH],int (&reverseBoard)[CHESS_HEIGHT][CHESS_LENGTH]);
    bool judgeChessBoardStatus(int (&board)[CHESS_HEIGHT][CHESS_LENGTH]);

    //chess_type
    void init_Chess_6_Type();

    //button
    void setButton();
    void reload();
    signals:
        public slots:

};


#endif //CHESSFINAL_BOARD_H
