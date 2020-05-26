#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtGuiApplication2.h"
#include<QPushButton>
#include<QLabel>
#include<QPainter>
#include<QMouseEvent>
#include<QPoint>
#include<cmath>
#include"Score_Config.h"
#include"AI.h"

class QtGuiApplication2 : public QMainWindow
{
	Q_OBJECT

public:
	QtGuiApplication2(QWidget *parent = Q_NULLPTR);
	void paintEvent(QPaintEvent* event);
	void mousePressEvent(QMouseEvent* event);
	AI Alpha_Doge;
signals:

public slots:

private:
	int turn;//
	int Board[BoardLength][BoardLength];
	bool InBoard(int xx, int yy){
		if (xx > BoardMargin + 14 * BoardOneSize || xx<BoardMargin ||
			yy>BoardMargin + 14 * BoardOneSize || yy < BoardMargin)
			return false;
		else
			return true;
	}
	Turns WhiteOrBlack(){
		if (turn % 2)
			return BLACK;
		else
			return WHITE;
	}
	Ui::QtGuiApplication2Class ui;
};
