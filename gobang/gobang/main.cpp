#include<graphics.h>
#include<algorithm>
#include<conio.h>
#include"init.h"
#include"data.h"
#include"evaluate.h"
Point q[226];

extern int board[16][16];
extern int dir[4][2];
int count;//当前步数
int lastx, lasty;
bool final5[16][16];//用来标记最后形成五连的棋子，以在结果时高亮显示
bool reverse, can;

MOUSEMSG mouse;

void startGame();
Point dfs(int depth, int maxdepth, int color, int maxpre);
int checkwin();
bool toofar(int x, int y);
void putlatest(int x, int y, int color);
void putpiece(int x, int y, int color);
void selectiffirst();


int main()
{
	startGame();
	return 0;
}

void startGame()
{
	selectiffirst();
	initboard();
	while (1)
	{
		count++;
		if (count == 1)//如果电脑先走，第一步下正中心
		{
			putlatest(8, 8, Black);
			lastx = 8; lasty = 8;
		}
		else if (count & 1)//电脑走
		{
			Point nextPoint;
			for (int maxdepth = 2; maxdepth <= 4; maxdepth += 2)//迭代
			{

				nextPoint = dfs(1, maxdepth, Black, -0x7fffffff);
				if (nextPoint.score > 20000000) break;
			}
			putpiece(lastx, lasty, White);
			putlatest(nextPoint.x, nextPoint.y, Black);
			lastx = nextPoint.x; lasty = nextPoint.y;
		}
		else//人走
		{
			while (1)
			{
				mouse = GetMouseMsg();
				if (mouse.mkLButton)
				{
					int x = mouse.x - 55, y = mouse.y - 55;
					if (x < 0 || x>35 * 14 || y < 0 || y>35 * 14) continue;
					int posx = (x + 17) / 35 + 1;
					int posy = (y + 17) / 35 + 1;
					if (board[posx][posy]) continue;
					if(lastx) putpiece(lastx, lasty, Black);
					putlatest(posx, posy, White);
					lastx = posx; lasty = posy;
					break;
				}
			}
		}
		int whoWin = checkwin();//判断输赢与结果显示
		if (whoWin)
		{
			settextcolor(WHITE);
			settextstyle(50, 0, _T("宋体"));
			RECT r = { 35 * 0, 35 * -1.5, 35 * 14, 35 * 5 };
			if (whoWin == White)
			{
				drawtext(_T("你赢了！"), &r, DT_CENTER);
			}
			else drawtext(_T("你输了。"), &r, DT_CENTER);
			for (int i = 1; i <= 15; i++)
				for (int j = 1; j <= 15; j++)
					if (final5[i][j])
						putlatest(i, j, board[i][j]);
			while (1)
			{
				mouse = GetMouseMsg();
				if (mouse.mkLButton) break;
			}
			break;
		}
	}
}

Point dfs(int depth,int maxdepth,int color,int maxpre)//深搜
{
	int cnt = 0;
	for (int i = 1; i <= 15; i++)
		for (int j = 1; j <= 15; j++)
		{
			if (board[i][j] || toofar(i, j)) continue;//该位置已经有棋子了不能下或离已有棋子太远了不该下
			Point p=evaluatePoint(i, j);//计算当前位置的优先级
			if (p.score < 2) continue;
			q[++cnt] = p;
		}
	std::sort(q + 1, q + cnt + 1);//根据优先度对当前要下的位置进行排序以提升剪枝的效果
	Point maxPoint;//使己方得分最高的点
	maxPoint.score = -0x7fffffff;
	for (int i = 1; i <= cnt; i++)
	{
		if (depth == 1) can = true;
		Point nowp = q[i];
		board[nowp.x][nowp.y] = color;
		Point selPoint;
		if (depth == maxdepth) selPoint = evaluateWhole(nowp.x, nowp.y);//到搜索的最大层数后计算当前棋面的分数
		else selPoint = dfs(depth + 1, maxdepth, 3 - color, maxPoint.score);

		if (maxdepth == 4 && depth == 2 && selPoint.score > 20000000)
		{
			Point judgePoint = evaluateWhole(nowp.x, nowp.y);
			if (judgePoint.score < -20000000) can = false;
		}//避免四步之后己方五连，但在两步时对方就已经五连的情况(因为己方的五连分数比对方的五连分数高，以在能获胜时直接采取能获胜的方式)

		board[nowp.x][nowp.y] = Empty;//回溯时需要将下的棋删去
		selPoint.score *= -1;//该操作能将极小极大值搜索统一为极大值搜索
		if (depth == 1 && can == false) selPoint.score = -0x7fffffff + 1;
		if (selPoint.score > maxPoint.score)
		{
			maxPoint.score = selPoint.score;
			maxPoint.x = nowp.x; maxPoint.y = nowp.y;
		}
		if (maxPoint.score * -1 <= maxpre) break;//α-β剪枝
	}
	return maxPoint;
}


int checkwin()//在下每步棋之后调用，检查是否有一方已经获胜，如已获胜，则标记导致获胜的五连棋，并返回胜利方
{
	int winner;
	for (int i = 1; i <= 15; i++)
		for (int j = 1; j <= 15; j++)
		{
			if (board[i][j] == Empty) continue;
			for (int k = 0; k < 4; k++)
			{
				if (i + 4 * dir[k][0] > 15 || i + 4 * dir[k][0] < 1 || j + 4 * dir[k][1]>15) continue;
				int nowx = i, nowy = j;
				bool FLAG = true;
				for (int K = 1; K <= 4; K++)
					if (board[i + K * dir[k][0]][j + K * dir[k][1]] != board[i + (K - 1) * dir[k][0]][j + (K - 1) * dir[k][1]])
					{
						FLAG = false;
						break;
					}
				if (FLAG)
				{
					for (int K = 0; K <= 4; K++)
						final5[i + K * dir[k][0]][j + K * dir[k][1]] = true;
					winner = board[i][j];
					return winner;
				}
			}
		}
	return 0;
}


bool toofar(int x, int y)//判断该位置是否离现有的棋子太远，用来确定当前可下的位置的集合
{
	for (int i = -2; i <= 2; i++)
		for (int j = -2; j <= 2; j++)
		{
			if (outboard(x + i, y + j)) continue;
			if (i == 0 && j == 0) continue;
			if (board[x + i][y + j]) return false;
		}
	return true;
}


void putlatest(int x, int y, int color)//下最新的那颗棋(外围为黄色以提示用户)
{
	board[x][y] = color;
	if (reverse) color = 3 - color;
	setfillcolor(color == White ? WHITE : BLACK);
	setlinecolor(YELLOW);
	fillcircle((x - 1) * 35, (y - 1) * 35, 12);
}
void putpiece(int x, int y, int color)//将上一颗外围为黄色的棋子变为正常颜色
{
	if (reverse) color = 3 - color;
	setfillcolor(color == White ? WHITE : BLACK);
	setlinecolor(color == White ? WHITE : BLACK);
	fillcircle((x - 1) * 35, (y - 1) * 35, 12);
}


void selectiffirst()//选择先下还是后下
{
	initboard();
	setfillcolor(WHITE);
	setlinecolor(BLACK);
	fillrectangle(35 * 5.5, 35 * 4, 35 * 8.5, 35 * 5.25);
	fillrectangle(35 * 5.5, 35 * 5.75, 35 * 8.5, 35 * 7);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(35, 0, _T("宋体"));
	RECT r1 = { 35 * 5.5, 35 * 4, 35 * 8.5, 35 * 5.5 };
	RECT r2 = { 35 * 5.5, 35 * 5.75, 35 * 8.5, 35 * 7 };
	drawtext(_T("先下"), &r1, DT_CENTER);
	drawtext(_T("后下"), &r2, DT_CENTER);
	while (1)
	{
		mouse = GetMouseMsg();
		if (mouse.mkLButton)
		{
			int x = mouse.x - 55, y = mouse.y - 55;
			if (x < 35 * 5.5 || x>35 * 8.5) continue;
			if (y >= 35 * 4 && y <= 35 * 5.25)
			{
				count++;
				reverse = true;
				break;
			}
			if (y >= 35 * 5.75 && y <= 35 * 7) break;
		}
	}
}