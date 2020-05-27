#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Evaluator;
class Widget : public QWidget
{
	Q_OBJECT


public:
	Widget(QWidget* parent = nullptr);
	void paintEvent(QPaintEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
    void initFunc();
    void initGUI();
	void centralize();
	void gameOver(int status);
	void stone();
	void react();
	void Widget::getPos(int& bi, int& bj);
	~Widget();

private:
	Evaluator* evaluator;
	Ui::Widget* ui;
	int chess[15][15];
	int moveX, moveY;
	int currentX = -1, currentY = -1;
	QTimer timer;
	int seconds = 0, counter = 0,steps=0;

	friend Evaluator;
};
#endif // WIDGET_H
