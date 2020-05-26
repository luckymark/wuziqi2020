#include <QPainter>
#include <QTimer>
#include <QMenuBar>
#include <QSound>
#include <QDebug>
#include <QMouseEvent>
#include <QMenu>
#include <QMessageBox>
#include <QAction>
#include <math.h>
#include "mainwindow.h"
#define CHESS_SOUND ":/res/sound/chessone.wav"
#define VCTY_SOUND ":/res/sound/win.wav"
#define DEFT_SOUND ":/res/sound/lose.wav"
const int brdMrg=30;                     // 棋盘相关设定
const int rad=15;
const int mkSz=6;
const int blkSz=40;
const int psDlt=20;
const int AIThk=800;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(brdMrg*2+blkSz*brdSz,brdMrg*2+blkSz*brdSz);
    setStyleSheet("background-color:khaki;");
    setMouseTracking(true);
    QMenu *gMenu=menuBar()->addMenu(tr("Game"));
    QAction *actionPVP=new QAction("Person VS Person",this);
    connect(actionPVP,SIGNAL(triggered()),this,SLOT(PVPInit()));
    gMenu->addAction(actionPVP);
    QAction *actPVE=new QAction("Person VS Computer",this);
    connect(actPVE,SIGNAL(triggered()),this,SLOT(PVEInit()));
    gMenu->addAction(actPVE);
    gmInit();
}
MainWindow::~MainWindow()
{
    if (game){
        delete game;
        game=nullptr;
    }
}
void MainWindow::gmInit()
{   
    game=new GameModel;                // 初始化游戏
    PVPInit();
}
void MainWindow::PVPInit()
{
    gameType=PERSON;
    game->gameStat=GAMING;
    game->startGame(gameType);
    update();
}
void MainWindow::PVEInit()
{
    gameType=BOT;
    game->gameStat=GAMING;
    game->startGame(gameType);
    update();
}
void MainWindow::paintEvent(QPaintEvent *event)                // 棋盘绘制相关
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    QPen pen;
    pen.setWidth(2);
    painter.setPen(pen);
    for(int i=0;i<brdSz+1;i++){
        painter.drawLine(brdMrg+blkSz*i,brdMrg,brdMrg+blkSz*i,size().height()-brdMrg);
        painter.drawLine(brdMrg,brdMrg+blkSz*i,size().width()-brdMrg,brdMrg+blkSz*i);
    }
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    if(clkRow>0&&clkRow<brdSz&&clkCol>0&&clkCol<brdSz&&game->gmVc[clkRow][clkCol]==0){
        if(game->plOpt)
            brush.setColor(Qt::black);
        else
            brush.setColor(Qt::white);
        painter.setBrush(brush);
        painter.drawRect(brdMrg+blkSz*clkCol-mkSz/2,brdMrg+blkSz*clkRow-mkSz/2,mkSz,mkSz);
    }
    for(int i=0;i<brdSz;i++)
        for(int j=0;j<brdSz;j++){
            if(game->gmVc[i][j]==1){
                brush.setColor(Qt::black);
                painter.setBrush(brush);
                painter.drawEllipse(brdMrg+blkSz*j-rad,brdMrg+blkSz*i-rad,rad*2,rad*2);
            }
            else if(game->gmVc[i][j]==-1)
            {
                brush.setColor(Qt::white);
                painter.setBrush(brush);
                painter.drawEllipse(brdMrg+blkSz*j-rad,brdMrg+blkSz*i-rad,rad*2,rad*2);
            }
        }
    if(clkRow>0&&clkRow<brdSz&&clkCol>0&&clkCol<brdSz&&(game->gmVc[clkRow][clkCol]==1||game->gmVc[clkRow][clkCol]==-1)){
        if(game->isWin(clkRow,clkCol)&&game->gameStat==GAMING){
            qDebug()<<"win";
            game->gameStat=WIN;
            QSound::play(VCTY_SOUND);
            QString str;
            if(game->gmVc[clkRow][clkCol]==1)
                str="Black player";
            else if(game->gmVc[clkRow][clkCol]==-1)
                str="White player";
            QMessageBox::StandardButton btnValue=QMessageBox::information(this,"congratulations",str+" win!");
            if(btnValue==QMessageBox::Ok){
                game->startGame(gameType);
                game->gameStat=GAMING;
            }
        }
    }
    if(game->isDead()){                            // 判断僵局
        QSound::play(DEFT_SOUND);
        QMessageBox::StandardButton btnValue=QMessageBox::information(this,"oops","dead game!");
        if (btnValue==QMessageBox::Ok){
            game->startGame(gameType);
            game->gameStat=GAMING;
        }

    }
}
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{   
    int x=event->x();
    int y=event->y();
    if(x>=brdMrg+blkSz/2&&x<size().width()-brdMrg&&y>=brdMrg+blkSz/2&&y<size().height()-brdMrg){
        int col=x/blkSz;
        int row=y/blkSz;
        int leftPosX=brdMrg+blkSz*col;
        int leftPosY=brdMrg+blkSz*row;
        clkRow=-1;
        clkCol=-1;
        int length=0;
        length=sqrt((x-leftPosX)*(x-leftPosX)+(y-leftPosY)*(y-leftPosY));
        if(length<psDlt){
           clkRow=row;
           clkCol=col;
        }
        length=sqrt((x-leftPosX-blkSz)*(x-leftPosX-blkSz)+(y-leftPosY)*(y-leftPosY));
        if(length<psDlt){
            clkRow=row;
            clkCol=col+1;
        }
        length=sqrt((x-leftPosX)*(x-leftPosX)+(y-leftPosY-blkSz)*(y-leftPosY-blkSz));
        if(length<psDlt){
           clkRow=row+1;
           clkCol=col;
        }
        length=sqrt((x-leftPosX-blkSz)*(x-leftPosX-blkSz)+(y-leftPosY-blkSz)*(y-leftPosY-blkSz));
        if(length<psDlt){
           clkRow=row+1;
           clkCol=col+1;
        }
    }
    update();
}
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(!(gameType==BOT&&!game->plOpt)){
        playerChess();
        if(game->gameType==BOT&&!game->plOpt){
           QTimer::singleShot(AIThk,this,SLOT(AIChess()));
        }
    }

}
void MainWindow::playerChess()                                // 落子
{
    if(clkRow!=-1&&clkCol!=-1&&game->gmVc[clkRow][clkCol]==0){
        game->PlayerAct(clkRow,clkCol);
        QSound::play(CHESS_SOUND);
        update();
    }
}
void MainWindow::AIChess()
{
    game->AIAct(clkRow,clkCol);
    QSound::play(CHESS_SOUND);
    update();
}
