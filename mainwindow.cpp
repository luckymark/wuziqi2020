#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "paintevents.h"
#include "mouseveents.h"
#include "check_win.h"
#include "refreshs.h"
#include "mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    player = 1;
    renshu =2;
    int i,j;
    for(i=0;i<SIZE;i++)
    {
        for(j=0;j<SIZE;j++)
        {
            a[i][j] = 0;
        }
    }
    connect(this,SIGNAL(gameover()),this,SLOT(refresh()));

}

MainWindow::~MainWindow()
{
    delete ui;

}
void MainWindow::paintEvent(QPaintEvent *);


void MainWindow::in_game(){
    if(player==1){
//        mouseReleaseEvent(QMouseEvent *e);
//        wheelEvent(QWheelEvent *event);
        this->update();
    }else{
//        int dx,dy;
//        MainWindow::AImax_search(dx,dy,4);
        this->update();
    }
//    j1 = jiance(1,0,a[x][y],x,y);
//    j2 = jiance(0,1,a[x][y],x,y);
//    j3 = jiance(1,1,a[x][y],x,y);
//    j4 = jiance(1,-1,a[x][y],x,y);
//    if(j1 ==4||j2==4||j3==4||j4==4)
//    {
//        this->update();
//        if(a[x][y] == 1)
//        {
//              QMessageBox::information(this, "Win", "Black Win!", QMessageBox::Ok);
//        }
//        if(a[x][y] == 2)
//        {
//              QMessageBox::information(this, "Win", "White Win!", QMessageBox::Ok);
//        }
//        emit gameover();
//    }
//    this->update();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e);
int MainWindow::jiance(int i, int j,int team,int x,int y);
void MainWindow::wheelEvent(QWheelEvent *event);
void MainWindow::refresh();

























