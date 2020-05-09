#include"gobang.h"

int BoardMove[CbIntNum][CbIntNum];
int BoardKey[CbIntNum][CbIntNum];//棋盘棋子类型，总共15*15格
int BoardValue[CbIntNum][CbIntNum];//棋盘位置价值类型，总共15*15
int value[4][4][4][4][4][4];
int val;
int WhoGo;

//
void UnmakeMove(LPLink* p) {
	BoardKey[p->size.y][p->size.x] = P_BLANK;
}
//
void MakeNextMove(LPLink* p,int depth,int who) {
	if (((who + depth) % 2) == 1)
	{
		BoardKey[p->size.y][p->size.x] = P_BLACK;
	}
	else if (((who + depth) % 2) == 0)
	{
		BoardKey[p->size.y][p->size.x] = P_WHITE;
	}
}

LPLink* GenerateLegalMoves() {
	
	for (int i = 2; i < CbIntNum-2; i++)
	{
		for (int j = 2; j < CbIntNum-2; j++)
		{
			//棋子周围两格为可能下棋的位置
			if (BoardKey[i][j]==P_BLACK|| BoardKey[i][j] == P_WHITE)
			{
				//周围一格
				BoardMove[i + 1][j] = LegalMove;
				BoardMove[i][j + 1] = LegalMove;
				BoardMove[i - 1][j] = LegalMove;
				BoardMove[i][j - 1] = LegalMove;
				BoardMove[i + 1][j + 1] = LegalMove;
				BoardMove[i - 1][j + 1] = LegalMove;
				BoardMove[i - 1][j - 1] = LegalMove;
				BoardMove[i + 1][j - 1] = LegalMove;
				//按八条线延伸到第二格
				BoardMove[i + 2][j] = LegalMove;
				BoardMove[i][j+2] = LegalMove;
				BoardMove[i - 2][j] = LegalMove;
				BoardMove[i][j - 2] = LegalMove;
				BoardMove[i + 2][j + 2] = LegalMove;
				BoardMove[i - 2][j + 2] = LegalMove;
				BoardMove[i - 2][j - 2] = LegalMove;
				BoardMove[i + 2][j - 2] = LegalMove;
			}
		}
	}

	for (int i = 2; i < CbIntNum-2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (BoardKey[i][j] == P_BLACK || BoardKey[i][j] == P_WHITE)
			{
				//周围一格
				BoardMove[i + 1][j] = LegalMove;
				BoardMove[i][j + 1] = LegalMove;
				BoardMove[i - 1][j] = LegalMove;
				BoardMove[i + 1][j + 1] = LegalMove;
				BoardMove[i - 1][j + 1] = LegalMove;
				//按八条线延伸到第二格
				BoardMove[i + 2][j] = LegalMove;
				BoardMove[i][j+2] = LegalMove;
				BoardMove[i - 2][j] = LegalMove;
				BoardMove[i + 2][j + 2] = LegalMove;
				BoardMove[i - 2][j + 2] = LegalMove;
			}
			if (BoardKey[j][i] == P_BLACK || BoardKey[j][i] == P_WHITE)
			{
				//周围一格
				BoardMove[j + 1][i] = LegalMove;
				BoardMove[j][i + 1] = LegalMove;
				BoardMove[j][i - 1] = LegalMove;
				BoardMove[j + 1][i + 1] = LegalMove;
				BoardMove[j + 1][i - 1] = LegalMove;
				//按八条线延伸到第二格
				BoardMove[j + 2][i] = LegalMove;
				BoardMove[j][i + 2] = LegalMove;
				BoardMove[j][i - 2] = LegalMove;
				BoardMove[j + 2][i + 2] = LegalMove;
				BoardMove[j + 2][i - 2] = LegalMove;

			}
			if (BoardKey[i][14-j] == P_BLACK || BoardKey[i][14-j] == P_WHITE)
			{
				//周围一格
				BoardMove[i + 1][14 - j] = LegalMove;
				BoardMove[i][13 - j] = LegalMove;
				BoardMove[i - 1][14 - j] = LegalMove;
				BoardMove[i + 1][13 - j] = LegalMove;
				BoardMove[i - 1][13 - j] = LegalMove;
				//按八条线延伸到第二格
				BoardMove[i + 2][14 - j] = LegalMove;
				BoardMove[i][12 - j] = LegalMove;
				BoardMove[i - 2][14 - j] = LegalMove;
				BoardMove[i + 2][12 - j] = LegalMove;
				BoardMove[i - 2][12 - j] = LegalMove;

			}
			if (BoardKey[14-j][i] == P_BLACK || BoardKey[14-j][i] == P_WHITE)
			{
				//周围一格
				BoardMove[14 - j][i - 1] = LegalMove;
				BoardMove[14 - j][i + 1] = LegalMove;
				BoardMove[13 - j][i] = LegalMove;
				BoardMove[13 - j][i + 1] = LegalMove;
				BoardMove[13 - j][i - 1] = LegalMove;
				//按八条线延伸到第二格
				BoardMove[14 - j][i - 2] = LegalMove;
				BoardMove[14 - j][i + 2] = LegalMove;
				BoardMove[12 - j][i] = LegalMove;
				BoardMove[12 - j][i - 2] = LegalMove;
				BoardMove[12 - j][i + 2] = LegalMove;
			}
		}
	}

	for (int i = 0; i < CbIntNum; i++)
	{
		for (int j = 0; j < CbIntNum; j++)
		{
			if (BoardKey[i][j] == P_BLACK || BoardKey[i][j] == P_WHITE) 
			{
				BoardMove[i][j] = UnLegalMove;
			}
		}
	}

	return creat(BoardMove);
}

LPoint ChoseBest(LPLink* p,int who) {
	LPLink * node;
	LPoint best;
	node = p->next;
	int val=0,valbest=0;
	if (who==1)
	{
		valbest = -9999999;
	}
	if (who==2)
	{
		valbest = 9999999;
	}
	while (p->next != NULL) {
		p = p->next;
		MakeNextMove(p, who,MAX_depth);
		val = P_ValBest(p,who, MAX_depth,999999,-999999);
		UnmakeMove(p);
		if (who == 1)
		{
			if (val > valbest) {
				node = p;
				valbest = val;
			}
		}
		if (who == 2)
		{
			if (val < valbest) {
				node = p;
				valbest = val;
			}
		}
		
	}
	best.value = valbest;
	best.x = node->size.x;
	best.y = node->size.y;
	return best;
}

void freeLPLink(LPLink* node) {
	LPLink* end;
	while (node!= NULL) {
		end = node;
		node = node->next;
		free(end);
	}
}

int P_ValBest(LPLink* thisP, int who, int depth, int alpha, int beta) {
	if (depth == 1) {
		return boardValueEvaluate();
	}
	LPLink* node;
	int val = 0;
	int valbest=0;
	if ((who + depth - 1) % 2 == 1)//极大节点
	{
		valbest = -9999999;
	}
	if ((who + depth - 1) % 2 == 0)//极小节点
	{
		valbest = 9999999;
	}

	LPLink* nextP;
	nextP = GenerateLegalMoves();
	while (nextP->next != NULL) {
		node = nextP;
		nextP = nextP->next;
		free(node);
		MakeNextMove(nextP, who,depth-1);
		val = P_ValBest(thisP,who,depth-1,alpha,beta);
		UnmakeMove(nextP);
		if ((who+depth-1)%2 == 1)
		{
			if (val > valbest) {
				valbest = val;
			}
			if (val > alpha) {
				freeLPLink(nextP);
				return val;
			}
			if (val > beta) {
				beta = val;
			}

			
		}
		if ((who+depth-1)%2 == 0)
		{
			if (val < valbest) {
				valbest = val;
			}
			if (val < beta) {
				freeLPLink(nextP);
				return val;
			}
			if (val < alpha) {
				alpha = val;
			}
		}
		
	}
	//freeLPLink(node);
	return valbest;
}

//从中间开始创建一个链表越靠近中间的在前面
LPLink* creat(int BoardMove[][CbIntNum]) {
	LPLink* head, * node, * end;//定义头节点，普通节点，尾部节点；
	head = (LPLink*)malloc(sizeof(LPLink));//分配地址
	end = head;         //若是空链表则头尾节点一样
	for (int i = 1; i < 8; i++)
	{
		for (int j = -i+1; j <= i; j++)
		{
			if (BoardMove[7+i][7-j] == LegalMove)
			{
				node = (LPLink*)malloc(sizeof(LPLink));
				node->size.y = 7 + i;
				node->size.x = 7 - j;
				end->next = node;
				end = node;
			}
			if (BoardMove[7-i][7+j] == LegalMove)
			{
				node = (LPLink*)malloc(sizeof(LPLink));
				node->size.y = 7 - i;
				node->size.x = 7 + j;
				end->next = node;
				end = node;
			}
			if (BoardMove[7+j][7+i] == LegalMove)
			{
				node = (LPLink*)malloc(sizeof(LPLink));
				node->size.y = 7 + j;
				node->size.x = 7 + i;
				end->next = node;
				end = node;
			}
			if (BoardMove[7-j][7-i] == LegalMove)
			{
				node = (LPLink*)malloc(sizeof(LPLink));
				node->size.y = 7 - j;
				node->size.x = 7 - i;
				end->next = node;
				end = node;
			}
		}
	}

	end->next = NULL;//结束创建
	return head;
}

void valueInitialization() {
	//活四
	value[P_BLANK][P_BLACK][P_BLACK][P_BLACK][P_BLACK][P_BLANK] = liveFour;
	value[P_BLANK][P_WHITE][P_WHITE][P_WHITE][P_WHITE][P_BLANK] = -liveFour;
	//连五
	value[P_BOUND][P_BLACK][P_BLACK][P_BLACK][P_BLACK][P_BLACK] = liveFive;
	value[P_BLANK][P_BLACK][P_BLACK][P_BLACK][P_BLACK][P_BLACK] = liveFive;
	value[P_WHITE][P_BLACK][P_BLACK][P_BLACK][P_BLACK][P_BLACK] = liveFive;
	value[P_BOUND][P_WHITE][P_WHITE][P_WHITE][P_WHITE][P_WHITE] = -liveFive;
	value[P_BLANK][P_WHITE][P_WHITE][P_WHITE][P_WHITE][P_WHITE] = -liveFive;
	value[P_BLACK][P_WHITE][P_WHITE][P_WHITE][P_WHITE][P_WHITE] = -liveFive;
	//活三 1 存疑 有重复的可能
	value[P_BLANK][P_BLANK][P_BLACK][P_BLACK][P_BLACK][P_BLANK] = liveThree;
	value[P_BLANK][P_BLACK][P_BLANK][P_BLACK][P_BLACK][P_BLANK] = liveThree;
	value[P_BLANK][P_BLACK][P_BLACK][P_BLANK][P_BLACK][P_BLANK] = liveThree;
	value[P_BLANK][P_BLACK][P_BLACK][P_BLACK][P_BLANK][P_BLANK] = liveThree;
	value[P_BLANK][P_BLANK][P_WHITE][P_WHITE][P_WHITE][P_BLANK] = -liveThree;
	value[P_BLANK][P_WHITE][P_BLANK][P_WHITE][P_WHITE][P_BLANK] = -liveThree;
	value[P_BLANK][P_WHITE][P_WHITE][P_BLANK][P_WHITE][P_BLANK] = -liveThree;
	value[P_BLANK][P_WHITE][P_WHITE][P_WHITE][P_BLANK][P_BLANK] = -liveThree;
	//眠四  只有一个位置的堵法
	value[P_BLANK][P_BLACK][P_BLACK][P_BLANK][P_BLACK][P_BLACK] = sleepFour;
	value[P_WHITE][P_BLACK][P_BLACK][P_BLANK][P_BLACK][P_BLACK] = sleepFour;
	value[P_BLANK][P_BLACK][P_BLANK][P_BLACK][P_BLACK][P_BLACK] = sleepFour;
	value[P_WHITE][P_BLACK][P_BLANK][P_BLACK][P_BLACK][P_BLACK] = sleepFour;
	value[P_BLANK][P_BLACK][P_BLACK][P_BLACK][P_BLANK][P_BLACK] = sleepFour;
	value[P_WHITE][P_BLACK][P_BLACK][P_BLACK][P_BLANK][P_BLACK] = sleepFour;
	value[P_BLANK][P_WHITE][P_WHITE][P_BLANK][P_WHITE][P_WHITE] = -sleepFour;
	value[P_BLACK][P_WHITE][P_WHITE][P_BLANK][P_WHITE][P_WHITE] = -sleepFour;
	value[P_BLANK][P_WHITE][P_BLANK][P_WHITE][P_WHITE][P_WHITE] = -sleepFour;
	value[P_BLACK][P_WHITE][P_BLANK][P_WHITE][P_WHITE][P_WHITE] = -sleepFour;
	value[P_BLANK][P_WHITE][P_WHITE][P_WHITE][P_BLANK][P_WHITE] = -sleepFour;
	value[P_BLACK][P_WHITE][P_WHITE][P_WHITE][P_BLANK][P_WHITE] = -sleepFour;
	//眠四  四子相连一边断
	value[P_WHITE][P_BLACK][P_BLACK][P_BLACK][P_BLACK][P_BLANK] = sleepFour;
	value[P_BLANK][P_BLACK][P_BLACK][P_BLACK][P_BLACK][P_WHITE] = sleepFour;
	value[P_BLACK][P_WHITE][P_WHITE][P_WHITE][P_WHITE][P_BLANK] = -sleepFour;
	value[P_BLANK][P_WHITE][P_WHITE][P_WHITE][P_WHITE][P_BLACK] = -sleepFour;
	//眠四  边界
	value[P_BOUND][P_BLACK][P_BLACK][P_BLACK][P_BLACK][P_BLANK] = sleepFour;
	value[P_BOUND][P_BLACK][P_BLACK][P_BLACK][P_BLANK][P_BLACK] = sleepFour;
	value[P_BOUND][P_BLACK][P_BLACK][P_BLANK][P_BLACK][P_BLACK] = sleepFour;
	value[P_BOUND][P_BLACK][P_BLANK][P_BLACK][P_BLACK][P_BLACK] = sleepFour;
	value[P_BOUND][P_WHITE][P_WHITE][P_WHITE][P_WHITE][P_BLANK] = -sleepFour;
	value[P_BOUND][P_WHITE][P_WHITE][P_WHITE][P_BLANK][P_WHITE] = -sleepFour;
	value[P_BOUND][P_WHITE][P_WHITE][P_BLANK][P_WHITE][P_WHITE] = -sleepFour;
	value[P_BOUND][P_WHITE][P_BLANK][P_WHITE][P_WHITE][P_WHITE] = -sleepFour;

	value[P_BLANK][P_BLACK][P_BLACK][P_BLACK][P_BLACK][P_BOUND] = sleepFour;
	value[P_BLACK][P_BLANK][P_BLACK][P_BLACK][P_BLACK][P_BOUND] = sleepFour;
	value[P_BLACK][P_BLACK][P_BLANK][P_BLACK][P_BLACK][P_BOUND] = sleepFour;
	value[P_BLACK][P_BLACK][P_BLACK][P_BLANK][P_BLACK][P_BOUND] = sleepFour;
	value[P_BLANK][P_WHITE][P_WHITE][P_WHITE][P_WHITE][P_BOUND] = -sleepFour;
	value[P_WHITE][P_BLANK][P_WHITE][P_WHITE][P_WHITE][P_BOUND] = -sleepFour;
	value[P_WHITE][P_WHITE][P_BLANK][P_WHITE][P_WHITE][P_BOUND] = -sleepFour;
	value[P_WHITE][P_WHITE][P_WHITE][P_BLANK][P_WHITE][P_BOUND] = -sleepFour;
	//眠三 
	value[P_WHITE][P_BLACK][P_BLANK][P_BLACK][P_BLANK][P_BLACK] = sleepThree;
	value[P_WHITE][P_BLACK][P_BLACK][P_BLACK][P_BLANK][P_BLANK] = sleepThree;
	value[P_WHITE][P_BLACK][P_BLACK][P_BLANK][P_BLACK][P_BLANK] = sleepThree;
	value[P_WHITE][P_BLACK][P_BLANK][P_BLACK][P_BLACK][P_BLANK] = sleepThree;
	value[P_BLACK][P_WHITE][P_BLANK][P_WHITE][P_BLANK][P_WHITE] = -sleepThree;
	value[P_BLACK][P_WHITE][P_WHITE][P_WHITE][P_BLANK][P_BLANK] = -sleepThree;
	value[P_BLACK][P_WHITE][P_WHITE][P_BLANK][P_WHITE][P_BLANK] = -sleepThree;
	value[P_BLACK][P_WHITE][P_BLANK][P_WHITE][P_WHITE][P_BLANK] = -sleepThree;
	 
	value[P_BLACK][P_BLANK][P_BLACK][P_BLANK][P_BLACK][P_WHITE] = sleepThree;
	value[P_BLANK][P_BLANK][P_BLACK][P_BLACK][P_BLACK][P_WHITE] = sleepThree;
	value[P_BLANK][P_BLACK][P_BLANK][P_BLACK][P_BLACK][P_WHITE] = sleepThree;
	value[P_BLANK][P_BLACK][P_BLACK][P_BLANK][P_BLACK][P_WHITE] = sleepThree;
	value[P_WHITE][P_BLANK][P_WHITE][P_BLANK][P_WHITE][P_BLACK] = -sleepThree;
	value[P_BLANK][P_BLANK][P_WHITE][P_WHITE][P_WHITE][P_BLACK] = -sleepThree;
	value[P_BLANK][P_WHITE][P_BLANK][P_WHITE][P_WHITE][P_BLACK] = -sleepThree;
	value[P_BLANK][P_WHITE][P_WHITE][P_BLANK][P_WHITE][P_BLACK] = -sleepThree;
	//眠三  边界
	value[P_BOUND][P_BLACK][P_BLACK][P_BLACK][P_BLANK][P_BLANK] = sleepThree;
	value[P_BOUND][P_BLACK][P_BLACK][P_BLANK][P_BLACK][P_BLANK] = sleepThree;
	value[P_BOUND][P_BLACK][P_BLANK][P_BLACK][P_BLACK][P_BLANK] = sleepThree;
	value[P_BOUND][P_WHITE][P_WHITE][P_WHITE][P_BLANK][P_BLANK] = -sleepThree;
	value[P_BOUND][P_WHITE][P_WHITE][P_BLANK][P_WHITE][P_BLANK] = -sleepThree;
	value[P_BOUND][P_WHITE][P_BLANK][P_WHITE][P_WHITE][P_BLANK] = -sleepThree;

	value[P_BLANK][P_BLANK][P_BLACK][P_BLACK][P_BLACK][P_BOUND] = sleepThree;
	value[P_BLANK][P_BLACK][P_BLANK][P_BLACK][P_BLACK][P_BOUND] = sleepThree;
	value[P_BLANK][P_BLACK][P_BLACK][P_BLANK][P_BLACK][P_BOUND] = sleepThree;
	value[P_BLANK][P_BLANK][P_WHITE][P_WHITE][P_WHITE][P_BOUND] = -sleepThree;
	value[P_BLANK][P_WHITE][P_BLANK][P_WHITE][P_WHITE][P_BOUND] = -sleepThree;
	value[P_BLANK][P_WHITE][P_WHITE][P_BLANK][P_WHITE][P_BOUND] = -sleepThree;
	//活二 
	value[P_BLANK][P_BLANK][P_BLANK][P_BLACK][P_BLACK][P_BLANK] = liveTwo;
	value[P_BLANK][P_BLANK][P_BLACK][P_BLANK][P_BLACK][P_BLANK] = liveTwo;
	value[P_BLANK][P_BLANK][P_BLACK][P_BLACK][P_BLANK][P_BLANK] = liveTwo;

	value[P_BLANK][P_BLANK][P_BLANK][P_BLACK][P_BLACK][P_BLANK] = liveTwo;
	value[P_BLANK][P_BLACK][P_BLANK][P_BLANK][P_BLACK][P_BLANK] = liveTwo;
	value[P_BLANK][P_BLACK][P_BLANK][P_BLACK][P_BLANK][P_BLANK] = liveTwo;

	value[P_BLANK][P_BLANK][P_BLACK][P_BLANK][P_BLACK][P_BLANK] = liveTwo;
	value[P_BLANK][P_BLACK][P_BLANK][P_BLANK][P_BLACK][P_BLANK] = liveTwo;
	value[P_BLANK][P_BLACK][P_BLACK][P_BLANK][P_BLANK][P_BLANK] = liveTwo;

	value[P_BLANK][P_BLANK][P_BLACK][P_BLACK][P_BLANK][P_BLANK] = liveTwo;
	value[P_BLANK][P_BLACK][P_BLANK][P_BLACK][P_BLANK][P_BLANK] = liveTwo;
	value[P_BLANK][P_BLACK][P_BLACK][P_BLANK][P_BLANK][P_BLANK] = liveTwo;

	value[P_BLANK][P_BLANK][P_BLANK][P_WHITE][P_WHITE][P_BLANK] = -liveTwo;
	value[P_BLANK][P_BLANK][P_WHITE][P_BLANK][P_WHITE][P_BLANK] = -liveTwo;
	value[P_BLANK][P_BLANK][P_WHITE][P_WHITE][P_BLANK][P_BLANK] = -liveTwo;

	value[P_BLANK][P_BLANK][P_BLANK][P_WHITE][P_WHITE][P_BLANK] = -liveTwo;
	value[P_BLANK][P_WHITE][P_BLANK][P_BLANK][P_WHITE][P_BLANK] = -liveTwo;
	value[P_BLANK][P_WHITE][P_BLANK][P_WHITE][P_BLANK][P_BLANK] = -liveTwo;

	value[P_BLANK][P_BLANK][P_WHITE][P_BLANK][P_WHITE][P_BLANK] = -liveTwo;
	value[P_BLANK][P_WHITE][P_BLANK][P_BLANK][P_WHITE][P_BLANK] = -liveTwo;
	value[P_BLANK][P_WHITE][P_WHITE][P_BLANK][P_BLANK][P_BLANK] = -liveTwo;

	value[P_BLANK][P_BLANK][P_WHITE][P_WHITE][P_BLANK][P_BLANK] = -liveTwo;
	value[P_BLANK][P_WHITE][P_BLANK][P_WHITE][P_BLANK][P_BLANK] = -liveTwo;
	value[P_BLANK][P_WHITE][P_WHITE][P_BLANK][P_BLANK][P_BLANK] = -liveTwo;
	//眠二 边界
	value[P_BOUND][P_BLACK][P_BLACK][P_BLANK][P_BLANK][P_BLANK] = sleepTwo;
	value[P_BOUND][P_BLACK][P_BLANK][P_BLACK][P_BLANK][P_BLANK] = sleepTwo;
	value[P_BOUND][P_BLACK][P_BLANK][P_BLANK][P_BLACK][P_BLANK] = sleepTwo;
	value[P_BOUND][P_BLACK][P_BLANK][P_BLANK][P_BLANK][P_BLACK] = sleepTwo;
	value[P_BOUND][P_WHITE][P_WHITE][P_BLANK][P_BLANK][P_BLANK] = -sleepTwo;
	value[P_BOUND][P_WHITE][P_BLANK][P_WHITE][P_BLANK][P_BLANK] = -sleepTwo;
	value[P_BOUND][P_WHITE][P_BLANK][P_BLANK][P_WHITE][P_BLANK] = -sleepTwo;
	value[P_BOUND][P_WHITE][P_BLANK][P_BLANK][P_BLANK][P_WHITE] = -sleepTwo;

	value[P_BLACK][P_BLANK][P_BLANK][P_BLANK][P_BLACK][P_BOUND] = sleepTwo;
	value[P_BLANK][P_BLACK][P_BLANK][P_BLANK][P_BLACK][P_BOUND] = sleepTwo;
	value[P_BLANK][P_BLANK][P_BLACK][P_BLANK][P_BLACK][P_BOUND] = sleepTwo;
	value[P_BLANK][P_BLANK][P_BLANK][P_BLACK][P_BLACK][P_BOUND] = sleepTwo;
	value[P_WHITE][P_BLANK][P_BLANK][P_BLANK][P_WHITE][P_BOUND] = -sleepTwo;
	value[P_BLANK][P_WHITE][P_BLANK][P_BLANK][P_WHITE][P_BOUND] = -sleepTwo;
	value[P_BLANK][P_BLANK][P_WHITE][P_BLANK][P_WHITE][P_BOUND] = -sleepTwo;
	value[P_BLANK][P_BLANK][P_BLANK][P_WHITE][P_WHITE][P_BOUND] = -sleepTwo;
	//眠二 
	value[P_WHITE][P_BLACK][P_BLACK][P_BLANK][P_BLANK][P_BLANK] = sleepTwo;
	value[P_WHITE][P_BLACK][P_BLANK][P_BLACK][P_BLANK][P_BLANK] = sleepTwo;
	value[P_WHITE][P_BLACK][P_BLANK][P_BLANK][P_BLACK][P_BLANK] = sleepTwo;
	value[P_WHITE][P_BLACK][P_BLANK][P_BLANK][P_BLANK][P_BLACK] = sleepTwo;
	value[P_BLACK][P_WHITE][P_WHITE][P_BLANK][P_BLANK][P_BLANK] = -sleepTwo;
	value[P_BLACK][P_WHITE][P_BLANK][P_WHITE][P_BLANK][P_BLANK] = -sleepTwo;
	value[P_BLACK][P_WHITE][P_BLANK][P_BLANK][P_WHITE][P_BLANK] = -sleepTwo;
	value[P_BLACK][P_WHITE][P_BLANK][P_BLANK][P_BLANK][P_WHITE] = -sleepTwo;

	value[P_BLACK][P_BLANK][P_BLANK][P_BLANK][P_BLACK][P_WHITE] = sleepTwo;
	value[P_BLANK][P_BLACK][P_BLANK][P_BLANK][P_BLACK][P_WHITE] = sleepTwo;
	value[P_BLANK][P_BLANK][P_BLACK][P_BLANK][P_BLACK][P_WHITE] = sleepTwo;
	value[P_BLANK][P_BLANK][P_BLANK][P_BLACK][P_BLACK][P_WHITE] = sleepTwo;
	value[P_WHITE][P_BLANK][P_BLANK][P_BLANK][P_WHITE][P_BLACK] = -sleepTwo;
	value[P_BLANK][P_WHITE][P_BLANK][P_BLANK][P_WHITE][P_BLACK] = -sleepTwo;
	value[P_BLANK][P_BLANK][P_WHITE][P_BLANK][P_WHITE][P_BLACK] = -sleepTwo;
	value[P_BLANK][P_BLANK][P_BLANK][P_WHITE][P_WHITE][P_BLACK] = -sleepTwo;
	//活一
	value[P_WHITE][P_BLANK][P_BLACK][P_BLANK][P_BLANK][P_BLANK] = liveOne;
	value[P_WHITE][P_BLANK][P_BLANK][P_BLACK][P_BLANK][P_BLANK] = liveOne;
	value[P_WHITE][P_BLANK][P_BLANK][P_BLANK][P_BLACK][P_BLANK] = liveOne;
	value[P_BLACK][P_BLANK][P_WHITE][P_BLANK][P_BLANK][P_BLANK] = -liveOne;
	value[P_BLACK][P_BLANK][P_BLANK][P_WHITE][P_BLANK][P_BLANK] = -liveOne;
	value[P_BLACK][P_BLANK][P_BLANK][P_BLANK][P_WHITE][P_BLANK] = -liveOne;

	value[P_BLANK][P_BLACK][P_BLANK][P_BLANK][P_BLANK][P_WHITE] = liveOne;
	value[P_BLANK][P_BLANK][P_BLACK][P_BLANK][P_BLANK][P_WHITE] = liveOne;
	value[P_BLANK][P_BLANK][P_BLANK][P_BLACK][P_BLANK][P_WHITE] = liveOne;
	value[P_BLANK][P_WHITE][P_BLANK][P_BLANK][P_BLANK][P_BLACK] = -liveOne;
	value[P_BLANK][P_BLANK][P_WHITE][P_BLANK][P_BLANK][P_BLACK] = -liveOne;
	value[P_BLANK][P_BLANK][P_BLANK][P_WHITE][P_BLANK][P_BLACK] = -liveOne;
	//活一边界
	value[P_BOUND][P_BLANK][P_BLACK][P_BLANK][P_BLANK][P_BLANK] = liveOne;
	value[P_BOUND][P_BLANK][P_BLANK][P_BLACK][P_BLANK][P_BLANK] = liveOne;
	value[P_BOUND][P_BLANK][P_BLANK][P_BLANK][P_BLACK][P_BLANK] = liveOne;
	value[P_BOUND][P_BLANK][P_WHITE][P_BLANK][P_BLANK][P_BLANK] = -liveOne;
	value[P_BOUND][P_BLANK][P_BLANK][P_WHITE][P_BLANK][P_BLANK] = -liveOne;
	value[P_BOUND][P_BLANK][P_BLANK][P_BLANK][P_WHITE][P_BLANK] = -liveOne;

	value[P_BLANK][P_BLACK][P_BLANK][P_BLANK][P_BLANK][P_BOUND] = liveOne;
	value[P_BLANK][P_BLANK][P_BLACK][P_BLANK][P_BLANK][P_BOUND] = liveOne;
	value[P_BLANK][P_BLANK][P_BLANK][P_BLACK][P_BLANK][P_BOUND] = liveOne;
	value[P_BLANK][P_WHITE][P_BLANK][P_BLANK][P_BLANK][P_BOUND] = -liveOne;
	value[P_BLANK][P_BLANK][P_WHITE][P_BLANK][P_BLANK][P_BOUND] = -liveOne;
	value[P_BLANK][P_BLANK][P_BLANK][P_WHITE][P_BLANK][P_BOUND] = -liveOne;

}

int boardValueEvaluate() {
	int totalvalue=0;
	for (int i = 0; i < CbIntNum; i++)
	{
		for (int j = 0; j < CbIntNum; j++)
		{
			BoardValue[i][j]=0;
		}
	}
	//直线边界
	for (int i = 0; i < CbIntNum; i++)
	{
		BoardValue[i][0] += value[P_BOUND][BoardKey[i][0]][BoardKey[i][1]][BoardKey[i][2]][BoardKey[i][3]][BoardKey[i][4]];
		BoardValue[0][i] += value[P_BOUND][BoardKey[0][i]][BoardKey[1][i]][BoardKey[2][i]][BoardKey[3][i]][BoardKey[4][i]];
		BoardValue[i][10] += value[BoardKey[i][10]][BoardKey[i][11]][BoardKey[i][12]][BoardKey[i][13]][BoardKey[i][14]][P_BOUND];
		BoardValue[10][i] += value[BoardKey[10][i]][BoardKey[11][i]][BoardKey[12][i]][BoardKey[13][i]][BoardKey[14][i]][P_BOUND];
	}
	//斜线边界
	for (int i = 0; i < CbBoardValueNum+1; i++)
	{
		BoardValue[i][10] += value[BoardKey[i][10]][BoardKey[i + 1][11]][BoardKey[i + 2][12]][BoardKey[i + 3][13]][BoardKey[i + 4][14]][P_BOUND];
		BoardValue[10][i] += value[BoardKey[10][i]][BoardKey[11][i + 1]][BoardKey[12][i + 2]][BoardKey[13][i + 3]][BoardKey[14][i + 4]][P_BOUND];
		BoardValue[i][4] += value[P_BOUND][BoardKey[i + 4][0]][BoardKey[i + 3][1]][BoardKey[i + 2][2]][BoardKey[i + 1][3]][BoardKey[i][4]];
		BoardValue[10][14 - i] += value[P_BOUND][BoardKey[14][10 - i]][BoardKey[13][11 - i]][BoardKey[12][12 - i]][BoardKey[11][13 - i]][BoardKey[10][14 - i]];
	}
	//直线棋盘遍历
	for (int i = 0; i < CbBoardValueNum; i++)
	{
		for (int j = 0; j < CbIntNum; j++)
		{
			BoardValue[i][j] += value[BoardKey[i][j]][BoardKey[i + 1][j]][BoardKey[i + 2][j]][BoardKey[i + 3][j]][BoardKey[i + 4][j]][BoardKey[i + 5][j]];
			BoardValue[j][i] += value[BoardKey[j][i]][BoardKey[j][i + 1]][BoardKey[j][i + 2]][BoardKey[j][i + 3]][BoardKey[j][i + 4]][BoardKey[j][i + 5]];
		}
	}
	//斜线棋盘遍历
	for (int i = 0; i < CbBoardValueNum; i++)
	{
		for (int j = 0; j < CbBoardValueNum; j++)
		{
			BoardValue[i][j] += value[BoardKey[i][j]][BoardKey[i + 1][j + 1]][BoardKey[i + 2][j + 2]][BoardKey[i + 3][j + 3]][BoardKey[i + 4][j + 4]][BoardKey[i + 5][j + 5]];
			BoardValue[i][14 - j] += value[BoardKey[i][14 - j]][BoardKey[i + 1][13 - j]][BoardKey[i + 2][12 - j]][BoardKey[i + 3][11 - j]][BoardKey[i + 4][10 - j]][BoardKey[i + 5][9 - j]];
		}
	}
	//遍历棋盘相加
	for (int i = 0; i < CbIntNum; i++)
	{
		for (int j = 0; j < CbIntNum; j++)
		{
			totalvalue += BoardValue[i][j];
		}
	}
	return totalvalue;
}

int gamewin() {
	for (int i = 0; i < CbIntNum; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			if ((BoardKey[i][j] == P_BLACK) && (BoardKey[i][j + 1] == P_BLACK) && (BoardKey[i][j + 2] == P_BLACK) && (BoardKey[i][j + 3] == P_BLACK) && (BoardKey[i][j + 4] == P_BLACK))
			{
				return 1;
			}
			if ((BoardKey[i][j] == P_WHITE) && (BoardKey[i][j + 1] == P_WHITE) && (BoardKey[i][j + 2] == P_WHITE) && (BoardKey[i][j + 3] == P_WHITE) && (BoardKey[i][j + 4] == P_WHITE))
			{
				return 2;
			}
			if ((BoardKey[j][i] == P_BLACK) && (BoardKey[j + 1][i] == P_BLACK) && (BoardKey[j + 2][i] == P_BLACK) && (BoardKey[j + 3][i] == P_BLACK) && (BoardKey[j + 4][i] == P_BLACK))
			{
				return 1;
			}
			if ((BoardKey[j][i] == P_WHITE) && (BoardKey[j + 1][i] == P_WHITE) && (BoardKey[j + 2][i] == P_WHITE) && (BoardKey[j + 3][i] == P_WHITE) && (BoardKey[j + 4][i] == P_WHITE))
			{
				return 2;
			}

		}
	}
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			if ((BoardKey[i][j] == P_BLACK) && (BoardKey[i + 1][j + 1] == P_BLACK) && (BoardKey[i + 2][j + 2] == P_BLACK) && (BoardKey[i + 3][j + 3] == P_BLACK) && (BoardKey[i + 4][j + 4] == P_BLACK))
			{
				return 1;
			}
			if ((BoardKey[i][j] == P_WHITE) && (BoardKey[i + 1][j + 1] == P_WHITE) && (BoardKey[i + 2][j + 2] == P_WHITE) && (BoardKey[i + 3][j + 3] == P_WHITE) && (BoardKey[i + 4][j + 4] == P_WHITE))
			{
				return 2;
			}
			if ((BoardKey[i + 4][j] == P_BLACK) && (BoardKey[i + 3][j + 1] == P_BLACK) && (BoardKey[i + 2][j + 2] == P_BLACK) && (BoardKey[i + 1][j + 3] == P_BLACK) && (BoardKey[i][j + 4] == P_BLACK))
			{
				return 1;
			}
			if ((BoardKey[i + 4][j] == P_WHITE) && (BoardKey[i + 3][j + 1] == P_WHITE) && (BoardKey[i + 2][j + 2] == P_WHITE) && (BoardKey[i + 1][j + 3] == P_WHITE) && (BoardKey[i][j + 4] == P_WHITE))
			{
				return 2;
			}
		}
	}
	return 0;
}

int main()
{
	BoardKey[7][7] = P_WHITE; 
	BoardKey[7][8] = P_WHITE;
	BoardKey[7][9] = P_WHITE;
	BoardKey[7][10] = P_WHITE;
	
	valueInitialization();
	drawCb();
	WhoGo = P_BLACKMove;
	drawPiece(7, 7, P_WHITE);
	drawPiece(7, 8, P_WHITE);
	drawPiece(7, 9, P_WHITE);
	drawPiece(7, 10, P_WHITE);
	while (1)
	{
		if (WhoGo == P_BLACKMove)
		{
			// 玩家下棋
			MOUSEMSG mouse = GetMouseMsg(); // 获取鼠标信息
			for (int i = 0; i < CbIntNum; i++)
			{
				for (int j = 0; j < CbIntNum; j++)
				{
					if (IsBLANK(mouse,i,j))
					{
						// 如果停在某一个空位置上面
						if (mouse.mkLButton)
						{
							// 如果按下了
							BoardKey[i][j] = P_BLACK; // 下棋
							drawPiece(i, j, P_BLACK);   // 新位置更新
							// 下一个玩家
							WhoGo = P_WHITEMove;
							if (gamewin() != 0)
							{
								break;
							}
						}
					}
				}
			}
		}
		
		if (WhoGo == P_WHITEMove)
		{
			// 电脑下棋
			LPoint Best;
			LPLink* pp;
			pp = GenerateLegalMoves();
			Best = ChoseBest(pp, WhoGo); // 寻找最佳位置
			BoardKey[Best.y][Best.x] = P_WHITE; // 下棋
			drawPiece(Best.y, Best.x, P_WHITE);
			WhoGo = P_BLACKMove;
			if (gamewin() != 0)
			{
				break;
			}
		}
	}
	if (gamewin() == 2)
	{
		outtextxy(320, 320, _T("白胜"));
	}
	if (gamewin() == 1)
	{
		outtextxy(320, 320, _T("黑胜"));
	}
	Sleep(5000);
	closegraph();			// 关闭绘图窗口
	return 0;
}
