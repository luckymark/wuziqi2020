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
    if (presentRowx>=0&&presentcoly>=0&&presentRowx<=BoardLength&&presentcoly<=BoardLength)
    {
        painter.setPen(QPen(Qt::red,2,Qt::SolidLine));
        int centerx = BoardMargin+presentRowx*BoardOneSize;
        int centery = BoardMargin+presentcoly*BoardOneSize;
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
            if (Board[i][j] != 0) {
                if (Board[i][j] == Black)
                    brush.setColor(Qt::black);
                else if (Board[i][j] == White)
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
    if (game.gamesatus==PLAYING)
    {
        QPainter painter(this);
        int x = event->x();
        int y = event->y();
        if (event->button() == Qt::LeftButton) {
            if (InBoard(x, y)) {
                int px = round((double)(x - BoardMargin) / (BoardOneSize));
                int py = round((double)(y - BoardMargin) / (BoardOneSize));
                Board[px][py] = Black;
                update();
                checkIfWin(px,py,Black);
            }
        }

        if(game.gamesatus==PLAYING) {
            //AI下子
            computer.calculateScore(Board);
            computer.point = computer.findBestScore(computer.scoreTable);
            Board[computer.point.x][computer.point.y] = White;
            update();
            checkIfWin(computer.point.x,computer.point.y,White);
        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    presentRowx = (event->x()-BoardMargin)/BoardOneSize;
    presentcoly = (event->y()-BoardMargin)/BoardOneSize;
    if ((event->x()-BoardMargin)%BoardOneSize>=BoardOneSize/2){
        presentRowx+=1;
    }
    if ((event->y()-BoardMargin)%BoardOneSize>=BoardOneSize/2){
        presentcoly+=1;
    }
    update();
}

void MainWindow::initChessBoard() {
    game.gamesatus= PLAYING;
    game.winner = Nobody;
    for (int i = 0; i < BoardLength; i++)
        for (int j = 0; j < BoardLength; j++)
            Board[i][j] = 0;
}

Turns MainWindow::WhiteOrBlack() {
    if (turn % 2)
        return Black;
    else
        return White;
}

bool MainWindow::InBoard(int xx, int yy) {
    if (xx > BoardMargin + (BoardMargin-1) * BoardOneSize || xx<BoardMargin ||
        yy>BoardMargin + (BoardMargin-1) * BoardOneSize || yy < BoardMargin)
        return false;
    else
        return true;
}

void MainWindow::checkIfWin(const int i, const int j, const int obj) {
    int cntWhite,cntBlack;
    //横向搜
    for (int k =j-4 ; k <=j ; ++k) { //枚举左端点
        if (k<0)
        {
            k=0;
            continue;
        }
        cntWhite=0,cntBlack=0;
        //搜一个小条
        for (int l = k; l <=k+4 ; ++l) {
            if (l > BoardLength) break;
            if (Board[i][l] == White) cntWhite++;
            else if (Board[i][l] == Black) cntBlack++;
        }
        if (obj==White){
            if(cntWhite==5)
            {
                game.gamesatus=UNPLAYING;
                game.winner=White;
            }
        }
        else if (obj==Black){
            if(cntBlack==5)
            {
                game.gamesatus=UNPLAYING;
                game.winner=Black;
            }
        }
    }
    //纵向搜
    for (int k =i-4 ; k <=i ; ++k) {  //枚举上端点
        if (k<0)
        {
            k=0;
            continue;
        }
        //搜一个小条
        cntWhite=0,cntBlack=0;
        for (int l = k; l <=k+4 ; ++l) {
            if (l>BoardLength) break;
            if(Board[l][j]==1) cntWhite++;
            else if (Board[l][j]==-1) cntBlack++;
        }
        if (obj==White){
            if(cntWhite==5)
            {
                game.gamesatus=UNPLAYING;
                game.winner=White;
            }
        }
        else if (obj==Black){
            if(cntBlack==5)
            {
                game.gamesatus=UNPLAYING;
                game.winner=Black;
            }
        }
    }
    //主对角线搜
    for (int p=i-4,k =j-4; k <=j ; ++k,++p) { //枚举左上端点
        if (k<0||p<0) continue;
        cntWhite=0,cntBlack=0;
        for (int u = p,v=k; u <=p+4 ; u++,v++) {
            if (u>BoardLength||v>BoardLength) break;
            if(Board[u][v]==White) cntWhite++;
            else if (Board[u][v]==Black) cntBlack++;
        }
        if (obj==White){
            if(cntWhite==5)
            {
                game.gamesatus=UNPLAYING;
                game.winner=White;
            }
        }
        else if (obj==Black){
            if(cntBlack==5)
            {
                game.gamesatus=UNPLAYING;
                game.winner=Black;
            }
        }
    }
    //副对角线搜

    for (int p=i+4,k =j-4 ; k <=j ; p--,k++) { //枚举左下端点
        if (k<0||p>BoardLength) continue;
        cntWhite=0,cntBlack=0;
        for (int u=p, v=k; v<=k+4 ; u--,v++) {
            if (v>BoardLength||u<0) continue;
            if(Board[u][v]==White) cntWhite++;
            else if (Board[u][v]==Black) cntBlack++;
        }
        if (obj==White){
            if(cntWhite==5)
            {
                game.gamesatus=UNPLAYING;
                game.winner=White;
            }
        }
        else if (obj==Black){
            if(cntBlack==5)
            {
                game.gamesatus=UNPLAYING;
                game.winner=Black;
            }
        }
    }

    if (game.winner!=Nobody)
    {
        game.gamesatus=UNPLAYING;
        printWinnerInformation();
    }

}

void MainWindow::printWinnerInformation() {
//    QMessageBox msg;
//    msg.setFixedSize(400,100);
//    msg.setWindowTitle("Game Over!");
   // msg.setStyleSheet("font: 14pt;background-color:rgb(0, 0, 0)");
   //msg.setIcon(QMessageBox::Critical);
//    dialog = new QDialog(this);
//    dialog->setModal(false);
//    dialog->setFixedSize(200,100);
//    dialog.se

    if(game.winner==White)
        QMessageBox::information(NULL,"提示","You Lose");
    if (game.winner==Black)
        QMessageBox::information(NULL,"提示","You Win");
    //    dialog->show();
}


