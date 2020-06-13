#include "ChessAI.h"

#include <conio.h>

#include <cstdlib>
#include <queue>
using namespace std;

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
const long long VALUE[] = {0,       1000000, -10000000, 50000, -100000, 400,
                           -100000, 400,     -8000,     20,    -50,     20,
                           -50,     1,       -3,        1,     -3};  //估分表
const int MAXN_DEPTH = 6;  //搜索层数

void ChessAI::init_typescore() {
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

    int p1, p2, p3, p4, p5, p6, x, y, ix,
        iy;  // x:左5中黑个数,y:左5中白个数,ix:右5中黑个数,iy:右5中白个数
    for (p1 = 0; p1 < 4; p1++) {
        for (p2 = 0; p2 < 3; p2++) {
            for (p3 = 0; p3 < 3; p3++) {
                for (p4 = 0; p4 < 3; p4++) {
                    for (p5 = 0; p5 < 3; p5++) {
                        for (p6 = 0; p6 < 4; p6++) {
                            x = y = ix = iy = 0;

                            if (p1 == 1)
                                x++;
                            else if (p1 == 2)
                                y++;

                            if (p2 == 1) {
                                x++;
                                ix++;
                            } else if (p2 == 2) {
                                y++;
                                iy++;
                            }

                            if (p3 == 1) {
                                x++;
                                ix++;
                            } else if (p3 == 2) {
                                y++;
                                iy++;
                            }

                            if (p4 == 1) {
                                x++;
                                ix++;
                            } else if (p4 == 2) {
                                y++;
                                iy++;
                            }

                            if (p5 == 1) {
                                x++;
                                ix++;
                            } else if (p5 == 2) {
                                y++;
                                iy++;
                            }

                            if (p6 == 1)
                                ix++;
                            else if (p6 == 2)
                                iy++;

                            if (p1 == 3 || p6 == 3) {      //有边界
                                if (p1 == 3 && p6 != 3) {  //左边界
                                    //白冲4
                                    if (ix == 0 &&
                                        iy ==
                                            4) {  //若右边有空位是活4也没关系，因为活4权重远大于冲4，再加上冲4权重变化可以不计
                                        if (chess_type[p1][p2][p3][p4][p5]
                                                      [p6] == 0)
                                            chess_type[p1][p2][p3][p4][p5][p6] =
                                                BLOCK4;
                                    }
                                    //黑冲4
                                    if (ix == 4 && iy == 0) {
                                        if (chess_type[p1][p2][p3][p4][p5]
                                                      [p6] == 0)
                                            chess_type[p1][p2][p3][p4][p5][p6] =
                                                block4;
                                    }
                                    //白眠3
                                    if (ix == 0 && iy == 3) {
                                        if (chess_type[p1][p2][p3][p4][p5]
                                                      [p6] == 0)
                                            chess_type[p1][p2][p3][p4][p5][p6] =
                                                BLOCK3;
                                    }
                                    //黑眠3
                                    if (ix == 3 && iy == 0) {
                                        if (chess_type[p1][p2][p3][p4][p5]
                                                      [p6] == 0)
                                            chess_type[p1][p2][p3][p4][p5][p6] =
                                                block3;
                                    }
                                    //白眠2
                                    if (ix == 0 && iy == 2) {
                                        if (chess_type[p1][p2][p3][p4][p5]
                                                      [p6] == 0)
                                            chess_type[p1][p2][p3][p4][p5][p6] =
                                                BLOCK2;
                                    }
                                    //黑眠2
                                    if (ix == 2 && iy == 0) {
                                        if (chess_type[p1][p2][p3][p4][p5]
                                                      [p6] == 0)
                                            chess_type[p1][p2][p3][p4][p5][p6] =
                                                block2;
                                    }
                                } else if (p6 == 3 && p1 != 3) {  //右边界
                                                                  //白冲4
                                    if (x == 0 && y == 4) {
                                        if (chess_type[p1][p2][p3][p4][p5]
                                                      [p6] == 0)
                                            chess_type[p1][p2][p3][p4][p5][p6] =
                                                BLOCK4;
                                    }
                                    //黑冲4
                                    if (x == 4 && y == 0) {
                                        if (chess_type[p1][p2][p3][p4][p5]
                                                      [p6] == 0)
                                            chess_type[p1][p2][p3][p4][p5][p6] =
                                                block4;
                                    }
                                    //黑眠3
                                    if (x == 3 && y == 0) {
                                        if (chess_type[p1][p2][p3][p4][p5]
                                                      [p6] == 0)
                                            chess_type[p1][p2][p3][p4][p5][p6] =
                                                BLOCK3;
                                    }
                                    //白眠3
                                    if (x == 0 && y == 3) {
                                        if (chess_type[p1][p2][p3][p4][p5]
                                                      [p6] == 0)
                                            chess_type[p1][p2][p3][p4][p5][p6] =
                                                block3;
                                    }
                                    //黑眠2
                                    if (x == 2 && y == 0) {
                                        if (chess_type[p1][p2][p3][p4][p5]
                                                      [p6] == 0)
                                            chess_type[p1][p2][p3][p4][p5][p6] =
                                                BLOCK2;
                                    }
                                    //白眠2
                                    if (x == 0 && y == 2) {
                                        if (chess_type[p1][p2][p3][p4][p5]
                                                      [p6] == 0)
                                            chess_type[p1][p2][p3][p4][p5][p6] =
                                                block2;
                                    }
                                }
                            } else {  //无边界
                                      //白冲4
                                if ((x == 0 && y == 4) ||
                                    (ix == 0 && iy == 4)) {
                                    if (chess_type[p1][p2][p3][p4][p5][p6] == 0)
                                        chess_type[p1][p2][p3][p4][p5][p6] =
                                            BLOCK4;
                                }
                                //黑冲4
                                if ((x == 4 && y == 0) ||
                                    (ix == 4 && iy == 0)) {
                                    if (chess_type[p1][p2][p3][p4][p5][p6] == 0)
                                        chess_type[p1][p2][p3][p4][p5][p6] =
                                            block4;
                                }
                                //白眠3
                                if ((x == 0 && y == 3) ||
                                    (ix == 0 && iy == 3)) {
                                    if (chess_type[p1][p2][p3][p4][p5][p6] == 0)
                                        chess_type[p1][p2][p3][p4][p5][p6] =
                                            BLOCK3;
                                }
                                //黑眠3
                                if ((x == 3 && y == 0) ||
                                    (ix == 3 && iy == 0)) {
                                    if (chess_type[p1][p2][p3][p4][p5][p6] == 0)
                                        chess_type[p1][p2][p3][p4][p5][p6] =
                                            block3;
                                }
                                //白眠2
                                if ((x == 0 && y == 2) ||
                                    (ix == 0 && iy == 2)) {
                                    if (chess_type[p1][p2][p3][p4][p5][p6] == 0)
                                        chess_type[p1][p2][p3][p4][p5][p6] =
                                            BLOCK2;
                                }
                                //黑眠2
                                if ((x == 2 && y == 0) ||
                                    (ix == 2 && iy == 0)) {
                                    if (chess_type[p1][p2][p3][p4][p5][p6] == 0)
                                        chess_type[p1][p2][p3][p4][p5][p6] =
                                            block2;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

bool ChessAI::AI_set_chess(Checkerboard& board) {
    alpha_beta(board, 0, INT64_MIN, INT64_MAX);

    board.set_chess(best_point.x, best_point.y, WHITECHESS);
    board.print_chess();
    if (board.judge(best_point.x, best_point.y, WHITECHESS)) {
        board.print_win();
        _getch();
        return true;
    }
    return false;
}

EVALUATION ChessAI::get_score(Checkerboard& board) {
    int stat[4][17];  //四个方向上的棋型
    memset(stat, 0, sizeof(stat));

    int STAT[17];  //存某个方向的棋型
    memset(STAT, 0, sizeof(STAT));

    int i, j, type;     //稍微加点速度移到外面来。
    int Board[17][17];  //用来加入边界
    memset(Board, 0, sizeof(Board));
    for (i = 0; i < 17; i++) {
        Board[i][0] = 3;
        Board[i][16] = 3;
        Board[0][i] = 3;
        Board[16][i] = 3;
    }
    for (i = 1; i < 16; i++) {
        for (j = 1; j < 16; j++) {
            Board[i][j] = board.board[i - 1][j - 1];
        }
    }
    //判断横向棋型
    for (i = 1; i <= 15; ++i) {
        for (j = 0; j < 12; ++j) {
            type =
                chess_type[Board[i][j]][Board[i][j + 1]][Board[i][j + 2]]
                          [Board[i][j + 3]][Board[i][j + 4]][Board[i][j + 5]];
            stat[0][type]++;
        }
    }
    //判断竖向棋型
    for (j = 1; j <= 15; ++j) {
        for (i = 0; i < 12; ++i) {
            type =
                chess_type[Board[i][j]][Board[i + 1][j]][Board[i + 2][j]]
                          [Board[i + 3][j]][Board[i + 4][j]][Board[i + 5][j]];
            stat[1][type]++;
        }
    }
    //判断左上至右下棋型
    for (i = 0; i < 12; ++i) {
        for (j = 0; j < 12; ++j) {
            type = chess_type[Board[i][j]][Board[i + 1][j + 1]]
                             [Board[i + 2][j + 2]][Board[i + 3][j + 3]]
                             [Board[i + 4][j + 4]][Board[i + 5][j + 5]];
            stat[2][type]++;
        }
    }
    //判断右上至左下棋型
    for (i = 0; i < 12; ++i) {
        for (j = 5; j < 17; ++j) {
            type = chess_type[Board[i][j]][Board[i + 1][j - 1]]
                             [Board[i + 2][j - 2]][Board[i + 3][j - 3]]
                             [Board[i + 4][j - 4]][Board[i + 5][j - 5]];
            stat[3][type]++;
        }
    }
    EVALUATION eval;

    for (i = 1; i <= 16; i++) {
        int count = stat[0][i] + stat[1][i] + stat[2][i] + stat[3][i];
        eval.score += count * VALUE[i];

        switch (i) {
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
    } else if (eval.STAT[LOSE]) {
        eval.result = B_WIN;
    }

    return eval;
}

Points ChessAI::seek_points(Checkerboard board) {
    bool vis[15][15];
    Points best;

    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            if (board.board[i][j]) {
                for (int k = -3; k <= 3; k++) {
                    if (i + k >= 0 && i + k < 15) {
                        vis[i + k][j] = true;
                        if (j + k >= 0 && j + k < 15) {
                            vis[i + k][j + k] = true;
                        }
                        if (j - k >= 0 && j - k < 15) {
                            vis[i + k][j - k] = true;
                        }
                    }
                    if (j + k >= 0 && j + k < 15) {
                        vis[i][j + k] = true;
                    }
                }
            }
        }
    }

    priority_queue<Point> q;
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            if (board.board[i][j] == NOTHING && vis[i][j]) {
                board.board[i][j] =
                    WHITECHESS;  //教程里这里是黑子。感觉这里应该是白子才对
                EVALUATION score = get_score(board);
                board.board[i][j] = NOTHING;
                if (q.size() == MAXN_POINTS && score.score > q.top().val) {
                    q.pop();
                    q.push(Point(i, j, score.score));
                } else if (q.size() < MAXN_POINTS) {
                    q.push(Point(i, j, score.score));
                }
            }
        }
    }

    for (int i = MAXN_POINTS - 1; i >= 0; i--) {
        best.p[i] = q.top();
        q.pop();
    }
    return best;
}

Point ChessAI::get_best(Checkerboard board) {
    Point maxp(0, 0, INT64_MIN);
    EVALUATION temp;
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            if (!board.board[i][j]) {
                board.board[i][j] = WHITECHESS;
                temp = get_score(board);
                board.board[i][j] = NOTHING;

                //测试用
                // char s[25];
                // sprintf_s(s, "%lld", temp.score);
                // outtextxy(40 * (j + 1), 40 * (i + 1), s);

                Point p(i, j, temp.score);
                if (temp.score > maxp.val) {
                    maxp = p;
                }
            }
        }
    }
    return maxp;
}

long long ChessAI::alpha_beta(Checkerboard board, int depth, long long alpha,
                              long long beta) {
	EVALUATION score = get_score(board);
    if (depth == MAXN_DEPTH||score.result) {
		if (depth == 0) {
			return get_best(board).val;
		}
		if (score.result == B_WIN) {
			return score.score;//可能会输（人会失误），所以不能直接设置成INT64_MIN，而是要返回值。
		}
		else {
			return INT64_MAX;//必赢，直接往这里下
		}
    }
    if (!(depth & 1)) {  // AI方，白
        Checkerboard temp;
        temp = board;
        Points p = seek_points(temp);
        for (int i = 0; i < MAXN_POINTS; i++) {
            temp.board[p.p[i].x][p.p[i].y] = WHITECHESS;
            long long a = alpha_beta(temp, depth + 1, alpha, beta);
            temp.board[p.p[i].x][p.p[i].y] = NOTHING;
            if (a > alpha) {
                alpha = a;
                if (depth == 0) {
                    best_point = Point(p.p[i].x, p.p[i].y, alpha);
                }
            }
            if (alpha >= beta) {
                break;
            }
        }
        return alpha;
    } else {
        Checkerboard temp;
        temp = board.reverse();
        Points p = seek_points(temp);
        temp = board;

        for (int i = 0; i < MAXN_POINTS; i++) {
            temp.board[p.p[i].x][p.p[i].y] = BLACKCHESS;
            long long b = alpha_beta(temp, depth + 1, alpha, beta);
            temp.board[p.p[i].x][p.p[i].y] = NOTHING;
            if (b < beta) {
                beta = b;
            }
            if (alpha >= beta) {
                break;
            }
        }
        return beta;
    }
}
