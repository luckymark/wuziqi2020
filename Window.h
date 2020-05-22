#ifndef WUZIQI2020_WINDOW_H
#define WUZIQI2020_WINDOW_H

#include <QMainWindow>
#include "Game.h"

class Window : public QMainWindow {
    Q_OBJECT
public:
    explicit Window(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    Game game;
    int clickPosRow {-1};
    int clickPosCol {-1};
//    void checkGame(int y, int x);
};


#endif //WUZIQI2020_WINDOW_H
