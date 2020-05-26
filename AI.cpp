#include"AI.h"

AI::AI():game_status(true),role(WHITE),count(1),head(EMPTY),end(EMPTY)
{
	for(int i = 0 ; i < BoardLength;i++)
		for (int j = 0; j < BoardLength; j++)
		{
			ai_score_board[i][j] = 0;
			hum_score_board[i][j] = 0;
			game_board[i][j] = 0;
			score_board[i][j] = -INF;
		}
	same_score_chess.push_back(best);
}

void AI::ReserveRole()
{
	if (role == BLACK)	role = WHITE;
	else role = BLACK;
}

//接口函数
void AI::UpdateBoard(int x, int y,Turns t)		//更新落子点
{
	game_board[x][y] = t;
	UpdateScore();
	if (Evaluate(BLACK) > FIVE || Evaluate(WHITE) > FIVE)
		game_status = false;
	//ReserveRole();
}

bool AI::GamingOrNot()
{
	return game_status;
}


void AI::ResetData()
{
	count = 1;
	head = EMPTY;
	end = EMPTY;
}

//对单点进行评估
int AI::EvaluateGreedy(int x, int y,Turns color)
{
	int result = 0;
	//横 先->  再<-
	ResetData();
	for (int i = 1; i <= 4; i++)
	{
		if (y + i >= BoardLength || game_board[x][y + i] == opponent(color)) {
			head = BLOCK;
			break;
		}
		if (game_board[x][y + i] == EMPTY) {
			head = EMPTY;
			break;
		}
		if (game_board[x][y + i] == color)
			count++;
	}
	for (int i = 1; i <= 4; i++)
	{
		if (y - i < 0 || game_board[x][y - i] == opponent(color)) {
			end = BLOCK;
			break;
		}
		if (game_board[x][y - i] == EMPTY) {
			end = EMPTY;
			break;
		}
		if (game_board[x][y - i] == color)
			count++;
	}
	result += TurnToScore(count, head, end);

	//竖 先下后上
	ResetData();
	for (int i = 1; i <= 4; i++)
	{
		if (x + i >= BoardLength || game_board[x + i][y] == opponent(color)) {
			head = BLOCK;
			break;
		}
		if (game_board[x + i][y] == EMPTY) {
			head = EMPTY;
			break;
		}
		if (game_board[x + i][y] == color)
			count++;
	}
	for (int i = 1; i <= 4; i++)
	{
		if (x - i < 0 || game_board[x - i][y] == opponent(color)) {
			end = BLOCK;
			break;
		}
		if (game_board[x - i][y] == EMPTY) {
			end = EMPTY;
			break;
		}
		if (game_board[x - i][y] == color)
			count++;
	}
	result += TurnToScore(count, head, end);

	// / 先左下再右上
	ResetData();
	for (int i = 1; i <= 4; i++)
	{
		if (x + i >= BoardLength || y - i < 0 || game_board[x + i][y - i] == opponent(color)) {
			head = BLOCK;
			break;
		}
		if (game_board[x + i][y - i] == EMPTY) {
			head = EMPTY;
			break;
		}
		if (game_board[x + i][y - i] == color)
			count++;
	}
	for (int i = 1; i <= 4; i++)
	{
		if (x - i < 0 || y + i >= BoardLength || game_board[x - i][y + i] == opponent(color)) {
			end = BLOCK;
			break;
		}
		if (game_board[x - i][y + i] == EMPTY) {
			end = EMPTY;
			break;
		}
		if (game_board[x - i][y + i] == color)
			count++;
	}
	result += TurnToScore(count, head, end);

	// \ 先左下再右上
	ResetData();
	for (int i = 1; i <= 4; i++)
	{
		if (x + i >= BoardLength || y + i >= BoardLength || game_board[x + i][y + i] == opponent(color)) {
			head = BLOCK;
			break;
		}
		if (game_board[x + i][y + i] == EMPTY) {
			head = EMPTY;
			break;
		}
		if (game_board[x + i][y + i] == color)
			count++;
	}
	for (int i = 1; i <= 4; i++)
	{
		if (x - i < 0 || y - i < 0 || game_board[x - i][y - i] == opponent(color)) {
			end = BLOCK;
			break;
		}
		if (game_board[x - i][y - i] == EMPTY) {
			end = EMPTY;
			break;
		}
		if (game_board[x - i][y - i] == color)
			count++;
	}
	result += TurnToScore(count, head, end);
	return result;
}

//把单点评分数据转换为分数
int AI::TurnToScore(int cnt, Edge_Status h, Edge_Status e)
{
	if (cnt >= 5)
		return FIVE;

	if (cnt == 4)		//用if把前面所有的可能性都排掉，剩下的归为一种
	{
		if (h == EMPTY && e == EMPTY)//两边空 活四
			return FOUR;
		else if (h == BLOCK && e == BLOCK)//两边堵 没用
			return NOTHREAT;
		else//剩下的自然是冲四
			return BLOCKED_FOUR;
	}

	if (cnt == 3)
	{
		if (h == EMPTY && e == EMPTY)//两边空 活三
			return THREE;
		else if (h == BLOCK && e == BLOCK)//两边堵 没用
			return NOTHREAT;
		else//剩下的自然是冲三
			return BLOCKED_THREE;
	}
	if (cnt == 2)
	{
		if (h == EMPTY && e == EMPTY)//两边空 活二
			return TWO;
		else if (h == BLOCK && e == BLOCK)//两边堵 没用
			return NOTHREAT;
		else//
			return BLOCKED_TWO;
	}
	if (cnt == 1)
	{
		if (h == EMPTY && e == EMPTY)//两边空 正常一
			return NOTHREAT;
		else if (h == BLOCK && e == BLOCK)//两边堵 没用
			return NOTHREAT;
		else//
			return BLOCKED_ONE;
	}
}

//贪心算法中的更新函数，即单点更新函数
void AI::UpdateScoreGreedy()
{
	best.score = 0;
	for(int i = 0 ; i < BoardLength;i++)			//遍历棋盘为每个空位估分
		for (int j = 0; j < BoardLength; j++)
		{
			if (game_board[i][j] == EMPTY)//空位估分
			{
				score_board[i][j] = EvaluateGreedy(i, j, BLACK) + EvaluateGreedy(i, j, WHITE);

				if (score_board[i][j] > best.score)
				{
					best.score = score_board[i][j];
					best.x = i;
					best.y = j;
					same_score_chess.clear();
					same_score_chess.push_back(best);
				}
				if (score_board[i][j] == best.score)
				{
					best.score = score_board[i][j];
					best.x = i;
					best.y = j;
					same_score_chess.push_back(best);
				}
				
				int human = EvaluateGreedy(i, j, WHITE);
				int bot = EvaluateGreedy(i, j, BLACK);
			}
		}
}

//minmax算法中的更新函数
/*我的更新策略：1.先通过gen函数对可下子点进行估值排序，选前10最优个点
	2.对于每个点进行“预下棋”
	3.在分数数组中用minimax对预下棋后的棋子分数进行估值（在这一点）
		i)若该棋子分数高于最高点，将最高点设为它
		ii)若该棋子分数等于最高点，将其放入最优棋子的vector中
	4.删除该棋子
*/
void AI::UpdateScore()
{
	best.score = -INF;
	for (int i = 0; i < BoardLength; i++)
		for (int j = 0; j < BoardLength; j++)
		{
			score_board[i][j] = -INF;
		}

	std::vector<Chess> points;
	gen(points, BLACK);
	for (int i = 0; i < 10; i++)
	{
		game_board[points[i].x][points[i].y] = BLACK;
		score_board[points[i].x][points[i].y] = minimax(DEPTH - 1, -INF, INF, false);//
		if (score_board[points[i].x][points[i].y] > best.score)
		{
			best.score = score_board[points[i].x][points[i].y];
			best.x = points[i].x;
			best.y = points[i].y;
			same_score_chess.clear();
			same_score_chess.push_back(best);
		}
		if (score_board[points[i].x][points[i].y] == best.score)
		{
			best.score = score_board[points[i].x][points[i].y];
			best.x = points[i].x;
			best.y = points[i].y;
			same_score_chess.push_back(best);
		}
		game_board[points[i].x][points[i].y] = EMPTY;
	}

}

//将棋子储存序列中的最好的棋子输出
Chess& AI::BestChess()
{
	srand((unsigned)time(0));
	int i = rand() % same_score_chess.size();
	game_board[same_score_chess[i].x][same_score_chess[i].y] = BLACK;
	if (Evaluate(BLACK) > FIVE || Evaluate(WHITE) > FIVE)
		game_status = false;
	return same_score_chess[i];
}

//alpha含义：（白棋利益最大化/遏制黑棋利益）最大-的上限    beta含义：（黑棋利益最大化/遏制白棋利益）最小-的下限   
//传递时alpha 和 beta的值是暂定的
//max层取max，并往_上_返回其取值（max），  min层同理
//当在max层中发现alpha大于beta，即（白棋的利益）大于（黑棋的利益），那么在其上一层（黑棋层min取最小），肯定会遏制白棋利益，不下这个棋，所以说讨论之后的无效，剪枝
//当在min层中发现alpha大于beta，（黑棋的alpha由白棋传递过来，白棋的alpha由其下黑棋的beta确定）（黑棋alpha由之前黑棋确定），即黑棋这步的利益没有黑棋上一步高，白棋为了利益最大化肯定不会下，所以剪枝
//不用存预测后的棋，你不是跳大神的
/*我的minimax更新策略（递归）
	0.判断层数是否到头，到头后返回当前局势下的分数
	1.gen后预下棋
	2.
	
*/
int AI::minimax(int depth, int alpha, int beta, bool maxmizingPlayer)
{
	if (depth == 0)
		return Evaluate(BLACK);//极大极小默认设置偶数层，black代表电脑

	std::vector<Chess> points;

	if (maxmizingPlayer)
	{
		int maxEval = -1000000;			//设置一个负无穷值保证不被取到	  为什么？ 极大搜索判断条件是alpha大于beta时停止，代表对手有更好选择
		gen(points, BLACK);
		for (int i = 0; i < 10; i++)
		{
			game_board[points[i].x][points[i].y] = BLACK;
			int eval =  minimax(depth - 1, alpha, beta, false);
			game_board[points[i].x][points[i].y] = EMPTY;
			if (eval != 0) {
				maxEval = maxEval > eval ? maxEval : eval;						//返回值
				alpha = alpha > eval ? alpha : eval;							//传递的值，仅用于判断剪枝
			}
			if (beta <= alpha)
				break;
		}
		return maxEval;
	}
	else{
		int minEval = 1000000;
		gen(points, WHITE);
		for (int i = 0; i < 10; i++)
		{
			game_board[points[i].x][points[i].y] = WHITE;
			int eval = minimax(depth - 1, alpha, beta, true);
			game_board[points[i].x][points[i].y] = EMPTY;
			if (eval != 0) {
				minEval = minEval < eval ? minEval : eval;
				beta = beta < eval ? beta : eval;
			}
			if (beta <= alpha)
				break;
		}
		return minEval;
	}
}

//判断棋子周围两个棋子是否有棋子
bool AI::HasNeighbour(int x, int y)
{
	int neighbour = 0;
	for (int i = -2; i <= 2; i++)
	{
		for (int j = -2; j <= 2; j++)
		{
			if (y + j >= BoardLength || y + j < 0 || x + i >= BoardLength || x + i < 0 || game_board[x + i][y + j] == EMPTY)
				continue;
			else if (i == 0 && j == 0)	continue;
			else if (game_board[x + i][y + j] == 0) continue;
			else neighbour++;
		}
	}

	return neighbour != 0;
}

//把棋子周围的点进行分值排序后返回给minimax以加快剪枝速度
void AI::gen(std::vector<Chess>& v, Turns t)
{
	Chess c;
	for (int i = 0; i < BoardLength; i++)
	{
		for (int j = 0; j < BoardLength; j++)
		{
			if (game_board[i][j] == EMPTY && HasNeighbour(i, j))
			{
				c.score = EvaluateGreedy(i, j, t)+EvaluateGreedy(i,j,opponent(t));			//进攻加防守
				c.x = i;
				c.y = j;
				v.push_back(c);
			}
		}
	}
	sort(v);
}

//minimax中的全局评分函数
//判断该种颜色的棋子的棋形有多少（所以是已落子点）
int AI::Evaluate(Turns t)
{
	int score = 0;
	for (int i = 0; i < BoardLength; i++)
		for (int j = 0; j < BoardLength; j++)
		{
			if (game_board[i][j] == t)
				score += EvaluateGreedy(i, j, t);
			else if (game_board[i][j] == opponent(t))
				score -= EvaluateGreedy(i, j, opponent(t));
		}
	return score;
}

//用于gen函数中的排序
void AI::sort(std::vector<Chess>& v)			//排序
{
	for (int i = 0; i < v.size() - 1; i++)
	{
		for (int j = 0; j < v.size() - i - 1; j++)
		if (v[j].score < v[j + 1].score) {
			Chess t = v[j + 1];
			v[j + 1] = v[j];
			v[j] = t;
		}
	}
}

//5.20 更改了剪枝顺序防止跳过
//更改了inf大小防止不够大