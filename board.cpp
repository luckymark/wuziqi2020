//
// Created by hw730 on 2020/4/19.
//

#include "board.h"
//
// Created by hw730 on 2020/4/9.
//


Board::Board(QWidget *parent) : QWidget(parent)
{
    _button = new QPushButton(this);
    _button->show();
    memset(board,0,sizeof(board));
//    board[4][4] = board[5][4] = board[6][4] = C_BLACK;
//    board[7][4] = board[3][4] = board[1][1] = C_WHITE;
//    R1 = R = 6;
//    q1[1] = q[1] = QPoint(4,4);col[1] = col[3] = col[5] = 2;
//    q1[2] = q[2] = QPoint(7,4);
//    q1[3] = q[3] = QPoint(5,4);
//    q1[4] = q[4] = QPoint(3,4);
//    q1[5] = q[5] = QPoint(6,4);
//    q1[6] = q[6] = QPoint(1,1);
}

void Board::paintEvent(QPaintEvent *)
{
    bool flag = false;
    QPainter painter(this);
//    painter.drawLine(QPoint(PAINT_X, PAINT_Y),QPoint(PAINT_X + CHESS_LENGTH, PAINT_Y));
//    painter.drawLine(QPoint(PAINT_X, PAINT_Y),QPoint(PAINT_X, PAINT_Y+ CHESS_HEIGHT));
    for(int i = 1;i < CHESS_LENGTH - 1;i++)
    {
        painter.drawLine(QPoint(PAINT_X + (i - 1) * DISTANCE,PAINT_Y),QPoint(PAINT_X + (i - 1) * DISTANCE,PAINT_Y + SHOW_CHESS_HEIGHT));
    }
    for(int i = 1;i < CHESS_HEIGHT - 1;i++)/*画横线*/
    {
        painter.drawLine(QPoint(PAINT_X,PAINT_Y + (i - 1) * DISTANCE),QPoint(PAINT_X + SHOW_CHESS_LENGTH,PAINT_Y + (i - 1) * DISTANCE));
    }
    for(int i = 1;i <= R1;i++)
    {
        if(col[i] == 2)
        {
            painter.setBrush(QBrush(QColor(0,0,0)));
        }
        else if(col[i] == 1)
        {
            painter.setBrush(QBrush(QColor(100,0,0)));
            flag = true;
            col[i] = 0;
        }
        else
        {
            painter.setBrush(QBrush(QColor(255,255,255)));
        }
        painter.drawEllipse(QPoint((q1[i].y() - 1) * DISTANCE + PAINT_X,(q1[i].x() - 1) * DISTANCE + PAINT_Y),ROUND,ROUND);
    }
    QRect rect = QRect(QPoint(TOP_X,TOP_Y),QPoint(BOTTOM_X,BOTTOM_Y));
    if(status == 1)
    {
        painter.drawText(rect,QString("You Lose"),QTextOption(Qt::AlignHCenter));
    }
    else if(status == 2)
    {
        painter.drawText(rect,QString("You Win"),QTextOption(Qt::AlignHCenter));
    }
}

QPoint Board::getChesspiece(QPoint pos)
{
    QPoint ans(0,0);
    for(int i = 1;i < CHESS_HEIGHT - 1;i++)
    {
        for(int j = 1;j < CHESS_LENGTH - 1;j++)
        {
            if(abs((i - 1) * DISTANCE + PAINT_Y - pos.y()) <= RES && abs((j - 1) * DISTANCE + PAINT_X - pos.x()) <= RES)
            {
                ans = QPoint(i,j);
                return ans;
            }
        }
    }
    return ans;
}

void Board::mousePressEvent(QMouseEvent *event)
{
    QPoint pos = event->pos();
    QPoint pos_board = getChesspiece(pos);
    if(pos.x() <= BUTTON_W && pos.y() <= BUTTON_H)
    {
        reload();
        return;
    }
    else if(R1 % 2 == 0 && status == 0 && pos_board.x() != 0 && pos_board.y() != 0 && board[pos_board.x()][pos_board.y()] == C_NONE)
    {
        q[++R] = QPoint(pos_board.x(),pos_board.y());
        q1[++R1] = q[R];
        col[R1] = 2;
        board[pos_board.x()][pos_board.y()] = C_BLACK;
        Hash ^= zob[pos_board.x()][pos_board.y()][C_BLACK - 1];
        status =  evaluateBoard(board,Hash).status;
        repaint();
        if(status == 0)
        {
            AI(board);
            col[R1] = 1;
            status = evaluateBoard(board,Hash).status;
            repaint();
            Sleep(SHINING_TIME);
            repaint();
        }
    }
}

void Board::setButton()
{
    _button->setText(QString("右键重新开始"));
    _button->resize(100,100);
}

void Board::reload()
{
    status = R = R1 = 0;
    memset(board,0,sizeof(board));
    update();
}
