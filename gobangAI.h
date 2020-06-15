#pragma once

#define MAX_depth 4							//层数

#define CheckerboardColor RGB(255, 222, 173)//R 255 G 222 B 173棋盘黄色
#define CbInt 40							//棋盘间隔大小
#define CbLen CbInt*14						//棋盘长度
#define CbIntNum 15							//棋盘格数
#define CbBoundNum	2						//棋盘边界数量
#define CbBoardKeyNum CbIntNum+CbBoundNum	//棋盘数组数量
#define CbBoardValueNum 10					//棋盘位置价值类型数量
#define WinLen CbLen+CbInt*2				//窗口长度
#define charlen 14




#define P_BLACKMove 1
#define P_WHITEMove 2

#define LegalMove 1
#define UnLegalMove 0

//棋子类型
#define P_BLANK 0 
#define P_BLACK 1
#define P_WHITE 2
#define P_BOUND 3

//价值定义
#define liveOne		10
#define liveTwo		100
#define liveThree	1000
#define liveFour	100000
#define liveFive	10000000
#define sleepOne	1
#define sleepTwo	10
#define sleepThree	100
#define sleepFour	10000
#define unknown		0

typedef struct ActualPoint {
	int x;
	int y;
}APoint;//物理位置：用像素大小表示
typedef struct LogicPoint {
	int x;
	int y;
	int value;
}LPoint;//逻辑位置
typedef struct LPointLinkList
{
	LPoint size;
	struct LPointLinkList* next;
}LPLink;

extern int BoardMove[CbIntNum][CbIntNum];
extern int BoardKey[CbIntNum][CbIntNum];//棋盘棋子类型，总共15*15格
extern int BoardValue[CbIntNum][CbIntNum];//棋盘位置价值类型，总共15*15
extern int value[4][4][4][4][4][4];
extern int val;
extern int WhoGo;
extern APoint IP;


LPoint* creat(LPoint LegalMoves[], int* numMove);
LPoint ChoseBest(int who);
int P_ValBest(int who, int depth, int alpha, int beta);
void GenerateLegalMoves();
void pointLegalMoves(int y, int x);
int sumValue();
int boardValueEvaluate(); 
void valueInitialization();
