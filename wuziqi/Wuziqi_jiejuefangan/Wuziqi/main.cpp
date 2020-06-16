#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <string.h>
#include <conio.h>
#define BOARD 15



void getLine(int who, int x, int y, int dir, int* Line);
void getHalfLine(int who, int x, int y, int dx, int dy, int* sum);
void isWall(int who, int opponent, int* Line, int* type);
void renderAqizi(int X, int Y);
void AIRound();
void playerRound();
void getScoresList();
int evaluatePointDeScore(int who, int x, int y);
void evaluate2Opti(int x, int y, int comboOfPoint, int* totalScore);
void isWall(int who, int opponent, int* Line, int* type);
int evaluate1First(int who, int opponent, int* Line, int* comboOfPoint);
void AISelectPosition(int* idealX, int* idealY);
void isWin(int who, int x, int y);
void renderEndingInfo(int who);

//全局变量-------------------------------------------------------
//建立当前局面棋盘各个位置的得分 便于ai选择最高分的位置去下
int scoreList[BOARD][BOARD] = { 0 };

int board[BOARD][BOARD] = { 0 };
enum { YOU = 1, YOUXIA, XIA, ZUOXIA };

//胜利标志  1黑棋胜利 2白棋胜利
int winFlag = 0;

//位置上的初始分
int positionScore[BOARD][BOARD] = {
	{-15, -15, -15, -15, -15, -15, -15, -15, -15, -15, -15, -15, -15, -15, -15},
	{-15, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -15},
	{-15, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, -15},
	{-15, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 1, -15},
	{-15, 1, 2, 3, 4, 4, 4, 4, 4, 4, 4, 3, 2, 1, -15},
	{-15, 1, 2, 3, 4, 5, 5, 5, 5, 5, 4, 3, 2, 1, -15},
	{-15, 1, 2, 3, 4, 5, 6, 6, 6, 5, 4, 3, 2, 1, -15},
	{-15, 1, 2, 3, 4, 5, 6, 7, 6, 5, 4, 3, 2, 1, -15},
	{-15, 1, 2, 3, 4, 5, 6, 6, 6, 5, 4, 3, 2, 1, -15},
	{-15, 1, 2, 3, 4, 5, 5, 5, 5, 5, 4, 3, 2, 1, -15},
	{-15, 1, 2, 3, 4, 4, 4, 4, 4, 4, 4, 3, 2, 1, -15},
	{-15, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 1, -15},
	{-15, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, -15},
	{-15, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -15},
	{-15, -15, -15, -15, -15, -15, -15, -15, -15, -15, -15, -15, -15, -15, -15} };
//---------------------------------------------------------------


void renderTheBoard() {
	setlinecolor(RED);
	setfillcolor(RGB(255, 205, 150));

	//绘制棋盘底色
	solidrectangle(-20, -20, 720, 720);

	//绘制边框
	for (int i = 1; i < 3; i++) {
		rectangle(-i, -i, 700 + i, 700 + i);
	}
	//绘制竖线
	for (int x = 0, y = 0, i = 0; i < 15; i++) {
		line(x, y, x, y + 700);
		x += 50;
	}
	//绘制横线
	for (int x = 0, y = 0, i = 0; i < 15; i++) {
		line(x, y, x + 700, y);
		y += 50;
	}
	//中心点标出
	setfillcolor(BLACK);
	fillcircle(350, 350, 5);

}

void renderTheBase() {
	setfillcolor(RGB(250, 240, 230));
	solidrectangle(-50, -50, 1100, 750);

	setbkmode(TRANSPARENT);
	settextcolor(BLACK);

	settextstyle(30, 0, _T("黑体"));
	TCHAR s1[] = _T("玩家执黑先行");
	TCHAR s2[] = _T("电脑执白后行");
	outtextxy(800, 50, s1);
	outtextxy(800, 90, s2);
}

void getTheWindow() {
	initgraph(1150, 800);
	//设置新的原点
	setorigin(50, 50);
	renderTheBase();
	renderTheBoard();
}

//开始行棋
void battleStart() {
	int nowRound = 1;
	while (nowRound) {
		//printf("--%d\n", nowRound);

		switch (nowRound % 2) {
		case 0://AI走
			AIRound();
			nowRound++;
			break;
		case 1://玩家走
			playerRound();
			nowRound++;
			break;
		}

		//判胜-----------
		if (winFlag != 0) {
			renderEndingInfo(winFlag);
			return;
		}
	}
}

void renderEndingInfo(int who) {
	settextcolor(RGB(255, 106, 106));
	settextstyle(40, 0, _T("黑体"));
	TCHAR win1[] = _T("玩家获胜！");
	TCHAR win2[] = _T("电脑获胜！");
	switch (who) {
	case 1:
		outtextxy(800, 300, win1);
		break;
	case 2:
		outtextxy(800, 300, win2);
		break;
	}
}

//玩家行棋
void playerRound() {
	MOUSEMSG mouse;
	FlushMouseMsgBuffer();

	//意向落子靶坐标 除以50即对应数组下标
	//注意 由于设备坐标原点不可更改 所以最后要-50
	int X = 0, Y = 0;
	while (true) {
		while (MouseHit()) {
			mouse = GetMouseMsg();
			if (mouse.uMsg == WM_LBUTTONDOWN) {
				//此处将实际鼠标读取到的坐标 修正为原点变换后的坐标
				int mouseX = mouse.x - 50;
				int mouseY = mouse.y - 50;
				//判断鼠标是否在棋盘内
				if ((mouseX >= 0 && mouseX <= 700) && (mouseY >= 0 && mouseY <= 700)) {
					//判断鼠标是否在落子判定区域内
					if ((mouseX % 50 > 10 && mouseX % 50 < 40) || (mouseY % 50 > 10 && mouseY % 50 < 40)) {
						break; //鼠标不在判定区域内
					}
					//精确定位到某一靶坐标上
					else {
						if (mouseX % 50 <= 10) {
							X = 50 * (mouseX / 50);
						}
						else if (mouseX % 50 >= 40) {
							X = 50 * ((mouseX / 50) + 1);
						}

						if (mouseY % 50 <= 10) {
							Y = 50 * (mouseY / 50);
						}
						else if (mouseY % 50 >= 40) {
							Y = 50 * ((mouseY / 50) + 1);
						}


						//如果按下左键

						if (board[Y / 50][X / 50] == 0) {
							board[Y / 50][X / 50] = 1; //落上玩家的黑子
							renderAqizi(X, Y); //绘制出那个位置上的棋子
							isWin(1, X / 50, Y / 50);
							return;
						}
						//延时以降低cpu使用
						Sleep(20);
					}
				}
			}
		}
	}
}

//胜利判断
void isWin(int who, int x, int y) {

	int theLine[11] = { 0 };
	for (int dir = 1; dir <= 4; dir++) {
		getLine(who, x, y, dir, theLine);

		int count = 1;  //因为Line[5]必定有一个 所以count从1开始
		for (int i = 6; i <= 10; i++) {
			if (theLine[i] == who) {
				count++;
			}
			else {
				break;
			}
		}
		for (int i = 4; i >= 0; i--) {
			if (theLine[i] == who) {
				count++;
			}
			else {
				break;
			}
		}
		if (count >= 5) {
			winFlag = who;
			break;
		}
	}
}

//------------------------------------------------------AI部分
//AI行棋
void AIRound() {
	int idealX = 0, idealY = 0;
	getScoresList();
	AISelectPosition(&idealX, &idealY);
	board[idealY][idealX] = 2; //落上AI的白子
	renderAqizi((idealX) * 50, (idealY) * 50); //绘制出那个位置上的棋子
	isWin(2, idealX, idealY);
}



void AISelectPosition(int* idealX, int* idealY) {
	int maxScore = -99999;
	for (int i = 0; i < BOARD; i++)
	{
		for (int j = 0; j < BOARD; j++) {
			if (board[i][j] == 0) {
				if (scoreList[i][j] > maxScore) {
					maxScore = scoreList[i][j];
					*idealX = j;
					*idealY = i;
				}
			}
		}
	}
}



//------------------棋形判断部分----------------------------------------

void getHalfLine(int who, int x, int y, int dx, int dy, int* sum) {
	int isPositive = 1;
	if (dy == -1 || (dy == 0 && dx == -1)) {
		isPositive = 0;
	}
	for (int i = 0; i < 5; i++) {
		x += dx;
		y += dy;
		//越界处理
		if (x < 0 || x > BOARD - 1 || y < 0 || y > BOARD - 1) {
			sum[i] = 3 - who;  //记为对手的棋色
		}
		else {
			sum[i] = board[y][x];
		}
	}
	//判断是否逆置
	if (isPositive == 0) {
		int sum2[5];
		for (int i = 0; i < 5; i++) {
			sum2[i] = sum[i];
		}
		for (int i = 0; i < 5; i++) {
			sum[i] = sum2[4 - i];
		}
	}
}

// who:1黑2白
//函数功能：给定一个坐标 和 方向 ，给一个数组进去 将数组处理为那一个方向上的棋形
void getLine(int who, int x, int y, int dir, int* Line) {
	int negtive[5], positive[5];
	int dx, dy;
	switch (dir) {
	case YOU:
		dx = 1;
		dy = 0;
		break;
	case YOUXIA:
		dx = 1;
		dy = 1;
		break;
	case XIA:
		dx = 0;
		dy = 1;
		break;
	case ZUOXIA:
		dx = -1;
		dy = 1;
		break;
	}
	getHalfLine(who, x, y, dx * (-1), dy * (-1), negtive);
	getHalfLine(who, x, y, dx, dy, positive);

	for (int i = 0; i < 5; i++) {
		Line[i] = negtive[i];
	}
	Line[5] = who;
	for (int i = 0; i < 5; i++) {
		Line[i + 6] = positive[i];
	}
}
////////////////////////////////////////////////////////////////////////////////////
enum {
	FIVE = 50000,
	ALIVE4 = 10000,
	ALIVE3 = 2000,
	ALIVE2 = 80,
	RUSH4 = 1600,
	SLEEP3 = 150,
	SLEEP2 = 40,
	DEAD1 = -1,
	SLEEP1 = 5,
	NONE = 0,
	DEAD2 = -2,
	DEAD4 = -10,
	DEAD3 = -5,

};



int evaluatePointDeScore(int who, int x, int y) {
	int totalScore = 0;
	int score = 0;
	//存每个点的 combo ,用十位百位千位的数字来表示二三四的个数 用于优化补正分数
	//例如0200表示双三
	int comboOfPoint = 0;
	int Line[11];
	// 4个方向分别打分 再将打分相加
	for (int dir = 1; dir <= 4; dir++) {
		getLine(who, x, y, dir, Line);  //得到Line了
		score = evaluate1First(who, 3 - who, Line, &comboOfPoint);
		totalScore += score;
	}
	evaluate2Opti(x, y, comboOfPoint, &totalScore);  //对总得分进行补正
	return totalScore;
}

//判断某一Line上的棋形并初步打分函数-----------------------
int evaluate1First(int who, int opponent, int* Line, int* comboOfPoint) {
	int score = 0;
	int type[2];                        //[0]存count [1]存flag
	isWall(who, opponent, Line, type);  //得到type
	switch (type[0]) {
	case 1:  // 1颗连子
		switch (type[1]) {
		case -2:  // DEAD
			score = DEAD1;

			break;
		case 0:
			score = SLEEP1;
			break;
		case 2:  // ALIVE
			score = NONE;
			break;
		}
		break;
	case 2:  // 2颗连子
		switch (type[1]) {
		case -2:  // DEAD
			score = DEAD2;
			break;
		case 0:
			score = SLEEP2;
			break;
		case 2:  // ALIVE
			score = ALIVE2;
			*comboOfPoint += 35;
			break;
		}
		break;
	case 3:  // 3颗连子
		switch (type[1]) {
		case -2:  // DEAD
			score = DEAD3;
			break;
		case 0:
			score = SLEEP3;
			*comboOfPoint += 50;
			break;
		case 2:  // ALIVE
			score = ALIVE3;
			*comboOfPoint += 130;
			break;
		}
		break;
	case 4:  // 4颗连子
		switch (type[1]) {
		case -2:  // DEAD
			score = DEAD4;
			break;
		case 0:
			score = RUSH4;
			*comboOfPoint += 1200;
			break;
		case 2:  // ALIVE
			score = ALIVE4;
			break;
		}
		break;
	case 5:  // FIVE
		score = FIVE;
		break;

		//以下为了应付长连的情况
	case 6:
		score = FIVE;
		break;
	case 7:
		score = FIVE;
		break;
	case 8:
		score = FIVE;
		break;
	}
	return score;
}

//判断与中心子相连的子有多少个
//遇到异色棋子即停止计数 标记-1
//若两边都是异色停止 则flag最后为-2
//遇到空位也停止 标记+1
//那么最后flag值只能为-2，0，2 对应 死，眠/冲，活
//便于进一步判断
void isWall(int who, int opponent, int* Line, int* type) {
	int count = 1;  //因为Line[5]必定有一个 所以count从1开始
	int flag = 0;
	for (int i = 6; i <= 10; i++) {
		if (Line[i] == who) {
			count++;
		}
		else if (Line[i] == opponent) {
			flag -= 1;
			break;
		}
		else {
			flag += 1;
			break;
		}
	}
	for (int i = 4; i >= 0; i--) {
		if (Line[i] == who) {
			count++;
		}
		else if (Line[i] == opponent) {
			flag -= 1;
			break;
		}
		else {
			flag += 1;
			break;
		}
	}
	type[0] = count;
	type[1] = flag;
}  //留个坑 其实判断到空位后 至少应该再继续判断下1个格子的情况

//分值优化函数
void evaluate2Opti(int x, int y, int comboOfPoint, int* totalScore) {
	// 根据处在棋盘中的位置给予位置分
	*totalScore += positionScore[y][x];
	// 有双三 双二等 那么给予额外的补正分数
	if (comboOfPoint > 2000) {
		*totalScore = (*totalScore) * 2;
	}
	else if (comboOfPoint < 1000 && comboOfPoint > 200) {
		*totalScore = (*totalScore) * 2.5;
	}
	else if (comboOfPoint < 100 && comboOfPoint > 60) {
		*totalScore = (*totalScore) * 1.5;
	}
}


//-------------------------------某一点的棋形判断 打分 优化得分部分  结束----------------------------------------

//为当前局面棋盘各个可下的位置打分 便于ai选择最高分的位置去下
void getScoresList() {
	for (int i = 0; i < BOARD; i++) {
		for (int j = 0; j < BOARD; j++) {
			if (board[i][j] == 0) {
				//攻击分+防守分 等于综合得分
				scoreList[i][j] = evaluatePointDeScore(2, j, i) + evaluatePointDeScore(1, j, i) * 1;
			}
		}
	}
}

//--------------------------------------------------------------------------

//各种绘制函数-----------------------------------------

//绘制棋子 半径20  坐标x,y  0空 2白棋 1黑棋
void renderAqizi(int X, int Y) {
	int type = board[Y / 50][X / 50];
	setlinecolor(BLACK);
	switch (type) {
	case 0:
		break;
	case 2:
		setfillcolor(WHITE);
		break;
	case 1:
		setfillcolor(BLACK);
		break;
	}
	fillcircle(X, Y, 20);
}


int main(void) {
	getTheWindow();

	battleStart();

	_getch();
	closegraph();
	return 0;
}