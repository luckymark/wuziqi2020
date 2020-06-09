#include "ChessAI.h"
#include <cstdlib>
enum {
	OTHER,
	WIN,
	LOSE,
	FLEX4,
	flex4,
	BLOCK4,
	block4,
	FLEX3,
	flex3,
	BLOCK3,
	block3,
	FLEX2,
	flex2,
	BLOCK2,
	block2,
	FLEX1,
	flex1
};
int chess_type[4][4][4][4][4][4];
const long long VALUE[] = {
	0,
	1000000,
	-10000000,
	50000,
	-100000,
	400,
	-100000,
	400,
	-8000,
	20,
	-50,
	20,
	-50,
	1,
	-3,
	1,
	-3
};//估分表

//0表空，1表自己，2表敌方（棋形表）


void ChessAI::init_typescore()
{
	memset(chess_type, 0, sizeof(chess_type));
	//白连5,ai赢
	chess_type[2][2][2][2][2][2] = WIN;
	chess_type[2][2][2][2][2][0] = WIN;
	chess_type[0][2][2][2][2][2] = WIN;
	chess_type[2][2][2][2][2][1] = WIN;
	chess_type[1][2][2][2][2][2] = WIN;
	chess_type[3][2][2][2][2][2] = WIN;
	chess_type[2][2][2][2][2][3] = WIN;
	//黑连5,ai输
	chess_type[1][1][1][1][1][1] = LOSE;
	chess_type[1][1][1][1][1][0] = LOSE;
	chess_type[0][1][1][1][1][1] = LOSE;
	chess_type[1][1][1][1][1][2] = LOSE;
	chess_type[2][1][1][1][1][1] = LOSE;
	chess_type[3][1][1][1][1][1] = LOSE;
	chess_type[1][1][1][1][1][3] = LOSE;
	//白活4
	chess_type[0][2][2][2][2][0] = FLEX4;
	//黑活4
	chess_type[0][1][1][1][1][0] = flex4;
	//白活3
	chess_type[0][2][2][2][0][0] = FLEX3;
	chess_type[0][0][2][2][2][0] = FLEX3;
	chess_type[0][2][0][2][2][0] = FLEX3;
	chess_type[0][2][2][0][2][0] = FLEX3;
	//黑活3
	chess_type[0][1][1][1][0][0] = flex3;
	chess_type[0][0][1][1][1][0] = flex3;
	chess_type[0][1][0][1][1][0] = flex3;
	chess_type[0][1][1][0][1][0] = flex3;
	//白活2
	chess_type[0][2][2][0][0][0] = FLEX2;
	chess_type[0][2][0][2][0][0] = FLEX2;
	chess_type[0][2][0][0][2][0] = FLEX2;
	chess_type[0][0][2][2][0][0] = FLEX2;
	chess_type[0][0][2][0][2][0] = FLEX2;
	chess_type[0][0][0][2][2][0] = FLEX2;
	//黑活2
	chess_type[0][1][1][0][0][0] = flex2;
	chess_type[0][1][0][1][0][0] = flex2;
	chess_type[0][1][0][0][1][0] = flex2;
	chess_type[0][0][1][1][0][0] = flex2;
	chess_type[0][0][1][0][1][0] = flex2;
	chess_type[0][0][0][1][1][0] = flex2;
	//白活1
	chess_type[0][2][0][0][0][0] = FLEX1;
	chess_type[0][0][2][0][0][0] = FLEX1;
	chess_type[0][0][0][2][0][0] = FLEX1;
	chess_type[0][0][0][0][2][0] = FLEX1;
	//黑活1
	chess_type[0][1][0][0][0][0] = flex1;
	chess_type[0][0][1][0][0][0] = flex1;
	chess_type[0][0][0][1][0][0] = flex1;
	chess_type[0][0][0][0][1][0] = flex1;

	int p1, p2, p3, p4, p5, p6, x, y, ix, iy;//x:左5中黑个数,y:左5中白个数,ix:右5中黑个数,iy:右5中白个数
	for (p1 = 0;p1 < 4;++p1) {
		for (p2 = 0;p2 < 3;++p2) {
			for (p3 = 0;p3 < 3;++p3) {
				for (p4 = 0;p4 < 3;++p4) {
					for (p5 = 0;p5 < 3;++p5) {
						for (p6 = 0;p6 < 4;++p6) {
							x = y = ix = iy = 0;

							if (p1 == 1)x++;
							else if (p1 == 2)y++;

							if (p2 == 1) { x++;ix++; }
							else if (p2 == 2) { y++;iy++; }

							if (p3 == 1) { x++;ix++; }
							else if (p3 == 2) { y++;iy++; }

							if (p4 == 1) { x++;ix++; }
							else if (p4 == 2) { y++;iy++; }

							if (p5 == 1) { x++;ix++; }
							else if (p5 == 2) { y++;iy++; }

							if (p6 == 1)ix++;
							else if (p6 == 2)iy++;

							if (p1 == 3 || p6 == 3) {//有边界
								if (p1 == 3 && p6 != 3) {//左边界
									//白冲4
									if (ix == 0 && iy == 4) {//若右边有空位是活4也没关系，因为活4权重远大于冲4，再加上冲4权重变化可以不计
										if (chess_type[p1][p2][p3][p4][p5][p6] == 0)
											chess_type[p1][p2][p3][p4][p5][p6] = BLOCK4;
									}
									//黑冲4
									if (ix == 4 && iy == 0) {
										if (chess_type[p1][p2][p3][p4][p5][p6] == 0)
											chess_type[p1][p2][p3][p4][p5][p6] = block4;
									}
									//白眠3
									if (ix == 0 && iy == 3) {
										if (chess_type[p1][p2][p3][p4][p5][p6] == 0)
											chess_type[p1][p2][p3][p4][p5][p6] = BLOCK3;
									}
									//黑眠3
									if (ix == 3 && iy == 0) {
										if (chess_type[p1][p2][p3][p4][p5][p6] == 0)
											chess_type[p1][p2][p3][p4][p5][p6] = block3;
									}
									//白眠2
									if (ix == 0 && iy == 2) {
										if (chess_type[p1][p2][p3][p4][p5][p6] == 0)
											chess_type[p1][p2][p3][p4][p5][p6] = BLOCK2;
									}
									//黑眠2
									if (ix == 2 && iy == 0) {
										if (chess_type[p1][p2][p3][p4][p5][p6] == 0)
											chess_type[p1][p2][p3][p4][p5][p6] = block2;
									}
								}
								else if (p6 == 3 && p1 != 3) {//右边界
								   //白冲4
									if (x == 0 && y == 4) {
										if (chess_type[p1][p2][p3][p4][p5][p6] == 0)
											chess_type[p1][p2][p3][p4][p5][p6] = BLOCK4;
									}
									//黑冲4
									if (x == 4 && y == 0) {
										if (chess_type[p1][p2][p3][p4][p5][p6] == 0)
											chess_type[p1][p2][p3][p4][p5][p6] = block4;
									}
									//黑眠3
									if (x == 3 && y == 0) {
										if (chess_type[p1][p2][p3][p4][p5][p6] == 0)
											chess_type[p1][p2][p3][p4][p5][p6] = BLOCK3;
									}
									//白眠3
									if (x == 0 && y == 3) {
										if (chess_type[p1][p2][p3][p4][p5][p6] == 0)
											chess_type[p1][p2][p3][p4][p5][p6] = block3;
									}
									//黑眠2
									if (x == 2 && y == 0) {
										if (chess_type[p1][p2][p3][p4][p5][p6] == 0)
											chess_type[p1][p2][p3][p4][p5][p6] = BLOCK2;
									}
									//白眠2
									if (x == 0 && y == 2) {
										if (chess_type[p1][p2][p3][p4][p5][p6] == 0)
											chess_type[p1][p2][p3][p4][p5][p6] = block2;
									}
								}
							}
							else {//无边界
							   //白冲4
								if ((x == 0 && y == 4) || (ix == 0 && iy == 4)) {
									if (chess_type[p1][p2][p3][p4][p5][p6] == 0)
										chess_type[p1][p2][p3][p4][p5][p6] = BLOCK4;
								}
								//黑冲4
								if ((x == 4 && y == 0) || (ix == 4 && iy == 0)) {
									if (chess_type[p1][p2][p3][p4][p5][p6] == 0)
										chess_type[p1][p2][p3][p4][p5][p6] = block4;
								}
								//白眠3
								if ((x == 0 && y == 3) || (ix == 0 && iy == 3)) {
									if (chess_type[p1][p2][p3][p4][p5][p6] == 0)
										chess_type[p1][p2][p3][p4][p5][p6] = BLOCK3;
								}
								//黑眠3
								if ((x == 3 && y == 0) || (ix == 3 && iy == 0)) {
									if (chess_type[p1][p2][p3][p4][p5][p6] == 0)
										chess_type[p1][p2][p3][p4][p5][p6] = block3;
								}
								//白眠2
								if ((x == 0 && y == 2) || (ix == 0 && iy == 2)) {
									if (chess_type[p1][p2][p3][p4][p5][p6] == 0)
										chess_type[p1][p2][p3][p4][p5][p6] = BLOCK2;
								}
								//黑眠2
								if ((x == 2 && y == 0) || (ix == 2 && iy == 0)) {
									if (chess_type[p1][p2][p3][p4][p5][p6] == 0)
										chess_type[p1][p2][p3][p4][p5][p6] = block2;
								}
							}
						}
					}
				}
			}
		}
	}
}

EVALUATION ChessAI::get_score(Checkerboard& board)
{
	int stat[4][17];//四个方向上的棋型
	memset(stat, 0, sizeof(stat));

	int STAT[17];//存某个方向的棋型
	memset(STAT, 0, sizeof(STAT));

	int Board[17][17];	//用来加入边界
	for (int i = 0;i < 17;i++) {
		Board[i][0] = 3;
		Board[i][16] = 3;
		Board[0][i] = 3;
		Board[16][i] = 3;
	}
	for (int i = 1; i < 16;i++) {
		for (int j = 1; j < 16; j++)
		{
			Board[i][j] = board.board[i][j];
		}	
	}
	int i,j,type;//稍微加点速度移到外面来。
	//判断横向棋型
	for (i = 1;i <= 15;++i) {
		for (j = 0;j < 12;++j) {
			type = chess_type[Board[i][j]][Board[i][j + 1]][Board[i][j + 2]][Board[i][j + 3]][Board[i][j + 4]][Board[i][j + 5]];
			stat[0][type]++;
		}
	}
	//判断竖向棋型
	for (j = 1;j <= 15;++j) {
		for (i = 0;i < 12;++i) {
			type = chess_type[Board[i][j]][Board[i + 1][j]][Board[i + 2][j]][Board[i + 3][j]][Board[i + 4][j]][Board[i + 5][j]];
			stat[1][type]++;
		}
	}
	//判断左上至右下棋型
	for (i = 0;i < 12;++i) {
		for (j = 0;j < 12;++j) {
			type = chess_type[Board[i][j]][Board[i + 1][j + 1]][Board[i + 2][j + 2]][Board[i + 3][j + 3]][Board[i + 4][j + 4]][Board[i + 5][j + 5]];
			stat[2][type]++;
		}
	}
	//判断右上至左下棋型
	for (i = 0;i < 12;++i) {
		for (j = 5;j < 17;++j) {
			type = chess_type[Board[i][j]][Board[i + 1][j - 1]][Board[i + 2][j - 2]][Board[i + 3][j - 3]][Board[i + 4][j - 4]][Board[i + 5][j - 5]];
			stat[3][type]++;
		}
	}
	EVALUATION eval;

	for (i = 1; i <= 16; i++)
	{
		int count = stat[0][i] + stat[1][i] + stat[2][i] + stat[3][i];
		eval.score += count * VALUE[i];

		switch (i)
		{
		case WIN:
			eval.STAT[WIN] = count;
			break;
		case LOSE:
			eval.STAT[LOSE] = count;
			break;
		case FLEX4:
			eval.STAT[FLEX4] = count;
			break;
		case BLOCK4:
			eval.STAT[BLOCK4] = count;
			break;
		case FLEX3:
			eval.STAT[FLEX3] = count;
			break;
		default:
			break;
		}
	}

	eval.result = DRAW;
	if (eval.STAT[WIN]) {
		eval.result = W_WIN;
	}
	else if (eval.STAT[LOSE]) {
		eval.result = B_WIN;
	}

	return eval;
}




