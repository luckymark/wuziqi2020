//
// Created by 彭琳峰 on 2020/4/21.
//
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "AI.h"
#include<QApplication>
#include <QMouseEvent>
#include <iostream>
#include <QDialog>
#define INF 0x7ffffff

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(750,750);
    setWindowTitle("阿峰的五子棋");
    //设置追踪鼠标
    setMouseTracking(true);
    ui->centralWidget->setMouseTracking(true);
    initChessBoard();
}
void MainWindow::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    this->setAutoFillBackground(true);
    QPalette palette ;
    palette.setColor(QPalette::Background,QColor("#B1723C"));
    this->setPalette(palette);

    //画棋盘
    for (int i = 0; i < BoardLength; i++)
    {
        painter.drawLine(BoardMargin+BoardOneSize*i, BoardMargin, BoardMargin+BoardOneSize*i, BoardMargin+(BoardLength-1)*BoardOneSize);
        painter.drawLine(BoardMargin, BoardMargin+BoardOneSize*i, BoardMargin+(BoardLength-1)*BoardOneSize, BoardMargin+BoardOneSize*i);
    }
    //画棋盘里的小黑点
    QBrush brush;
    painter.setBrush(QBrush(Qt::black,Qt::SolidPattern));
    painter.drawRect(BoardMargin+3*BoardOneSize-5,BoardMargin+3*BoardOneSize-5,10,10);
    painter.drawRect(BoardMargin+11*BoardOneSize-5,BoardMargin+3*BoardOneSize-5,10,10);
    painter.drawRect(BoardMargin+11*BoardOneSize-5,BoardMargin+11*BoardOneSize-5,10,10);
    painter.drawRect(BoardMargin+3*BoardOneSize-5,BoardMargin+11*BoardOneSize-5,10,10);
    painter.drawRect(BoardMargin+7*BoardOneSize-5,BoardMargin+7*BoardOneSize-5,10,10);
    //画红方框
    if (presentRowy>=0&&presentcolx>=0&&presentRowy<=BoardLength&&presentcolx<=BoardLength)
    {
        painter.setPen(QPen(Qt::red,2,Qt::SolidLine));
        int centerx = BoardMargin+presentRowy*BoardOneSize;
        int centery = BoardMargin+presentcolx*BoardOneSize;
        painter.drawLine(centerx-20,centery-20,centerx-10,centery-20);
        painter.drawLine(centerx+10,centery-20,centerx+20,centery-20);
        painter.drawLine(centerx-20,centery-20,centerx-20,centery-10);
        painter.drawLine(centerx-20,centery+10,centerx-20,centery+20);
        painter.drawLine(centerx-20,centery+20,centerx-10,centery+20);
        painter.drawLine(centerx+20,centery+20,centerx+10,centery+20);
        painter.drawLine(centerx+20,centery+20,centerx+20,centery+10);
        painter.drawLine(centerx+20,centery-10,centerx+20,centery-20);
    }

    //画棋子(去掉pen,避免画出边框）
    // painter.setPen(QPen(Qt::black,1,Qt::SolidLine));
   painter.setPen(Qt::NoPen);
    for (int i = 0; i < BoardLength; i++) {
        for (int j = 0; j < BoardLength; j++) {
            if (board[i][j] != 0) {
                if (board[i][j] == Black)
                    brush.setColor(Qt::black);
                else if (board[i][j] == White)
                    brush.setColor(Qt::white);
                brush.setStyle(Qt::SolidPattern);
                painter.setBrush(brush);
                painter.drawEllipse(i*BoardOneSize + BoardMargin - 15, j * BoardOneSize + BoardMargin - 15, 30, 30);
            }
        }
    }
    painter.end();
}

void MainWindow::mousePressEvent(QMouseEvent* event)
{
    if (game.gamesatus==PLAYING) {
        int x = event->x();
        int y = event->y();
        if (event->button() == Qt::LeftButton) {
            int px = (x - BoardMargin) / BoardOneSize;
            if ((x - BoardMargin) % BoardOneSize >= BoardOneSize / 2) px++;
            int py = (y - BoardMargin) / BoardOneSize;
            if ((y - BoardMargin) % BoardOneSize >= BoardOneSize / 2) py++;

            if (px >= 0 && py >= 0 && px <= BoardLength && py <= BoardLength &&board[px][py]==Nobody)
            {
                board[px][py]=Black;
                if (computer.evaluate(board).winner == Nobody){//黑方下棋后仍未分出胜负
                    computer.abSearch(board,0,-INF,INF);
                    board[computer.decison.pos.x()][computer.decison.pos.y()]=White;
                    if (computer.evaluate(board).winner==White)
                    {
                        game.gamesatus = UNPLAYING;
                        game.winner = White;
                        printWinnerInformation();
                    }

                }else{//此时说明黑方已经获胜
                    game.gamesatus=UNPLAYING;
                    game.winner = Black;
                    printWinnerInformation();
                }




            }
        }
    }

}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    presentRowy= (event->x()-BoardMargin)/BoardOneSize;
    presentcolx = (event->y()-BoardMargin)/BoardOneSize;
    if ((event->x()-BoardMargin)%BoardOneSize>=BoardOneSize/2){
        presentRowy+=1;
    }
    if ((event->y()-BoardMargin)%BoardOneSize>=BoardOneSize/2){
        presentcolx+=1;
    }
    update();
}

void MainWindow::initChessBoard() {
    game.gamesatus= PLAYING;
    game.winner = Nobody;
    for (int i = 0; i < BoardLength; i++)
        for (int j = 0; j < BoardLength; j++)
            board[i][j] = 0;
}





void MainWindow::printWinnerInformation() {

    if(game.winner==White)
        QMessageBox::information(NULL,"提示","You Lose");
    if (game.winner==Black)
        QMessageBox::information(NULL,"提示","You Win");
    //    dialog->show();
}


