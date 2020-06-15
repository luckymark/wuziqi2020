#include"gobangAI.h"
#include"view.h"

APoint IP={ CbInt,CbInt };

//初始化棋盘
void drawCb() {
	static APoint IP = { CbInt,CbInt };  //初始点
	initgraph(WinLen, WinLen);	// 创建绘图窗口
	setbkcolor(CheckerboardColor);             //  设置背景颜色
	//setfillcolor(CheckerboardColor);//设置填充颜色
	//solidrectangle(0, 0, WindowLength, WindowLength);//绘制棋盘底色矩形
	cleardevice();			// 用背景色清空屏幕
	setlinecolor(BLACK);
	for (int i = 0; i < CbIntNum; i++)//黑色横线
	{
		line(IP.x, IP.y + i * CbInt, IP.x + CbLen, IP.y + i * CbInt);
	}
	for (int i = 0; i < CbIntNum; i++)//黑色竖线
	{
		line(IP.x + i * CbInt, IP.y, IP.x + i * CbInt, IP.y + CbLen);
	}
	//solidcircle();//
	// 坐标（数值）
	TCHAR strnum[15][3] = { _T("1"),_T("2") ,_T("3") ,_T("4"),_T("5") ,_T("6") ,_T("7"),_T("8"),_T("9"),_T("10"), _T("11"),_T("12") ,_T("13") ,_T("14"),_T("15") };
	// 坐标（字母）
	TCHAR strabc[15][3] = { _T("A"),_T("B") ,_T("C") ,_T("D"),_T("E") ,_T("F") ,_T("G"),_T("H"),_T("I"),_T("J"), _T("K"),_T("L") ,_T("M") ,_T("N"),_T("O") };
	settextcolor(BLACK);
	for (int i = 0; i < CbIntNum; i++)//下方字母
	{
		RECT Rabc = { IP.x - CbInt * 0.25 + i * (double)CbInt, IP.y + CbInt * 0.5 - charlen * 0.5 + (double)CbLen, IP.x + CbInt * 0.25 + (double)i * CbInt, IP.y + CbInt * 0.5 + charlen * 0.5 + (double)CbLen };
		drawtext(strabc[i], &Rabc, DT_CENTER);
	}
	for (int i = 0; i < CbIntNum; i++)//左侧数字
	{
		RECT Rnum = { 0 , IP.y - charlen * 0.5 + (double)i * (double)CbInt, IP.x - CbInt * 0.2 , IP.y + charlen * 0.5 + i * (double)CbInt };
		drawtext(strnum[i], &Rnum, DT_RIGHT);
	}
}

//画棋子
void drawPiece(int y,int x,int key) {
	if (key==1)
	{
		setfillcolor(BLACK);
	}
	else {
		setfillcolor(WHITE);
	}
	solidcircle((x+1)* CbInt, (y + 1) * CbInt, CbInt * 0.4);
}

//画棋盘
void PrintBoard(int Board[][CbIntNum]) {
	for (int i = 0; i < CbIntNum; i++)
	{
		for (int j = 0; j < CbIntNum; j++)
		{
			if (Board[i][j] == 1 || Board[i][j] == 2) {
				drawPiece(j, i, Board[i][j]);
			}
		}
	}
}

//判断鼠标位置是否是空
int IsBLANK(MOUSEMSG mouse,int y,int x) {
	if (mouse.x > IP.x + (x - 0.5) * CbInt && mouse.x<IP.x + (x + 0.5) * CbInt//判断x坐标
		&& mouse.y>IP.y + (y - 0.5) * CbInt && mouse.y < IP.y + (y + 0.5) * CbInt//判断y坐标
		&& BoardKey[y][x] == P_BLANK)//判断是否是空位置
	{
		return 1;
	}
	return 0;
}

