#pragma GCC optimize(3)
#pragma G++ optimize(3)

#include<QDebug>
#include<QDesktopWidget>
#include<QMessageBox>
#include<QPainter>
#include<QMouseEvent>
#include<QIcon>

#include<queue>

#include "widget.h"
#include "ui_widget.h"
#include"utility.h"
#include"def.h"
#include"evaluator.h"

Widget::Widget(QWidget* parent)
	: QWidget(parent)
	, ui(new Ui::Widget)
{
	ui->setupUi(this);
    initGUI();
    initFunc();
}
void Widget::paintEvent(QPaintEvent*) {

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);

	QPen pen = painter.pen();
	pen.setColor(QColor("#8D5822"));
	pen.setWidth(7);
	painter.setPen(pen);


	QBrush brush;
	brush.setColor(QColor("#EEC085"));
	brush.setStyle(Qt::SolidPattern);
	painter.setBrush(brush);
	painter.drawRect(20, 40, 600, 600);

	pen.setColor(Qt::black);
	pen.setWidth(1);
	painter.setPen(pen);
	for (int i = 0; i < NUMBER; ++i) {
		painter.drawLine(40 + i * 40, 60, 40 + i * 40, 620);
		painter.drawLine(40, 60 + i * 40, 600, 60 + i * 40);
	}
	brush.setColor(Qt::black);
	painter.setBrush(brush);
	painter.drawRect(155, 175, 10, 10);
	painter.drawRect(475, 175, 10, 10);
	painter.drawRect(155, 495, 10, 10);
	painter.drawRect(475, 495, 10, 10);
	painter.drawRect(315, 335, 10, 10);

	for (int i = 0; i < NUMBER; ++i) {
		for (int j = 0; j < NUMBER; ++j) {
			if (chess[i][j] == C_BLACK) {
				brush.setColor(Qt::black);
				painter.setBrush(brush);
				painter.drawEllipse(QPoint((j + 1) * 40, (i + 1) * 40 + 20), 18, 18);
			}
			if (chess[i][j] == C_WHITE) {
				brush.setColor(Qt::white);
				painter.setBrush(brush);
				painter.setPen(Qt::NoPen);
				painter.drawEllipse(QPoint((j + 1) * 40, (i + 1) * 40 + 20), 18, 18);
			}
		}
	}
	pen.setColor(Qt::red);
	pen.setWidth(1);
	painter.setPen(pen);
	if ((moveX * 40 + 40) >= 20 && (moveX * 40 + 40) <= 620 && moveY>=0 && (moveY * 40 + 20) <= 600) {
		painter.drawLine((moveY + 1) * 40 - 20, (moveX + 1) * 40, (moveY + 1) * 40 - 10, (moveX + 1) * 40);
		painter.drawLine((moveY + 1) * 40 + 20, (moveX + 1) * 40, (moveY + 1) * 40 + 10, (moveX + 1) * 40);
		painter.drawLine((moveY + 1) * 40 - 20, (moveX + 1) * 40 + 40, (moveY + 1) * 40 - 10, (moveX + 2) * 40);
		painter.drawLine((moveY + 1) * 40 + 20, (moveX + 1) * 40 + 40, (moveY + 1) * 40 + 10, (moveX + 2) * 40);

		painter.drawLine((moveY + 1) * 40 - 20, (moveX + 1) * 40, (moveY + 1) * 40 - 20, (moveX + 1) * 40 + 10);
		painter.drawLine((moveY + 1) * 40 + 20, (moveX + 1) * 40, (moveY + 1) * 40 + 20, (moveX + 1) * 40 + 10);
		painter.drawLine((moveY + 1) * 40 - 20, (moveX + 1) * 40 + 40, (moveY + 1) * 40 - 20, (moveX + 1) * 40 + 30);
		painter.drawLine((moveY + 1) * 40 + 20, (moveX + 1) * 40 + 40, (moveY + 1) * 40 + 20, (moveX + 1) * 40 + 30);
	}
	if (currentX != -1) {
		painter.drawLine((currentY + 1) * 40 - 1, (currentX + 1) * 40 + 20, (currentY + 1) * 40 - 6, (currentX + 1) * 40 + 20);
		painter.drawLine((currentY + 1) * 40 + 1, (currentX + 1) * 40 + 20, (currentY + 1) * 40 + 6, (currentX + 1) * 40 + 20);
		painter.drawLine((currentY + 1) * 40, (currentX + 1) * 40 + 19, (currentY + 1) * 40, (currentX + 1) * 40 + 14);
		painter.drawLine((currentY + 1) * 40, (currentX + 1) * 40 + 21, (currentY + 1) * 40, (currentX + 1) * 40 + 26);
	}

	ui->timeLabel->setText(QString("Time: ")+QString::number(seconds));
	ui->stepLabel->setText(QString("Steps: ") + QString::number(steps));
}

void Widget::mouseMoveEvent(QMouseEvent* event)
{
    moveX = (event->y() - 40) / 40;
    moveY = (event->x()+20 - 40) / 40;
	update();
}
void Widget::mouseReleaseEvent(QMouseEvent* event)
{
    int x = (event->y() - 40) / 40;
    int y = (event->x()+20 - 40) / 40;
	if (x > 14 || y > 14|| chess[x][y]!=C_EMPTY)return QWidget::mousePressEvent(event);
	chess[x][y] = C_BLACK;
	evaluator->setNeeds(x, y);
	++steps;
	++counter;
	update();
	react();
    update();
}

void Widget::initGUI()
{
    this->setFixedSize(740, 660);
    this->setAutoFillBackground(true);
    this->setWindowTitle("GoBang");
    QPalette palette;
    palette.setColor(QPalette::Background, QColor("#B1723C"));
    this->setPalette(palette);
    setMouseTracking(true);
    ui->titleLabel->move(90,0);
    ui->timeLabel->move(640, 150);
    ui->stepLabel->move(640, 500);
    setWindowIcon(QIcon(":res/monisha.ico"));
    centralize();
}
Widget::~Widget()
{
	delete ui;
}

void Widget::initFunc() {
	evaluator = new Evaluator(this);
	connect(&timer, &QTimer::timeout, [=]() {
		++seconds;
        update();
		});
	steps=seconds = counter = 0;
	timer.start(1000);
	memset(chess, 0, sizeof chess);
}

void Widget::centralize()
{
	QRect rec = QApplication::desktop()->screenGeometry();
	int left = (rec.width() - this->width()) >> 1;
	int top = (rec.height() - this->height()) >> 1;
	this->move(left, top);
}
void Widget::stone()
{
	for (int i = 0; i < NUMBER; ++i) {
		for (int j = 0; j < NUMBER; ++j) {
			chess[i][j] = -1;
		}
	}
	return;
}
void Widget::react()
{
//	clock_t beg = clock();
    int bestI, bestJ;
    getPos(bestI, bestJ);
    chess[bestI][bestJ] = C_WHITE;
	int ret = evaluator->check(C_WHITE);
	if (ret != S_WAIT)gameOver(ret);
    currentX = bestI;
    currentY = bestJ;
	++counter;
    evaluator->setNeeds(bestI, bestJ);
//	qDebug() << (1000 * (clock() - beg)) / CLOCKS_PER_SEC << "ms";
}

void Widget::gameOver(int status)
{
	switch (status) {
	case S_TIE:
		QMessageBox::information(this, "tie", "平局");
		break;
	case S_WIN:
		QMessageBox::information(this, "win", "胜利");
		break;
	case S_LOSE:
		QMessageBox::information(this, "lose", "失败");
		break;
	default:
		break;
	}
	stone();
}

void Widget::getPos(int& bestI, int& bestJ) {
    int bestGameTree = INT_MIN; int bestGreedy = INT_MIN;
	NBig Q; evaluator->getNBig(Q, 1, C_WHITE);
	while (Q.size()) {
		const Node& temp = Q.pop();
		int i = temp.row, j = temp.col;
		chess[i][j] = C_WHITE;
        int val = evaluator->max_min_search(C_BLACK, INT_MIN, INT_MAX, 2);
		chess[i][j] = C_EMPTY;
        if (bestGameTree < val) {
            bestGameTree = val;
			bestI = i; bestJ = j;
			bestGreedy = temp.mark;
		}
        else if (bestGameTree == val && temp.mark >= bestGreedy) {
			bestI = i; bestJ = j;
			bestGreedy = temp.mark;
		}
	}
}
