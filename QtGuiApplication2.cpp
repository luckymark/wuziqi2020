#include "QtGuiApplication2.h"
#include<QApplication>
QtGuiApplication2::QtGuiApplication2(QWidget* parent)
	: QMainWindow(parent), turn(0), Alpha_Doge()
{
	for (int i = 0; i < BoardLength; i++)			//初始化二维数组
		for (int j = 0; j < BoardLength; j++)
			Board[i][j] = 0;

	ui.setupUi(this);
}

void QtGuiApplication2::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setPen(Qt::black);
	QBrush brush;
	
	for (int i = 0; i < BoardLength; i++)
	{
		painter.drawLine(BoardMargin+BoardOneSize*i, BoardMargin, BoardMargin+BoardOneSize*i, BoardLineLong);
		painter.drawLine(BoardMargin, BoardMargin+BoardOneSize*i, BoardLineLong, BoardMargin + BoardOneSize * i);
	}
	for (int i = 0; i < BoardLength; i++) {
		for (int j = 0; j < BoardLength; j++) {
			if (Board[i][j] != 0) {
				if (Board[i][j] == BLACK)
					brush.setColor(Qt::black);
				else if (Board[i][j] == WHITE)
					brush.setColor(Qt::white);
				brush.setStyle(Qt::SolidPattern);
				painter.setBrush(brush);	
				//※drawEllipse第一个参数是点距离左边界y轴的大小，第二个是距离上边界x轴大小，所以第一个参数应该设定为j*BS表示列距
				painter.drawEllipse(j*BoardOneSize + BoardMargin - 15, i * BoardOneSize + BoardMargin - 15, 30, 30);
			}
		}
	}
	if (Alpha_Doge.GamingOrNot() == false)
	{
		QFont font;
		font.setFamily("Microsoft YaHei");
		font.setPointSize(50);
		font.setItalic(true);
		painter.setFont(font);
		painter.drawText(rect(), Qt::AlignCenter, "GAME END");
	}
}

void QtGuiApplication2::mousePressEvent(QMouseEvent* event)
{
	QPainter painter(this);
	QPoint ai_chess;
	int x = event->x();
	int y = event->y();
	if (event->button() == Qt::LeftButton) {
		if (InBoard(x, y)) {		//row 行；col列
			int col = round((double)(x - BoardMargin) / (BoardOneSize));		//再竖着的棋盘中x坐标->实际代表是列数
			int row = round((double)(y - BoardMargin) / (BoardOneSize));		//为方便称呼把xy记为行列
			Board[row][col] = WHITE;
			Alpha_Doge.UpdateBoard(row,col,WHITE);
			Board[Alpha_Doge.BestChess().x][Alpha_Doge.BestChess().y] = BLACK;
			
			//Alpha_Doge.UpdateBoard(Alpha_Doge.BestChess().x,Alpha_Doge.BestChess().y,BLACK);
		}
	}
	update();
}
