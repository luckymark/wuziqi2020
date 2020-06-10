//#pragma comment(lib,"User32.lib")
#ifndef SCORE_COUNT_H
#define SCORE_COUNT_H

#include <vector>
#include <cmath>
#include <algorithm>
//#pragma comment(lib,"ws2_32.lib")
const int Max_point = 100000;
extern int chess_board[25][25];
bool checks(int d_x, int d_y);
void genarator_point(std::vector <std::pair<std::pair<int, int>, int> >& v, int turn);
int score_table(int number, int emptys);
int count_score(std::vector<int> v_v, int turn);
bool cmp_increase(std::pair<std::pair<int, int>, int> A, std::pair<std::pair<int, int>, int> B);
bool cmp_decrease(std::pair<std::pair<int, int>, int> A, std::pair<std::pair<int, int>, int> B);
int gen_count(int ddx, int ddy, int turn);
bool cmp_increase(std::pair<std::pair<int, int>, int> A, std::pair<std::pair<int, int>, int> B) {
    return A.second < B.second;
}
bool cmp_decrease(std::pair<std::pair<int, int>, int> A, std::pair<std::pair<int, int>, int> B) {
    return A.second > B.second;
}
int gen_count(int ddx, int ddy,int turn) {
    int temp_score = 0;
    int numbers = 1, emptys = 0;
    for (int j = ddy+1; j < 15; j++) {
        if (chess_board[ddx][j] != turn) {
            if (!chess_board[ddx][j])   emptys++;
            break;
        }
        numbers++;
    }
    for (int j = ddy - 1; j >= 0; j--) {
        if (chess_board[ddx][j] != turn) {
            if (!chess_board[ddx][j])   emptys++;
            break;
        }
        numbers++;
    }
    temp_score += score_table(numbers, emptys);
    numbers = 1, emptys = 0;
    for (int i = ddx + 1; i < 15; i++) {
        if (chess_board[i][ddy] != turn) {
            if (!chess_board[i][ddy])   emptys++;
            break;
        }
        numbers++;
    }
    for (int i = ddx - 1; i >= 0; i--) {
        if (chess_board[i][ddy] != turn) {
            if (!chess_board[i][ddy])   emptys++;
            break;
        }
        numbers++;
    }
    temp_score += score_table(numbers, emptys);
    numbers = 1, emptys = 0;
    for (int i = 1; (i + ddx) < 15 && (i + ddy) < 15; i++) {
        int xxx = i + ddx;
        int yyy = i + ddy;
        if (chess_board[xxx][yyy] != turn) {
            if (!chess_board[xxx][yyy])  emptys++;
            break;
        }
        numbers++;
    }
    for (int i = 1; (ddx - i) >= 0 && (ddy - i) >= 0; i++) {
        int xxx = ddx - i;
        int yyy = ddy - i;
        if (chess_board[xxx][yyy] != turn) {
            if (!chess_board[xxx][yyy])  emptys++;
            break;
        }
        numbers++;
    }
    temp_score += score_table(numbers, emptys);
    numbers = 1, emptys = 0;
    for (int i = 1; (ddx - i) >= 0 && (ddy + i) < 15; i++) {
        int xxx = ddx - i;
        int yyy = ddy + i;
        if (chess_board[xxx][yyy] != turn) {
            if (!chess_board[xxx][yyy])  emptys++;
            break;
        }
        numbers++;
    }
    for (int i = 1; (ddx + i) < 15 && (ddy - i) >= 0; i++) {
        int xxx = ddx + i;
        int yyy = ddy - i;
        if (chess_board[xxx][yyy] != turn) {
            if (!chess_board[xxx][yyy])  emptys++;
            break;
        }
        numbers++;
    }
    temp_score += score_table(numbers, emptys);
    return temp_score;
}
bool checks(int d_x, int d_y) {
    const int SIZES = 15;
    for (int i = (d_x - 2) > 0 ? d_x - 2 : 0; i <= d_x + 2 && i < SIZES; i++) {
        for (int j = (d_y - 2) > 0 ? d_y - 2 : 0; j <= d_y + 2 && j < SIZES; j++) {
            if (chess_board[i][j]) {
                return true;
            }
        }
    }
    return false;
}
void genarator_point(std::vector <std::pair<std::pair<int, int> ,int> >& v,int turn) {
    const int SIZES = 15;
    for (int i = 0; i < SIZES; i++) {
        for (int j = 0; j < SIZES; j++) {
            if (chess_board[i][j] == 0 && checks(i, j)) {
                std::pair<std::pair <int, int>, int >p;
                p.first.first = i;
                p.first.second = j;
                
                p.second = gen_count(i, j, turn);
                v.push_back(p);
            }
        }
    }
    if (turn == 1) std::sort(v.begin(), v.end(), cmp_increase);
    if (turn == 2) std::sort(v.begin(), v.end(), cmp_decrease);
}
int score_table(int number, int emptys) {
    if (number >= 5)   return Max_point;
    if (number == 4) {
        if (emptys == 2)   return Max_point / 10;
        else {
            if (emptys == 1)   return Max_point / 100;
        }
    }
    if (number == 3) {
        if (emptys == 2)   return Max_point / 100;
        else {
            if (emptys == 1)   return Max_point / 1000;
        }
    }
    if (number == 2) {
        if (emptys == 2)   return Max_point / 1000;
        else {
            if (emptys == 1)   return Max_point / 10000;
        }
    }
    if (number == 1 && emptys == 2)    return Max_point / 10000;
    return 0;
}
int count_score(std::vector<int> v_v, int turn) {
    int temp_score = 0;          //积分总数
    int Length = v_v.size();      //横排，竖排，上斜线，下斜线
    int emptys = 0;           //空子个数
    int number = 0;           //计算turn代表的人所握棋子个数，1是黑，2是白
    for (int i = 0; i < Length; i++) {
        if (v_v[i] == turn)    number++;
        else {
            if (!v_v[i]) {
                if (!number) emptys = 1;
                else {           
                    temp_score += score_table(number, emptys+1);
                    emptys = 1;
                    number = 0;
                }
            }
            else {
                temp_score += score_table(number, emptys);
                emptys = 0;
                number = 0;
            }
        }
    }
    temp_score += score_table(number, emptys);
    return temp_score;
}
#endif
