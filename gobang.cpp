#pragma GCC optimize(3)
#pragma G++ optimize(3)

#include<QDebug>
#include<QMessageBox>
#include<QPainter>
#include<QMouseEvent>

#include "gobang.h"
#include "ui_widget.h"
#include"utility.h"
#include"def.h"
#include"evaluator.h"

GoBang::GoBang(QWidget* parent)
	: QWidget(parent)
	, ui(new Ui::Widget)
{
	ui->setupUi(this);
    initGUI();
    initFunc();
}
GoBang::~GoBang()
{
    delete ui;
    delete evaluator;
}
void GoBang::initFunc() {
	evaluator = new Evaluator(this);
    //委托一个AI
	connect(&timer, &QTimer::timeout, [=]() {
		++seconds;
        update();
        //收到信号后重绘
    });
    steps=seconds=counter=0;
	timer.start(1000);
    //timer每1000ms发送一次信号
	memset(chess, 0, sizeof chess);
}
void GoBang::restart()
{
    //各状态设为初始值
    memset(chess,0,sizeof chess);
    currentI = -1;currentJ = -1;
    seconds = 0;counter = 0;steps=0;
    evaluator->restart();
}
void GoBang::respond()
{
//    clock_t beg = clock();
    int bestI, bestJ;
    getPos(bestI, bestJ);
    //利用AI获得坐标
    chess[bestI][bestJ] = C_WHITE;
    //下子
	int ret = evaluator->check(C_WHITE);
    //判断棋局状态
    if (ret != S_WAIT){
        //胜负已分
        gameOver(ret);
        return;
    }
    currentI = bestI;
    currentJ = bestJ;
    //更新上一次下子位置
	++counter;
    //更新总子数目
    evaluator->setNeeds(bestI, bestJ);
    //扩大搜索范围
//    qDebug() <<(clock() - beg)<< "ms";
}

void GoBang::gameOver(int status)
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
    restart();
    //当前局结束后默认重新开始
}

void GoBang::getPos(int& bestI, int& bestJ) {
    int bestSearchMark = INT_MIN,bestGreedyMark = INT_MIN;
	NBig Q; evaluator->getNBig(Q, 1, C_WHITE);
	while (Q.size()) {
		const Node& temp = Q.pop();
		int i = temp.row, j = temp.col;
		chess[i][j] = C_WHITE;
        int val = evaluator->max_min_search(C_BLACK, INT_MIN, INT_MAX, 2);
		chess[i][j] = C_EMPTY;
        //回溯
        if (bestSearchMark < val) goto update;
        if (bestSearchMark == val && temp.mark >= bestGreedyMark)goto update;
        //这是一个patch,用于处理必败情况，此时该策略会让它尽可能拖延时间
        continue;
        update:
        bestSearchMark = val;
        bestI = i; bestJ = j;
        bestGreedyMark = temp.mark;
	}
}
void GoBang::mouseReleaseEvent(QMouseEvent* e)
{
    int posI = (e->y() - 40) / 40;
    int posJ = (e->x()+20 - 40) / 40;
    if (posI > 14 || posJ > 14|| chess[posI][posJ]!=C_EMPTY)return QWidget::mousePressEvent(e);
    chess[posI][posJ] = C_BLACK;
    evaluator->setNeeds(posI, posJ);
    ++steps;
    ++counter;
    update();
    respond();
    //触发响应
    update();
    QWidget::mouseReleaseEvent(e);
}
