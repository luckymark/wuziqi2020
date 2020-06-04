//
// Created by pointkab on 2020/4/28.
//
#include "game.h"
#include <ctime>
#include <memory.h>
#define FIVE 100000
#define LIVE_FOUR 10000
#define CHONG_FOUR 2000
#define LIVE_THREE 8000
#define MIAN_THREE 1500
#define LIVE_TWO 1000
#define MIAN_TWO 100


struct ChessScore Delocation;

int Qipan_status[QIPAN_SIZE][QIPAN_SIZE];

int Search_Tree(int depth){
    int i,index = 0;
    struct ChessScore scores[100];
    int n =  GetValueChess(scores, depth);
    if (n > 10) n = 10;
    for (i = 0; i < n; i++)
    {
        VirtualPut(scores, i);
        index++;
        if (depth == 1)
        {
            DeleChess(scores, i);
            continue;
        }
        scores[i].score = Search_Tree(depth - 1);
        DeleChess(scores, i);
    }
    Sort(scores, index, depth);
    if (depth == DEPTH)
    {
        Delocation.coord.X = scores[0].coord.X;
        Delocation.coord.Y = scores[0].coord.Y;
    }
    return scores[0].score;
}

int GetValueChess(ChessScore scores[], int depth){
    int i, j, k, temp1, temp2;
    int count = 0;//有效棋子的个数
    int chessType;//棋子的类型
    memset(Qipan_status, 0, 15*15* sizeof(int));
    if (depth%2 == 0){
        //电脑的棋子
        chessType = -1;
    } else{
        //玩家的的棋子
        chessType = 1;
    }
    //查找思路：找已经落子的周围2层，并通过一个单子的评分函数评分，最后同过分数来排序
    for (i = 0; i < ChessNums; i++)
    {
        int Chessy = CurrentChess[i].coord.Y;
        int Chessx = CurrentChess[i].coord.X;
        for (k = 0; k < 8; k++) {
            switch (k) {
                case 0:
                    //上
                    temp1 = 1;
                    temp2 = 0;
                    break;
                case 1:
                    //下
                    temp1 = -1;
                    temp2 = 0;
                    break;
                case 2:
                    //左
                    temp1 = 0;
                    temp2 = 1;
                    break;
                case 3:
                    //右
                    temp1 = 0;
                    temp2 = -1;
                    break;
                case 4:
                    //左上
                    temp1 = 1;
                    temp2 = 1;
                    break;
                case 5:
                    //右上
                    temp1 = 1;
                    temp2 = -1;
                    break;
                case 6:
                    //左下
                    temp1 = -1;
                    temp2 = 1;
                    break;
                case 7:
                    //右下
                    temp1 = -1;
                    temp2 = -1;
                    break;
            }
            for (j = 0; j < 2; j++) {
                if (Chessy - temp1*(j + 1) < 0 || Chessx - temp2*(j + 1) < 0 || Chessx - temp2*(j + 1) > 14 || Chessy - temp1*(j + 1) > 14)
                { break;}
                if (Qipan_status[Chessy - temp1 * (j + 1)][Chessx - temp2 * (j + 1)] != 0)//位置已经遍历
                { continue;}
                if (Qipan_Array[Chessy - temp1*(j + 1)][Chessx - temp2*(j + 1)] == 0) {
                    scores[count].chesstype = chessType;
                    scores[count].coord.X = Chessx - temp2*(j + 1);
                    scores[count].coord.Y = Chessy - temp1*(j + 1);
                    Qipan_Array[Chessy - temp1*(j + 1)][Chessx - temp2*(j + 1)] = chessType;
                    scores[count].score = EvaluateAllChess();
                    Qipan_Array[Chessy - temp1*(j + 1)][Chessx - temp2*(j + 1)] = 0;
                    Qipan_status[Chessy - temp1 * (j + 1)][Chessx - temp2 * (j + 1)] = 1;
                    count++;
                }
            }
        }

    }
    Sort(scores, count, depth);
    return count;

}

void Sort(ChessScore* scores, int count, int depth){
    int i, j;
    struct ChessScore temp;
    if (depth%2 == 0) {
        for (i = 0; i < count; i++) {
            for (j = 0; j < count - i - 1; j++) {
                if (scores[j].score < scores[j + 1].score) {
                    temp.score = scores[j].score;
                    temp.coord.X = scores[j].coord.X;
                    temp.coord.Y = scores[j].coord.Y;
                    scores[j].score = scores[j + 1].score;
                    scores[j].coord.X = scores[j + 1].coord.X;
                    scores[j].coord.Y = scores[j + 1].coord.Y;
                    scores[j + 1].score = temp.score;
                    scores[j + 1].coord.X = temp.coord.X;
                    scores[j + 1].coord.Y = temp.coord.Y;
                }
            }
            Qipan_status[scores[count - i - 1].coord.Y][scores[count - i - 1].coord.X] = 0;
        }
    } else {
        for (i = 0; i < count; i++) {
            for (j = 0; j < count - i - 1; j++) {
                if (scores[j].score > scores[j + 1].score) {
                    temp.score = scores[j].score;
                    temp.coord.X = scores[j].coord.X;
                    temp.coord.Y = scores[j].coord.Y;
                    scores[j].score = scores[j + 1].score;
                    scores[j].coord.X = scores[j + 1].coord.X;
                    scores[j].coord.Y = scores[j + 1].coord.Y;
                    scores[j + 1].score = temp.score;
                    scores[j + 1].coord.X = temp.coord.X;
                    scores[j + 1].coord.Y = temp.coord.Y;
                }
            }
            Qipan_status[scores[count - i - 1].coord.Y][scores[count - i - 1].coord.X] = 0;
        }
    }
}

int EvaluateAllChess(){
    //暴力匹配、ac算法暂时不会
    //思路：每行，每列，每斜列 对棋型进行匹配
    int i, j, score = 0;
    int matchChess[15][15][4];
    //初始化棋子匹配状态
    memset(matchChess,0,15*15*4*sizeof(int));
    for (i = 0; i < QIPAN_SIZE; i++){
        for (j = 0; j < QIPAN_SIZE; j++)
        {
            if (Qipan_Array[i][j] != 0)//有棋子
            {
                score += -Matchline(i,j,matchChess);
            }
        }
    }
    return score;
}

int Matchline(int y, int x, int matchChess[15][15][4]){
    int lenth = 1,i,j,k;
    int Iswin = 0;
    int direction;//方向
    int score = 0;
    int left_edge, right_edge;
    int type = Qipan_Array[y][x];
    int a, b;
    int left1, right1, left2, right2;
    for (k = 0; k < 4; k++) {
        lenth = 1;
        left_edge = 0;
        right_edge = 0;
        switch (k)
        {
            case 0:
                direction = 0;
                for (j = 0; j < 2; j++) {
                    //水平方向
                    if (j == 0) {
                        a = 1;
                        b = 0;
                    } else {
                        a = -1;
                        b = 0;
                    }
                    for (i = 0; i < 4; i++) {
                        if (y - b * (i + 1) < 0 || x - a * (i + 1) < 0 || y - b * (i + 1) > 14 || x - a * (i + 1) > 14)
                            break;
                        if (Qipan_Array[y - b * (i + 1)][x - a * (i + 1)] == type && matchChess[y - b * (i + 1)][x - a * (i + 1)][direction] == 0)
                        {
                            matchChess[y - b * (i + 1)][x - a * (i + 1)][direction] = 1;
                            lenth++;
                            if (j == 0) {
                                left_edge++;
                            } else {
                                right_edge++;
                            }
                        } else { break; }
                    }
                }
                break;
            case 1:
                direction = 1;
                for (j = 0; j < 2; j++) {
                    //竖直方向
                    if (j == 0) {
                        a = 0;
                        b = 1;
                    } else {
                        a = 0;
                        b = -1;
                    }
                    for (i = 0; i < 4; i++) {
                        if (y - b * (i + 1) < 0 || x - a * (i + 1) < 0 || y - b * (i + 1) > 14 || x - a * (i + 1) > 14)
                            break;
                        if (Qipan_Array[y - b * (i + 1)][x - a * (i + 1)] == type && matchChess[y - b * (i + 1)][x - a * (i + 1)][direction] == 0)
                        {
                            matchChess[y - b * (i + 1)][x - a * (i + 1)][direction] = 1;
                            lenth++;
                            if (j == 0) {
                                left_edge++;
                            } else {
                                right_edge++;
                            }
                        } else { break; }
                    }
                }
                break;
            case 2:
                direction = 2;
                for (j = 0; j < 2; j++) {
                    //左斜方向
                    if (j == 0) {
                        a = 1;
                        b = 1;
                    } else {
                        a = -1;
                        b = -1;
                    }
                    for (i = 0; i < 4; i++) {
                        if (y - b * (i + 1) < 0 || x - a * (i + 1) < 0 || y - b * (i + 1) > 14 || x - a * (i + 1) > 14)
                            break;
                        if (Qipan_Array[y - b * (i + 1)][x - a * (i + 1)] == type && matchChess[y - b * (i + 1)][x - a * (i + 1)][direction] == 0)
                        {
                            matchChess[y - b * (i + 1)][x - a * (i + 1)][direction] = 1;
                            lenth++;
                            if (j == 0) {
                                left_edge++;
                            } else {
                                right_edge++;
                            }
                        } else { break; }
                    }
                }
                break;
            case 3:
                direction = 3;
                for (j = 0; j < 2; j++) {
                    //右斜方向
                    if (j == 0) {
                        a = 1;
                        b = -1;
                    } else {
                        a = -1;
                        b = 1;
                    }
                    for (i = 0; i < 4; i++) {
                        if (y - b * (i + 1) < 0 || x - a * (i + 1) < 0 || y - b * (i + 1) > 14 || x - a * (i + 1) > 14)
                            break;
                        if (Qipan_Array[y - b * (i + 1)][x - a * (i + 1)] == type && matchChess[y - b * (i + 1)][x - a * (i + 1)][direction] == 0)
                        {
                            matchChess[y - b * (i + 1)][x - a * (i + 1)][direction] = 1;
                            lenth++;
                            if (j == 0) {
                                left_edge++;
                            } else {
                                right_edge++;
                            }
                        } else { break; }
                    }
                }
                break;
        }
            if (matchChess[y][x][direction] != 0) {
                continue;
            }
            matchChess[y][x][direction] = 1;
            if (x + a * (left_edge + 1) < 0 || y + b * (left_edge + 1) < 0||y + b * (left_edge + 1) > 14) {
                left1 = -type;
                left2 = -type;
            } else {
                left1 = Qipan_Array[y + b * (left_edge + 1)][x + a*(left_edge + 1)];
            }
            if (x - a*(right_edge + 1) > 14||y - b*(right_edge + 1) > 14||y - b*(right_edge + 1) < 0) {
                right1 = -type;
                right2 = -type;
            } else {
                right1 = Qipan_Array[y - b*(right_edge + 1)][x - a*(right_edge + 1)];
            }
            if (x + a * (left_edge + 2) < 0 || y + b * (left_edge + 2) < 0||y + b * (left_edge + 2) > 14) {
                left1 = Qipan_Array[y + b * (left_edge + 1)][x + a*(left_edge + 1)];
                left2 = -type;
            } else {
                left1 = Qipan_Array[y + b * (left_edge + 1)][x + a*(left_edge + 1)];
                left2 = Qipan_Array[y + b * (left_edge + 2)][x + a*(left_edge + 2)];
            }
            if (x - a*(right_edge + 2) > 14||y - b*(right_edge + 2) > 14||y - b*(right_edge + 2) < 0) {
                right1 = Qipan_Array[y - b*(right_edge + 1)][x - a*(right_edge + 1)];
                right2 = -type;
            } else {
                right1 = Qipan_Array[y - b*(right_edge + 1)][x - a*(right_edge + 1)];
                right2 = Qipan_Array[y - b*(right_edge + 2)][x - a*(right_edge + 2)];
            }
            switch (lenth) {
                case 5:
                    Iswin = type * 1;//Ai是-1，玩家是1
                    score = score + FIVE * type;
                    break;
                case 4://4颗棋子
                    if (left1 == 0 && right1 == 0) {
                        //活四o1111o
                        score = score + type * LIVE_FOUR;
                    } else if (left1 == -type || right1 == -type) {
                        //冲四x1111o
                        score = score + type * CHONG_FOUR;
                    }
                    break;
                case 3:
                    if (left1 == 0 && right1 == 0) {
                        if (left2 == -type && right2 == -type) {
                            //眠三xo111ox
                            score = score + type * MIAN_THREE;
                        }
                        //活三o111o
                        score = score + type * LIVE_THREE;
                    } else if (left1 == 0 && left2 == type) {
                        //(左)冲四111o1
                        score = score + type * CHONG_FOUR;
                        matchChess[y + b * (left_edge + 2)][x + a*(left_edge + 2)][direction] = 1;
                    } else if (right1 == 0 && right2 == type) {
                        //(右)冲四111o1
                        score = score + type * CHONG_FOUR;
                        matchChess[y - b*(right_edge + 2)][x - a*(right_edge + 2)][direction] = 1;
                    } else if (left1 == -type && right1 == 0 && right2 == 0) {
                        //(右)眠三x111oo
                        score = score + type * MIAN_THREE;
                    } else if (right1 == -type && left1 == 0 && left2 == 0) {
                        //(左)眠三x111oo
                        score = score + type * MIAN_THREE;
                    }
                    break;
                case 2:
                    if (left1 == 0 && left2 == 0 && right1 == 0 && right2 == 0) {
                        //活二oo11oo
                        score = score + type * LIVE_TWO;
                    } else if (left1 == 0 && left2 == type && x + a * (left_edge + 3) > 0 && y + b * (left_edge + 3) > 0 && y + b * (left_edge + 3) < 14) {
                        if (matchChess[y + b * (left_edge + 2)][x + a * (left_edge + 2)][direction] == 0){
                            if (Qipan_Array[y + b * (left_edge + 3)][x + a * (left_edge + 3)] == type) {
                                //(左)冲四11o11
                                if (matchChess[y + b * (left_edge + 3)][x + a * (left_edge + 3)][direction] == 0){
                                    score = score + type * CHONG_FOUR;
                                    matchChess[y + b * (left_edge + 2)][x + a * (left_edge + 2)][direction] = 1;
                                    matchChess[y + b * (left_edge + 3)][x + a * (left_edge + 3)][direction] = 1;
                                }
                            } else if (Qipan_Array[y + b * (left_edge + 3)][x + a * (left_edge + 3)] == 0 && right1 == 0) {
                                //(左)活三1o11
                                score = score + type * LIVE_THREE;
                                matchChess[y + b * (left_edge + 2)][x + a * (left_edge + 2)][direction] = 1;
                            } else if (Qipan_Array[y + b * (left_edge + 3)][x + a * (left_edge + 3)] == 0 && right1 == -type) {
                                //(左)眠三o1o11x
                                score = score + type * MIAN_THREE;
                                matchChess[y + b * (left_edge + 2)][x + a * (left_edge + 2)][direction] = 1;
                            }
                        }
                    } else if (left1 == 0 && left2 == 0 &&  x + a * (left_edge + 3) > 0 && y + b * (left_edge + 3) > 0 && y + b * (left_edge + 3) < 14) {
                        if (Qipan_Array[y + b * (left_edge + 3)][x + a * (left_edge + 3)] == type) {
                            //(左)眠三1oo11
                            if (matchChess[y + b * (left_edge + 3)][x + a * (left_edge + 3)][direction] == 0){
                                score = score + type * MIAN_THREE;
                                matchChess[y + b * (left_edge + 3)][x + a * (left_edge + 3)][direction] = 1;
                            }
                        } else if (Qipan_Array[y + b * (left_edge + 3)][x + a * (left_edge + 3)] == 0 && right1 == -type) {
                            //(左)眠二ooo11x
                            score = score + type * MIAN_TWO;
                        } else if (Qipan_Array[y + b * (left_edge + 3)][x + a * (left_edge + 3)] == 0 && right1 == 0) {
                            //(左)活二ooo11o
                            score = score + type * LIVE_TWO;
                        }
                    } else if (right1 == 0 && right2 == type && x - a*(right_edge + 3) < 14 && y - b*(right_edge + 3) < 14 &&y - b*(right_edge + 3) > 0) {
                        if (matchChess[y - b*(right_edge + 2)][x - a*(right_edge + 2)][direction] == 0) {
                            if (Qipan_Array[y - b * (right_edge + 3)][x - a * (right_edge + 3)] == type) {
                                //(右)冲四11o11
                                if (matchChess[y - b*(right_edge + 3)][x - a*(right_edge + 3)][direction] == 0){
                                    score = score + type * CHONG_FOUR;
                                    matchChess[y - b * (right_edge + 2)][x - a * (right_edge + 2)][direction] = 1;
                                    matchChess[y - b * (right_edge + 3)][x - a * (right_edge + 3)][direction] = 1;
                                }
                            } else if (Qipan_Array[y][x + right_edge + 3] == 0 && left1 == 0) {
                                //(右)活三1o11
                                score = score + type * LIVE_THREE;
                                matchChess[y - b * (right_edge + 2)][x - a * (right_edge + 2)][direction] = 1;
                            } else if (Qipan_Array[y - b * (right_edge + 3)][x - a * (right_edge + 3)] == 0 &&
                                       left1 == -type) {
                                //(右)眠三o1o11x
                                score = score + type * MIAN_THREE;
                                matchChess[y - b * (right_edge + 2)][x - a * (right_edge + 2)][direction] = 1;
                            }
                        }
                    } else if (right1 == 0 && right2 == 0 && x + right_edge + 3 < 14) {
                        if (Qipan_Array[y - b*(right_edge + 3)][x - a*(right_edge + 3)] == type) {
                            //(右)眠三1oo11
                            if (matchChess[y - b*(right_edge + 3)][x - a*(right_edge + 3)][direction] == 0){
                                score = score + type * MIAN_THREE;
                                matchChess[y - b*(right_edge + 3)][x - a*(right_edge + 3)][direction] = 1;
                            }
                        } else if (Qipan_Array[y - b*(right_edge + 3)][x - a*(right_edge + 3)] == 0 && left1 == -type) {
                            //(右)眠二ooo11x
                            score = score + type * MIAN_TWO;
                        } else if (Qipan_Array[y - b*(right_edge + 3)][x - a*(right_edge + 3)] == 0 && left1 == 0) {
                            //(右)活二ooo11o
                            score = score + type * LIVE_TWO;
                        }
                    }
                    break;
                case 1:
                    if (left1 == 0 && right1 == 0 && left2 == type && right2 == type) {
                        //眠三1o1o1
                        if (matchChess[y - b*(right_edge + 2)][x - a*(right_edge + 2)][direction] == 0&&matchChess[y + b * (left_edge + 2)][x + a*(left_edge + 2)][direction]==0) {
                            score = score + type * MIAN_THREE;
                            matchChess[y - b * (right_edge + 2)][x - a * (right_edge + 2)][direction] = 1;
                            matchChess[y + b * (left_edge + 2)][x + a * (left_edge + 2)][direction] = 1;
                        }
                    } else if (x + a * (left_edge + 3) > 0 && y + b * (left_edge + 3) > 0 && y + b * (left_edge + 3) < 14) {
                        if (matchChess[y + b * (left_edge + 2)][x + a*(left_edge + 2)][direction] == 0) {
                            if (left1 == 0 && right1 == 0 && left2 == type && Qipan_Array[y + b * (left_edge + 3)][x + a*(left_edge + 3)] == 0) {
                                //(左)活二o1o1o
                                score = score + type * LIVE_TWO;
                                matchChess[y + b * (left_edge + 2)][x + a*(left_edge + 2)][direction] = 1;
                            } else if (left1 == 0 && left2 == type && right1 == 0 && right2 == 0 &&
                                       Qipan_Array[y + b * (left_edge + 3)][x + a*(left_edge + 3)] == -type) {
                                //(左)眠二x1o1oo
                                score = score + type * MIAN_TWO;
                                matchChess[y + b * (left_edge + 2)][x + a*(left_edge + 2)][direction] = 1;
                            }
                        }
                    } else if (x - a*(right_edge + 3) < 14 && y - b*(right_edge + 3) < 14 &&y - b*(right_edge + 3) > 0) {
                        if (matchChess[y - b*(right_edge + 2)][x - a*(right_edge + 2)][direction] == 0) {
                            if (right1 == 0 && left1 == 0 && right2 == type &&
                                Qipan_Array[y - b*(right_edge + 3)][x - a*(right_edge + 3)] == 0) {
                                //(右)活二o1o1o
                                score = score + type * LIVE_TWO;
                                matchChess[y - b * (right_edge + 2)][x - a * (right_edge + 2)][direction] = 1;
                            } else if (right1 == 0 && right2 == type && left1 == 0 && left2 == 0 &&
                                       Qipan_Array[y - b * (right_edge + 3)][x - a * (right_edge + 3)] == -type) {
                                //(右)眠二oo1o1x
                                score = score + type * MIAN_TWO;
                                matchChess[y - b * (right_edge + 2)][x - a * (right_edge + 2)][direction] = 1;
                            }
                        }
                    } else if (x + a * (left_edge + 4) > 0 && y + b * (left_edge + 4) > 0 && y + b * (left_edge + 4) < 14) {
                        if (left1 == 0 && right1 == 0 && left2 == 0 && Qipan_Array[y][x - left_edge - 3] == type &&
                            Qipan_Array[y + b * (left_edge + 4)][x + a*(left_edge + 4)] == -type) {
                            //(左)眠二x1oo1o
                            if (matchChess[y + b * (left_edge + 3)][x + a*(left_edge + 3)][direction] == 0) {
                                score = score + type * MIAN_TWO;
                                matchChess[y + b * (left_edge + 3)][x + a * (left_edge + 3)][direction] = 1;
                            }
                        } else if (left1 == 0 && left2 == 0 && Qipan_Array[y + b * (left_edge + 3)][x + a*(left_edge + 3)] == 0 &&
                                   Qipan_Array[y + b * (left_edge + 4)][x + a*(left_edge + 4)] == type) {
                            //(左)眠二1ooo1
                            if (matchChess[y + b * (left_edge + 4)][x + a*(left_edge + 4)][direction] == 0) {
                                score = score + type * MIAN_TWO;
                                matchChess[y + b * (left_edge + 4)][x + a * (left_edge + 4)][direction] = 1;
                            }
                        }
                    } else if (x - a*(right_edge + 4) < 14 && y - b*(right_edge + 4) < 14 &&y - b*(right_edge + 4) > 0) {
                        if (right1 == 0 && left1 == 0 && right2 == 0 && Qipan_Array[y - b*(right_edge + 3)][x - a*(right_edge + 3)] == type &&
                            Qipan_Array[y - b*(right_edge + 4)][x - a*(right_edge + 4)] == -type) {
                            //(左)眠二x1oo1o
                            if (matchChess[y - b*(right_edge + 3)][x - a*(right_edge + 3)][direction] == 0) {
                                score = score + type * MIAN_TWO;
                                matchChess[y - b * (right_edge + 3)][x - a * (right_edge + 3)][direction] = 1;
                            }
                        } else if (right1 == 0 && right2 == 0 && Qipan_Array[y - b*(right_edge + 3)][x - a*(right_edge + 3)] == 0 &&
                                   Qipan_Array[y - b*(right_edge + 4)][x - a*(right_edge + 4)] == type) {
                            //(左)眠二1ooo1
                            if (matchChess[y - b*(right_edge + 4)][x - a*(right_edge + 4)][direction] == 0) {
                                score = score + type * MIAN_TWO;
                                matchChess[y - b * (right_edge + 4)][x - a * (right_edge + 4)][direction] = 1;
                            }
                        }
                    }
                    break;
            }
    }
    return score;
}


void VirtualPut(ChessScore*scores, int i){
    Qipan_Array[scores[i].coord.Y][scores[i].coord.X] = scores[i].chesstype;
    CurrentChess[ChessNums].coord.X = scores[i].coord.X;
    CurrentChess[ChessNums].coord.Y = scores[i].coord.Y;
    CurrentChess[ChessNums].type = scores[i].chesstype;
    ChessNums++;
}

void DeleChess(ChessScore * scores, int i){
    Qipan_Array[scores[i].coord.Y][scores[i].coord.X] = NONE;
    ChessNums--;
}

