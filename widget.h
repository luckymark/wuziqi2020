#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "ui_widget.h"
#include "ai.h"
#include "time.h"
#include <stdio.h>
#include <stdlib.h>
#include <QtGlobal>
#include <QTime>
#include <QPainter> //画家类
#include <QResizeEvent>
#include <QDebug>
#include <QPushButton>

#define GRIDCOUNT 15
#define INF 99999999

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);

    ~Widget();
protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    Ui::Widget *ui;
    QString bgFilename,black,white;
    QColor LineColor;
    Qt::PenStyle LineStyle;
    int Map[GRIDCOUNT][GRIDCOUNT];//1black 2white 0blank
    int LineWidth;
    int gridlength,startx,starty,sidelength;
    int flag;//1为先手 2为后手
    int isstarted;//是否开始

    void Init();//初始化背景及line
    void start1();
    void start2();
    void restart();
    void AI();
    void DFS(int layer);
    int xx,yy,max1,max2,max3,max4,max5,greater,v,v2,v3,v4,vv[5],vmax[5];
    int win;
    int value(int type);//评估函数
    bool isempty(int x,int y);
    void foo(int i,int j,const int type,int &count,int &val,int &die);
};
#endif // WIDGET_H
