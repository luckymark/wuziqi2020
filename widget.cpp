#include "widget.h"
#include "ui_widget.h"
#include "time.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <QtGlobal>
#include <QTime>
#include <QPainter> //画家类
#include <QResizeEvent>
#include <QDebug>
#include <QPushButton>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    Init();

    QPushButton *btn=new QPushButton("先手",this);
    btn->move(190,745);
    btn->resize(100,50);
    QPushButton *btn2=new QPushButton("后手",this);
    btn2->move(500,745);
    btn2->resize(100,50);
    QPushButton *btn3=new QPushButton("重来",this);
    btn3->move(350,765);
    btn3->resize(90,40);
    connect(btn,&QPushButton::clicked,this,&Widget::start1);
    connect(btn2,&QPushButton::clicked,this,&Widget::start2);
    connect(btn3,&QPushButton::clicked,this,&Widget::restart);
}

void Widget::paintEvent(QPaintEvent *){
    QPainter painter(this);
    setFixedSize(800,850);
    setWindowTitle("Chess-Gobang");
    //背景颜色 蓝色（135,206,250）  粉色（255,182,193）  紫色（238,130,238）
    QBrush brush(QColor(135,206,250));
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    painter.drawRect(0,0,size().width(),size().height());
    //画棋盘
    QPen pen;
    pen.setColor(LineColor);
    pen.setStyle(LineStyle);
    pen.setWidth(LineWidth);
    painter.setPen(pen);
    for(int i=0;i<GRIDCOUNT;i++){
        painter.drawLine(startx,starty+i*gridlength,startx+sidelength,starty+i*gridlength);
        painter.drawLine(startx+i*gridlength,starty,startx+i*gridlength,starty+sidelength);
    }
    //画棋子
    for(int i=0;i<GRIDCOUNT;i++){
        for(int j=0;j<GRIDCOUNT;j++){
            if(Map[i][j]){
                QString checker= Map[i][j]==1? black:white;
                QRect rect(QPoint(startx+(i-0.4)*gridlength,starty+(j-0.4)*gridlength),QPoint(startx+(i+0.4)*gridlength,starty+(j+0.4)*gridlength));
                QPixmap pix(checker);
                painter.drawPixmap(rect,pix);
            }
        }
    }
}
void Widget::resizeEvent(QResizeEvent *event){
    sidelength=event->size().width()<event->size().height()? event->size().width():event->size().height();
    gridlength=sidelength/(GRIDCOUNT+3);
    sidelength=(GRIDCOUNT-1)*gridlength;
    startx=2*gridlength;
    starty=2*gridlength;
}
void Widget::mousePressEvent(QMouseEvent *event){
    int a=event->x();
    int b=event->y();
    if(isstarted&&!win&&a>=startx-gridlength/2&&a<=startx+sidelength+gridlength/2&&b>=starty-gridlength/2&&b<=starty+sidelength+gridlength/2){
        int x=(a-startx+gridlength/2)/gridlength;
        int y=(b-starty+gridlength/2)/gridlength;
        //qDebug()<<x<<" "<<y<<endl;
        if(Map[x][y]==0){
            Map[x][y]=flag;
            update();
            value(flag);
            if(win) {
                QPushButton *btn= new QPushButton;
                btn->resize(400,100);
                btn->setText("呜呜呜呜呜呜呜呜呜呜呜呜呜呜 你欺负我（x）");
                btn->show();
            }else{
                AI();
                value(3-flag);
                if(win) {
                    QPushButton *btn= new QPushButton;
                    btn->resize(400,100);
                    btn->setText("哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈你输了！");
                    btn->show();
                }
            }

        }
    }
}

void Widget::start1(){
    if(isstarted==0){
        win=0;
        isstarted=1;
        flag=1;
    }
}
void Widget::start2(){
    if(isstarted==0){
        isstarted=1;
        flag=2;
        Map[7][7]=1;
        update();
        win=0;
    }
}
void Widget::restart(){
    isstarted=0;
    win=0;
    memset(Map,0,sizeof(Map));
    this->update();
}
void Widget::Init(){
    LineColor=Qt::black;
    LineStyle=Qt::SolidLine;
    LineWidth=3;
    black=":/image/b.png";
    white=":/image/w.png";
    flag=1;
    isstarted=0;
    memset(Map,0,sizeof(Map));
    win=0;
}
Widget::~Widget()
{
    delete ui;
}

void Widget::AI(){
    int layer=1; //层数
    max1=-INF;max2=0;
    DFS(layer);
    Map[xx][yy]=3-flag;
//    int val=value(1);
//    int val2=value(2);
//    qDebug()<<"black"<<val<<" white"<<val2<<endl;
    update();
}

void Widget::DFS(int layer){
    if(layer==3){
        v=value(flag);
        if(v>max2) max2=v;
        return;
    }
    max2=0;
    for(int i=0;i<GRIDCOUNT;i++){
        for(int j=0;j<GRIDCOUNT;j++){
            if(isempty(i,j)){
                Map[i][j]= layer%2? 3-flag:flag;
                if(layer==1){
                    v2=value(3-flag);
                    if(win==1){
                        xx=i;yy=j; return;
                    }
                }
                DFS(layer+1);
                if(greater==1){
                    greater=0;xx=i;yy=j;
                }
                Map[i][j]=0;
                //if(v2-max2<max1&&cen==2) return;
            }
        }
    }
    /*if(cen==4){
        if(max4<max3) max3=max4;
    }if(cen==3){
        if(max3>max2) max2=max3;
    }*/
    if(layer==2){
        v2-=max2;//biger
        if(v2>max1) {max1=v2;greater=1;}
        if(v2==max1) { int temp=rand()%3;if(!temp) greater=1; }
    }
    return;
}

bool Widget::isempty(int x,int y){ //方圆5*5内是否有棋
    if(!Map[x][y]){
        for(int i=-2;i<3;i++){
            for(int j=-2;j<3;j++){
                if(x+i<GRIDCOUNT&&x+i>=0&&y+j<GRIDCOUNT&&y+j>=0)
                    if(Map[x+i][y+j]) return true;
            }
        }
    }return false;
}

int Widget::value(int type){
    win=0;
    int val=0;  //type为1为评估黑棋，2为评估白棋
    int die,die2,count,count2,die3,die4,count3,count4;  //1为死 0为活
    for(int i=0;i<GRIDCOUNT;i++){//横竖
        die=1,die2=1,count=0,count2=0;
        for(int j=0;j<GRIDCOUNT;j++){
            foo(i,j,type,count,val,die);
            foo(j,i,type,count2,val,die2);
        }
    }
    for(int i=0;i<GRIDCOUNT;i++){//斜线
        die=1,die2=1,count=0,count2=0;
        die3=1,die4=1,count3=0,count4=0;
        for(int j=0;j+i<GRIDCOUNT;j++){
            foo(j,j+i,type,count,val,die);
            if(i!=0) foo(j+i,j,type,count2,val,die2);
            foo(14-j-i,j,type,count3,val,die3);
            if(i!=0) foo(14-j,j+i,type,count4,val,die4);
        }
   }
    return val;
}
void Widget::foo(int i,int j,const int type,int &count,int &val,int &die){
    if(Map[i][j]==type) count++;
    else if(Map[i][j]==3-type){
        if(!die&&count){
            count--;
            val+=pow(10,count);
        }
        die=1;
        count=0;
    }else if(Map[i][j]==0){
        if(count){
            if(die) count--;
            val+=pow(10,count);
        }
        die=0;
        count=0;
    }if(count==5){
        val+=99999;
        win=1;
    }
}
