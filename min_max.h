//#pragma comment(lib,"User32.lib")
#ifndef MIN_MAX_H
#define MIN_MAX_H

#include "score_count.h"
#include <vector>
//#pragma comment(lib,"ws2_32.lib")
extern int chess_board[25][25];
int max_search(int depths, int alpa);
int min_search(int depths, int beta);
void AImax_search(int& xxx, int& yyy, int depths);
int evaluate_minmax();
int evaluate_minmax() {      //这是评估函数
    const int SIZES = 15;
    int scoreAI = 0;
    int scoreplayer = 0;
    for (int i = 0; i < SIZES; i++) {    //横排
        std::vector <int> v;
        for (int j = 0; j < SIZES; j++)
            v.push_back(chess_board[i][j]);
        scoreplayer += count_score(v, 1);
        scoreAI += count_score(v, 2);
        v.clear();
    }
    for (int j = 0; j < SIZES; j++) {    //竖排
        std::vector <int> v;
        for (int i = 0; i < SIZES; i++)
            v.push_back(chess_board[i][j]);
        scoreplayer += count_score(v, 1);
        scoreAI += count_score(v, 2);
        v.clear();
    }
    for (int i = 0; i < SIZES; i++) {    //上半正斜线
        int ddx, ddy;
        std::vector <int> v;
        for (ddx = i, ddy = 0; ddx < SIZES && ddy < SIZES; ++ddx, ++ddy)
            v.push_back(chess_board[ddy][ddx]);
        scoreplayer += count_score(v, 1);
        scoreAI += count_score(v, 2);
        v.clear();
    }
    for (int j = 1; j < SIZES; j++) {    //下半正斜线
        int ddx, ddy;
        std::vector <int> v;
        for (ddx = 0, ddy = j; ddy < SIZES && ddx < SIZES; ddx++, ddy++)
            v.push_back(chess_board[ddy][ddx]);
        scoreplayer += count_score(v, 1);
        scoreAI += count_score(v, 2);
        v.clear();
    }
    for (int i = 0; i < SIZES; i++) {      //上半反斜线
        std::vector <int> v;
        int ddx, ddy;
        for (ddy = i, ddx = 0; ddy >= 0 && ddx < SIZES; ddy--, ddx++)
            v.push_back(chess_board[ddy][ddx]);
        scoreplayer += count_score(v, 1);
        scoreAI += count_score(v, 2);
        v.clear();
    }
    for (int j = 1; j < SIZES; j++) {
        std::vector <int> v;
        int ddx, ddy;
        for (ddy = j, ddx = SIZES - 1; ddy < 16 && ddx >= 0; ddy++, ddx--)
            v.push_back(chess_board[ddx][ddy]);
        scoreplayer += count_score(v, 1);
        scoreAI += count_score(v, 2);
        v.clear();
    }
    return scoreAI - scoreplayer;
} 
//, int beta        不加大概跑1min（54.96s)，加了大概40s左右(41.98s)
int min_search(int depths,int beta) {    
    if (depths <= 0) {
        int res = evaluate_minmax();
        return res;
    }
    std::vector < std::pair<std::pair<int, int>,int> > vv;
    genarator_point(vv, 1);
    int Length = vv.size();
    int best = INT_MAX;
    for (int i = 0; i < Length; i++) {
        int t1 = vv[i].first.first;
        int t2 = vv[i].first.second;
        chess_board[t1][t2] = 1;
        int temps = max_search(depths - 1, best < beta ? best : beta);
        chess_board[t1][t2] = 0;
        if (temps < best)  best = temps;
        if (temps < beta)  break;
//        int temps = max_search(depths - 1, best < alpha ? best : alpha);
//        if (temps < best)  best = temps;
 //       if (temps < beta)  break;  //剪枝
    }

    return best;
}
//, int alpha
int max_search(int depths,int alpa) {
    if (depths <= 0) {
        int res = evaluate_minmax();
        return res;
    }
    std::vector < std::pair<std::pair<int, int>,int> > vv;
    genarator_point(vv, 2);
    int Length = vv.size();
    int best = INT_MIN;
    for (int i = 0; i < Length; i++) {
        int t1 = vv[i].first.first;
        int t2 = vv[i].first.second;
        chess_board[t1][t2] = 1;
        int temps = min_search(depths - 1, best > alpa ? best : alpa);
        chess_board[t1][t2] = 0;
        if (temps > best)  best = temps;
        if (temps > alpa)  break;
//        int temps = min_search(depths - 1, best > beta ? best : beta);
//        if (temps > best)  best = temps;
//        if (temps > alpha) break;//剪枝
    }
    
    return best;
}

void AImax_search(int& xxx, int& yyy, int depths) {
    std::vector <std::pair<std::pair <int, int>,int> >  vv;
    genarator_point(vv, 2);
    int best = INT_MIN;
    int Length = vv.size();
    std::vector <std::pair<std::pair <int, int>,int> > vv2;
    for (int i = 0; i < Length; i++) {
        int t1 = vv[i].first.first;
        int t2 = vv[i].first.second;
        chess_board[t1][t2] = 2;
        int temp = min_search(depths - 1, best);
        if (temp > best) {
            best = temp;
            vv2.clear();
            vv2.push_back(vv[i]);
        }
        else {
            if (temp == best) {
                vv2.push_back(vv[i]);
            }
        }
        chess_board[t1][t2] = 0;
    }
    int Length2 = vv2.size();
    int choose = (int)(rand() % Length2);
    xxx = vv2[choose].first.first;
    yyy = vv2[choose].first.second;
}


#endif 
