#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <bits/stdc++.h>
#include <QMainWindow>
#include<QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void in_game();
    void paintEvent(QPaintEvent *);         //绘图，格子间距
    void mouseReleaseEvent(QMouseEvent *);  //鼠标事件
    bool checks(int d_x,int d_y);       //AI检查在即将落子9*9周围是否有棋子
    void genarator_point(std::vector <std::pair<int,int> > &v);//产生分并且记录
    int score_table(int number,int emptys); //积分规则
    int count_score(std::vector <int> v_v,int turn);     //计算分数
    int evaluate_minmax();
    int min_search(int depths,int beta);
    int max_search(int depths,int alpha);
    void AImax_search(int &xxx,int &yyy,int depth);
    int jiance(int i,int j,int team,int x,int y);
    void wheelEvent(QWheelEvent *event);
    const int SIZE=15;
    const int WIDTH=40;           //格子间距
    const int x_o=50,y_o=50;
    int renshu;
    int player;
signals:
    void gameover();
public slots:
    void refresh();

private:
    Ui::MainWindow *ui;
    int a[15][15];


};

#endif // MAINWINDOW_H
