//
// Created by hw730 on 2020/4/9.
//

#include"board.h"

void Board::copychess(int (&board)[CHESS_HEIGHT][CHESS_LENGTH],int (&sameBoard)[CHESS_HEIGHT][CHESS_LENGTH])
{
    for(int i = 0;i < CHESS_HEIGHT;i++)
    {
        for(int j = 0;j < CHESS_LENGTH;j++)
        {
            sameBoard[i][j] = board[i][j];
        }
    }
}

void Board::revBoard(int (&board)[CHESS_HEIGHT][CHESS_LENGTH],int (&reverseBoard)[CHESS_HEIGHT][CHESS_LENGTH])
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



boardStatus Board::evaluateBoard(int (&board)[CHESS_HEIGHT][CHESS_LENGTH])//
{
    boardStatus evaluation;
    ll score = 0,status = 0;
    bool flag = false;

    for(int i = 1;i <= R;i++)
    {
        int x = q[i].x(), y = q[i].y();
        for(int k = 0;k < 4;k++)
        {
            for(int t = 0;t <= 5;t++)
            {
                int min_x = x - dir[k][0] * t,min_y = y - dir[k][1] * t;
                int max_x = x - dir[k][0] * (t - 5), max_y = y - dir[k][1] * (t - 5);
                int pre = score;
                if((!judgePoints(min_x,min_y)) || (!judgePoints(max_x,max_y))) continue;
                score += chess_6_type[board[x - dir[k][0] * t][y - dir[k][1] * t]][board[x - dir[k][0] * (t - 1)][y - dir[k][1] * (t - 1)]][board[x - dir[k][0] * (t - 2)][y - dir[k][1] * (t - 2)]][board[x - dir[k][0] * (t - 3)][y - dir[k][1] * (t - 3)]][board[x - dir[k][0] * (t - 4)][y - dir[k][1] * (t - 4)]][board[x - dir[k][0] * (t - 5)][y - dir[k][1] * (t - 5)]];
                if(score - pre == WIN)
                {
                    status = 1;
                    flag = true;
                }
                else if(score - pre == LOSE)
                {
                    status = 2;
                    flag = true;
                }
                if(flag)
                {
                    score += (score - pre) * 5;
                    evaluation.score = score;
                    evaluation.status = status;
                    return evaluation;
                }
            }
        }
    }
    evaluation.score = score;
    evaluation.status = status;
    return evaluation;
}



bool Board::judgePoints(int x,int y)
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


decision Board::findPoints(int (&board)[CHESS_HEIGHT][CHESS_LENGTH])
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
        value_queue[t] = evaluateBoard(board).score;
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


ll Board::alphaBetaSearch(int (&board)[CHESS_HEIGHT][CHESS_LENGTH], int depth, ll alpha, ll beta)
{
    boardStatus result = evaluateBoard(board);
    if(depth == 0 || result.status != 0)
    {
        if(depth == 0)
        {
            decision P;
            P = findPoints(board);
            return P.score[0];
        }
        else
        {
            if(result.status == 1)
            {
                return LLONG_MAX - 1;
            }
            else
            {
                return -LLONG_MAX + 1;
            }
        }
    }
    else if(depth % 2 == 0)
    {
        int sameBoard[CHESS_HEIGHT][CHESS_LENGTH];
        copychess(board,sameBoard);
        decision P = findPoints(sameBoard);

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
            ll score = alphaBetaSearch(sameBoard, depth - 1,alpha,beta);
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
        return alpha;
    }
    else
    {
        int reverseBoard[CHESS_HEIGHT][CHESS_LENGTH];
        revBoard(board,reverseBoard);
        decision P = findPoints(reverseBoard);

        int sameBoard[CHESS_HEIGHT][CHESS_LENGTH];
        copychess(board,sameBoard);

        for(int i = 0;i < MAX_CHOICE;i++)
        {
            if(!judgePoints(P.pos[i].x,P.pos[i].y)) continue;
            sameBoard[P.pos[i].x][P.pos[i].y] = C_BLACK;
//            q[++R] = P.pos[i];
            q[++R] = QPoint(P.pos[i].x,P.pos[i].y);
            ll score = alphaBetaSearch(sameBoard,depth - 1,alpha,beta);
            sameBoard[P.pos[i].x][P.pos[i].y] = C_NONE;
            R--;
            if(score < beta)
            {
                beta = score;
            }
            if(alpha >= beta) break;
        }
        return beta;
    }
}

bool Board::judgeChessBoardStatus(int (&board)[CHESS_HEIGHT][CHESS_LENGTH])
{
    boardStatus chess_Board = evaluateBoard(board);
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

void Board::AI(int (&board)[CHESS_HEIGHT][CHESS_LENGTH])
{
    alphaBetaSearch(board,depth_MAX,-INT_MAX,INT_MAX);
    if(board[AIStep.x][AIStep.y] != C_NONE) return;
    q[++R] = QPoint(AIStep.x,AIStep.y);
    q1[++R1] = q[R];
    col[R1] = 0;
    board[AIStep.x][AIStep.y] = C_WHITE;
    update();
}

