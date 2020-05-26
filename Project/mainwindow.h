#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "GameModel.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent=0);
    ~MainWindow();
protected:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    GameModel *game;
    GameType gameType;
    int clkRow, clkCol;
    void gmInit();
    void gminspec(int y,int x);
private slots:
    void playerChess();
    void AIChess();
    void PVPInit();
    void PVEInit();
};
#endif
