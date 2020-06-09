#include <stdlib.h>
#include <limits.h>
#include "Game.h"
#include "points.h"

bool Game::chessByPerson(int clickPosRow, int clickPosCol) {
    if (clickPosRow >= 0 && clickPosRow <= kBoardSizeNum &&
        clickPosCol >= 0 && clickPosCol <= kBoardSizeNum &&
        map[clickPosRow][clickPosCol] == SPACE) {
        map[clickPosRow][clickPosCol] = BLACK;
        isWin = checkWin();
        steps++;
        player = AI;
        return true;
    }
    return false;
}

void Game::chessByAI() {
    search(Deep);
    isWin = checkWin();
    steps++;
    player = PERSON;
}

int Game::calc(int same, int dead, Chess chess) {
    int point = 0;
    if (dead < 2) {
        switch (chess) {
            case WHITE:
                point = points[same-dead];
                break;
            case BLACK:
                point = -(points[same-dead]);
                break;
            default:
                break;
        }
    }
    return point;
}

int Game::evaluate() {
    int all_points = 0;

    for (int row = 0; row < kBoardSizeNum; row++) {
        for (int col = 0; col < kBoardSizeNum; col++) {
            if (map[row][col] != SPACE) {
                // Vertical
                if (row == 0 || map[row][col] != map[row - 1][col]) {
                    int same = 1;
                    int dead = 0;
                    while (row + same < kBoardSizeNum && same < 5 && map[row + same][col] == map[row][col]) {
                        ++same;
                    }
                    if (row == 0 || map[row - 1][col] != SPACE) {
                        ++dead;
                    }
                    if (row + same == kBoardSizeNum || map[row + same][col] != SPACE) {
                        ++dead;
                    }
                    all_points += calc(same, dead, map[row][col]);
                }
                // Horizontal
                if (col == 0 || map[row][col] != map[row][col - 1]) {
                    int same = 1;
                    int dead = 0;
                    while (col + same < kBoardSizeNum && same < 5 && map[row][col + same] == map[row][col]) {
                        ++same;
                    }
                    if (col == 0 || map[row][col - 1] != SPACE) {
                        ++dead;
                    }
                    if (col + same == kBoardSizeNum || map[row][col + same] != SPACE) {
                        ++dead;
                    }
                    all_points += calc(same, dead, map[row][col]);
                }
                // Lower right
                if (row == 0 || col == 0 || map[row][col] != map[row - 1][col - 1]) {
                    int same = 1;
                    int dead = 0;
                    while (row + same < kBoardSizeNum && col + same < kBoardSizeNum && same < 5 &&
                           map[row + same][col + same] == map[row][col]) {
                        ++same;
                    }
                    if (row == 0 || col == 0 || map[row - 1][col - 1] != SPACE) {
                        ++dead;
                    }
                    if (row + same == kBoardSizeNum || col + same == kBoardSizeNum ||
                        map[row + same][col + same] != SPACE) {
                        ++dead;
                    }
                    all_points += calc(same, dead, map[row][col]);
                }
                // Higher right
                if (row == kBoardSizeNum - 1 || col == 0 || map[row][col] != map[row + 1][col - 1]) {
                    int same = 1;
                    int dead = 0;
                    while (row - same >= 0 && col + same < kBoardSizeNum && same < 5 &&
                           map[row - same][col + same] == map[row][col]) {
                        ++same;
                    }
                    if (row == kBoardSizeNum - 1 || col == 0 || map[row + 1][col - 1] != SPACE) {
                        ++dead;
                    }
                    if (row - same == -1 || col + same == kBoardSizeNum || map[row - same][col + same] != SPACE) {
                        ++dead;
                    }
                    all_points += calc(same, dead, map[row][col]);
                }
            }
        }
    }

    return all_points;
}

bool Game::available(int row, int col) {
    if (map[row][col] == SPACE) {
        for (int row0 = row - 2 < 0 ? 0 : row - 2; row0 < (row + 2 > kBoardSizeNum - 1 ? kBoardSizeNum - 1 : row + 2); row0++) {
            for (int col0 = col - 2 < 0 ? 0 : col - 2; col0 < (col + 2 > kBoardSizeNum - 1 ? kBoardSizeNum - 1 : col + 2); col0++) {
                if (map[row0][col0] != SPACE) {
                    return true;
                }
            }
        }
    }
    return false;
}

Player Game::checkWin() {
    for (int row = 0; row < kBoardSizeNum; row++) {
        for (int col = 0; col < kBoardSizeNum; col++) {
            if (map[row][col] != SPACE) {
                // Vertical
                if (row > 0 && row + 4 < kBoardSizeNum &&
                    map[row][col] == map[row + 1][col] &&
                    map[row][col] == map[row + 2][col] &&
                    map[row][col] == map[row + 3][col] &&
                    map[row][col] == map[row + 4][col]) {
                    return switchWin(row, col);
                }
                // Horizontal
                if (col > 0 && col + 4 < kBoardSizeNum &&
                    map[row][col] == map[row][col + 1] &&
                    map[row][col] == map[row][col + 2] &&
                    map[row][col] == map[row][col + 3] &&
                    map[row][col] == map[row][col + 4]) {
                    return switchWin(row, col);
                }
                // Lower right
                if (row > 0 && row + 4 < kBoardSizeNum &&
                    col > 0 && col + 4 < kBoardSizeNum &&
                    map[row][col] == map[row + 1][col + 1] &&
                    map[row][col] == map[row + 2][col + 2] &&
                    map[row][col] == map[row + 3][col + 3] &&
                    map[row][col] == map[row + 4][col + 4]) {
                    return switchWin(row, col);
                }
                // Higher right
                if (row - 4 > 0 && row < kBoardSizeNum &&
                    col > 0 && col + 4 < kBoardSizeNum &&
                    map[row][col] == map[row - 1][col + 1] &&
                    map[row][col] == map[row - 2][col + 2] &&
                    map[row][col] == map[row - 3][col + 3] &&
                    map[row][col] == map[row - 4][col + 4]) {
                    return switchWin(row, col);
                }
            }
        }
    }

    return NONE;
}

Player Game::switchWin(int row, int col) {
    switch (map[row][col]) {
        case WHITE:
            return AI;
        case BLACK:
            return PERSON;
        default:
            return NONE;
            break;
    }
}

void Game::search(int deep) {
    int best = INT_MIN;
    int points[255][2];
    int length = gen_points(points);
    int best_points[255][2];
    int best_length = 0;

    for (int i = 0; i < length; i++) {
        int row = points[i][0];
        int col = points[i][1];
        map[row][col] = WHITE;
        int v = maxmin(deep - 1, INT_MAX, INT_MIN);
        map[row][col] = SPACE;
        if (v == best) {
            best_points[best_length][0] = row;
            best_points[best_length][1] = col;
            best_length++;
        }
        if (v > best) {
            best = v;
            best_length = 0;
            best_points[best_length][0] = row;
            best_points[best_length][1] = col;
            best_length++;
        }
    }

    int point = rand() % best_length;
    int row = best_points[point][0];
    int col = best_points[point][1];
    map[row][col] = WHITE;
}

int Game::maxmin(int deep, int alpha, int beta) {
    int v = evaluate();
    Player win = checkWin();
    if (deep <= 0 || win != NONE) {
        return v;
    }
    int best = INT_MIN;
    int points[255][2];
    int length = gen_points(points);
    int ab = 0;

    for (int i = 0; i < length; i++) {
        int row = points[i][0];
        int col = points[i][1];
        if (deep % 2 == 0) {
            map[row][col] = WHITE;
            int v = maxmin(deep - 1, alpha, best > beta ? best : beta);
            if (v > alpha) {
                ab = 1;
            }
        } else {
            map[row][col] = BLACK;
            int v = maxmin(deep - 1, best < alpha ? best : alpha, beta);
            if (v < beta) {
                ab = 1;
            }
        }
        map[row][col] = SPACE;
        if (v > best) {
            best = v;
        }
        if (ab == 1) {
            break;
        }
    }

    return best;
}

int Game::gen_points(int points[255][2]) {
    int length = 0;
    for (int row = 0; row < kBoardSizeNum; row++) {
        for (int col = 0; col < kBoardSizeNum; col++) {
            if (available(row, col)) {
                points[length][0] = row;
                points[length][1] = col;
                length++;
            }
        }
    }
    return length;
}
