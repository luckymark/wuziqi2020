#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QTimer>
#include"utility.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Evaluator;
class GoBang : public QWidget
{
	Q_OBJECT


public:
    GoBang(QWidget* parent = nullptr);
    ~GoBang();

    void initFunc();

    void initGUI();
    void setAlignment();    //主要是窗口居中

    void respond(); //响应用户输入
    void getPos(int& posI, int& posJ);  //获得AI计算的坐标

	void gameOver(int status);
    void restart();

    void paintEvent(QPaintEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    //paintEvent和mouseMoveEvent用于绘图
    //mouseReleaseEvent用于捕捉用户输入

private:
    Ui::Widget* ui;
	Evaluator* evaluator;

    int chess[NUMBER][NUMBER];
    int moveI, moveJ;   //鼠标目前的坐标（按行列计算）
    int currentI = -1, currentJ = -1;   //上一次下子坐标
	QTimer timer;
	int seconds = 0, counter = 0,steps=0;
    //计时器，总子数，我方子数
	friend Evaluator;
};
#endif // WIDGET_H
