//
// Created by hw730 on 2020/4/19.
//

#include "alphabeta.h"

void copychess(int (&board)[CHESS_HEIGHT][CHESS_LENGTH],int (&sameBoard)[CHESS_HEIGHT][CHESS_LENGTH])
{
    for(int i = 0;i < CHESS_HEIGHT;i++)
    {
        for(int j = 0;j < CHESS_LENGTH;j++)
        {
            sameBoard[i][j] = board[i][j];
        }
    }
}

void revBoard(int (&board)[CHESS_HEIGHT][CHESS_LENGTH],int (&reverseBoard)[CHESS_HEIGHT][CHESS_LENGTH])
{
    for(int i = 0;i < CHESS_HEIGHT;i++)
    {
        for(int j = 0;j < CHESS_LENGTH;j++)
        {
            if(board[i][j] == C_BLACK)
            {
                reverseBoard[i][j] = C_WHITE;
            }
            else if(board[i][j] == C_WHITE)
            {
                reverseBoard[i][j] = C_BLACK;
            }
            else
            {
                reverseBoard[i][j] = board[i][j];
            }
        }
    }
}
//zobrist_hash
ll Rand()
{
    return rand()+(rand() << 16);
}
void init_zobrist()
{
    for(int i = 1;i < CHESS_HEIGHT;i++)
    {
        for(int j = 1;j < CHESS_LENGTH;j++)
        {
            zob[i][j][0] = Rand();
            zob[i][j][1] = Rand();
        }
    }
}
//end



boardStatus evaluateBoard(int (&board)[CHESS_HEIGHT][CHESS_LENGTH],ll zobrist)//
{
    boardStatus evaluation;
    ll score = 0,status = 0;
    bool flag = false;
    if(mp.count(zobrist) !=0 ) return mp[zobrist];


    for(int i = 1;i <= R;i++)
    {
        int x = q[i].x(), y = q[i].y();
        int white_live_4,white_dead_4,white_live_3;
        int black_live_4,black_dead_4,black_live_3;
        black_live_4 = black_dead_4 = black_live_3 = 0;
        white_live_4 = white_dead_4 = white_live_3 = 0;
        for(int k = 0;k < 4;k++)
        {
            bool white_judge_live_3 = false;
            auto black_judge_live_3 = false;
            ll type_score = 0;
            for(int t = 0; t <= 5; t++)
            {
                int min_x = x - dir[k][0] * t,min_y = y - dir[k][1] * t;
                int max_x = x - dir[k][0] * (t - 5), max_y = y - dir[k][1] * (t - 5);
//                ll pre;
                if((!judgePoints(min_x,min_y)) || (!judgePoints(max_x,max_y))) continue;
                type_score = chess_6_type[board[x - dir[k][0] * t][y - dir[k][1] * t]][board[x - dir[k][0] * (t - 1)][y - dir[k][1] * (t - 1)]][board[x - dir[k][0] * (t - 2)][y - dir[k][1] * (t - 2)]][board[x - dir[k][0] * (t - 3)][y - dir[k][1] * (t - 3)]][board[x - dir[k][0] * (t - 4)][y - dir[k][1] * (t - 4)]][board[x - dir[k][0] * (t - 5)][y - dir[k][1] * (t - 5)]];
//                if(i % 2 == 0)
//                {
//                    type_score = std::min(pre,type_score);
//                }
//                else
//                {
//                    type_score = std::max(pre,type_score);
//                }
                score += type_score;
                if(type_score == WIN)
                {
                    status = 1;
                    flag = true;
                }
                else if(type_score == LOSE)
                {
                    status = 2;
                    flag = true;
                }
                if(flag)
                {
                    score += (type_score) * 5;
                    evaluation.score = score;
                    evaluation.status = status;
                    mp[zobrist] = evaluation;
                    return evaluation;
                }
                if(type_score == WHITE_LIVE_3)
                {
                    white_judge_live_3 = true;
                }
                if(type_score == WHITE_LIVE_4)
                {
                    white_live_4 = 1;
                }
                if(type_score == WHITE_SLEEP_4)
                {
                    white_dead_4 = 1;
                }
                if(type_score == BLACK_LIVE_3)
                {
                    black_judge_live_3 = true;
                }
                if(type_score == WHITE_LIVE_4)
                {
                    black_live_4 = 1;
                }
                if(type_score == WHITE_SLEEP_4)
                {
                    black_dead_4 = 1;
                }
            }
            if(white_judge_live_3)
            {
                white_live_3++;
            }
            if(black_judge_live_3)
            {
                black_live_3++;
            }

        }
//        if(white_live_4 || (white_live_3 + white_dead_4 >= 2))
//        {
//            score += WIN;
//        }
//        if(black_live_4 || (black_dead_4 + black_live_3 >= 2))
//        {
//            score += LOSE;
//        }
    }

    evaluation.score = score;
    evaluation.status = status;
    mp[zobrist] = evaluation;
    return evaluation;
}



bool judgePoints(int x,int y)
{
    if(x <= 0 || x >= CHESS_HEIGHT - 1 || y <= 0 || y >= CHESS_LENGTH - 1)
    {
        return false;
    }
    return true;
}



Points queue[CHESS_HEIGHT * CHESS_LENGTH];
ll value_queue[CHESS_HEIGHT * CHESS_LENGTH];
bool inque[CHESS_HEIGHT][CHESS_LENGTH];


decision findPoints(int (&board)[CHESS_HEIGHT][CHESS_LENGTH],ll zobrist)
{
    decision P;
    int r = 0;
    for(int t = 1;t <= R;t++)
    {
        int i = q[t].x(), j = q[t].y();
        for(int k = 1;k <= STEPS;k++)
        {
            for(int d = 0;d < 8;d++)
            {
                if(judgePoints(i + dir[d][0] * k,j + dir[d][1] * k)
                   && board[i + dir[d][0] * k][j + dir[d][1] * k] == C_NONE
                   && (!inque[i + dir[d][0] * k][j + dir[d][1] * k]))
                {
                    Points pos;
                    pos.x = i + dir[d][0] * k;
                    pos.y = j + dir[d][1] * k;
                    queue[++r] = pos;
                    inque[i + dir[d][0] * k][j + dir[d][1] * k] = true;
                }
            }
        }
    }

    for(int t = 1;t <= r;t++)
    {
        int i = queue[t].x,j = queue[t].y;
        board[i][j] = C_WHITE;
        Points pos;
        pos.x = i;
        pos.y = j;
//        q[++R] = pos;
        q[++R] = QPoint(pos.x,pos.y);
        value_queue[t] = evaluateBoard(board,zobrist ^ zob[i][j][C_WHITE - 1]).score;
        board[i][j] = C_NONE;
        R--;
    }

    for(int k = 0;k < MAX_CHOICE;k++)
    {
        ll maxvalue = -LLONG_MAX;
        bool flag = false;
        int pos = -1;
        for(int t = 1;t <= r;t++)
        {
            int i = queue[t].x,j = queue[t].y;
            if(maxvalue < value_queue[t])
            {
                maxvalue = value_queue[t];
                P.pos[k] = queue[t];
                P.score[k] = value_queue[t];
                flag = true;
                pos = t;
            }
            inque[i][j] = false;
        }
        if(flag)
        {
            value_queue[pos] = -LLONG_MAX;
        }
    }
    return P;
}


ll alphaBetaSearch(int (&board)[CHESS_HEIGHT][CHESS_LENGTH], int depth, ll alpha, ll beta,ll zobrist)
{
    boardStatus result = evaluateBoard(board,zobrist);
    if(depth == 0 || result.status != 0)
    {
        if(depth == 0)
        {
            decision P;
            P = findPoints(board,zobrist);
            vis[zobrist] = P.score[0];
            return P.score[0];
        }
        else
        {
            if(result.status == 1)
            {
                vis[zobrist] = LLONG_MAX - 1;
                return LLONG_MAX - 1;
            }
            else
            {
                vis[zobrist] = -LLONG_MAX + 1;
                return -LLONG_MAX + 1;
            }
        }
    }
    else if(depth % 2 == 0)
    {
        int sameBoard[CHESS_HEIGHT][CHESS_LENGTH];
        copychess(board,sameBoard);
        decision P = findPoints(sameBoard,zobrist);

        for(int i = 0;i < MAX_CHOICE;i++)
        {
            if(!judgePoints(P.pos[i].x,P.pos[i].y)) continue;
            if(depth == depth_MAX && i == 0)
            {
                AIStep = P.pos[i];
            }
            sameBoard[P.pos[i].x][P.pos[i].y] = C_WHITE;
//            q[++R] = P.pos[i];
            q[++R] = QPoint(P.pos[i].x,P.pos[i].y);
            ll score;
            if(vis.count(zobrist ^ zob[P.pos[i].x][P.pos[i].y][C_WHITE - 1]) != 0)
            {
                score = vis[zobrist ^ zob[P.pos[i].x][P.pos[i].y][C_WHITE - 1]];
            }
            else
            {
                score = alphaBetaSearch(sameBoard, depth - 1,alpha,beta,zobrist ^ zob[P.pos[i].x][P.pos[i].y][C_WHITE - 1]);
            }
            sameBoard[P.pos[i].x][P.pos[i].y] = C_NONE;
            R--;
            if(score > alpha)
            {
                alpha = score;
                if(depth == depth_MAX)
                {
                    AIStep = P.pos[i];
                }
            }
            if(alpha >= beta) break;
        }
        vis[zobrist] = alpha;
        return alpha;
    }
    else
    {
        int reverseBoard[CHESS_HEIGHT][CHESS_LENGTH];
        revBoard(board,reverseBoard);
        decision P = findPoints(reverseBoard,zobrist);

        int sameBoard[CHESS_HEIGHT][CHESS_LENGTH];
        copychess(board,sameBoard);

        for(int i = 0;i < MAX_CHOICE;i++)
        {
            if(!judgePoints(P.pos[i].x,P.pos[i].y)) continue;
            sameBoard[P.pos[i].x][P.pos[i].y] = C_BLACK;
//            q[++R] = P.pos[i];
            q[++R] = QPoint(P.pos[i].x,P.pos[i].y);
            ll score;
            if(vis.count(zobrist ^ zob[P.pos[i].x][P.pos[i].y][C_WHITE - 1]) != 0)
            {
                score = vis[zobrist ^ zob[P.pos[i].x][P.pos[i].y][C_WHITE - 1]];
            }
            else
            {
                score = alphaBetaSearch(sameBoard,depth - 1,alpha,beta,zobrist ^ zob[P.pos[i].x][P.pos[i].y][C_BLACK - 1]);
            }
            sameBoard[P.pos[i].x][P.pos[i].y] = C_NONE;
            R--;
            if(score < beta)
            {
                beta = score;
            }
            if(alpha >= beta) break;
        }
        vis[zobrist] = beta;
        return beta;
    }
}

bool judgeChessBoardStatus(int (&board)[CHESS_HEIGHT][CHESS_LENGTH],ll zobrist)
{
    boardStatus chess_Board = evaluateBoard(board,zobrist);
    if(chess_Board.status == 0)
    {
        return false;
    }
    if(chess_Board.status == 1)
    {
        printf("You Lose");

    }
    else if(chess_Board.status == 2)
    {
        printf("You win");
    }
    system("pause");
    return true;
}

void AI(int (&board)[CHESS_HEIGHT][CHESS_LENGTH])
{
    alphaBetaSearch(board,depth_MAX,-INT_MAX,INT_MAX,Hash);
    if(board[AIStep.x][AIStep.y] != C_NONE) return;
    q[++R] = QPoint(AIStep.x,AIStep.y);
    q1[++R1] = q[R];
    col[R1] = 0;
    board[AIStep.x][AIStep.y] = C_WHITE;
    Hash ^= zob[AIStep.x][AIStep.y][C_WHITE - 1];
}