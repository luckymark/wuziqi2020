#include "Game.h"
#include "points.h"

bool Game::chessByPerson(int clickPosRow, int clickPosCol) {
    if (clickPosRow >= 0 && clickPosRow <= kBoardSizeNum &&
        clickPosCol >= 0 && clickPosCol <= kBoardSizeNum &&
        map[clickPosRow][clickPosCol] == SPACE) {
        map[clickPosRow][clickPosCol] = BLACK;
        checkWin(clickPosRow, clickPosCol);
        steps++;
        player = AI;
        return true;
    }
    return false;
}

void Game::chessByAI() {
    gen_steps(&rootStep, maxDeep);
    Step *nextStep = rootStep.nextSteps[0];
    for (int i = 1; i < rootStep.nextLength; i++) {
        if (rootStep.nextSteps[i]->point > nextStep->point) {
            nextStep = rootStep.nextSteps[i];
        }
    }
    map[nextStep->row][nextStep->col] = WHITE;
    checkWin(nextStep->row, nextStep->col);
    destroy_steps(&rootStep, maxDeep);
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
                if (same - dead == 3) {
                    same++;
                }
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

void Game::gen_steps(Step *step, int deep) {
    if (deep != 0) {
        step->nextLength = 0;
        for (int row = 0; row < kBoardSizeNum; row++) {
            for (int col = 0; col < kBoardSizeNum; col++) {
                if (available(row, col)) {
                    Step *newStep = new Step;
                    newStep->row = row;
                    newStep->col = col;
                    if (deep % 2 == 0) {
                        map[row][col] = WHITE;
                    } else {
                        map[row][col] = BLACK;
                    }
                    newStep->point = evaluate();
                    if (deep == maxDeep || steps < firstSteps || newStep->point > step->point + 100) {
                        step->nextSteps[step->nextLength] = newStep;
                        step->nextLength++;
                        gen_steps(newStep, deep - 1);
                        map[row][col] = SPACE;
                    } else {
                        delete newStep;
                        step->nextLength--;
                        delete step;
                        map[row][col] = SPACE;
                        return;
                    }
                }
            }
        }
    }
}

void Game::destroy_steps(Step *step, int deep) {
    if (deep != 0) {
        for (int i = 0; i < step->nextLength; i++) {
            destroy_steps(step->nextSteps[i], deep - 1);
            if (deep != maxDeep) {
                delete step;
            }
        }
    }
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

void Game::checkWin(int row, int col) {
    for (int i = 0; i < 5; i++) {
        // Vertical
        if (row - i > 0 && row - i + 4 < kBoardSizeNum &&
            map[row - i][col] == map[row - i + 1][col] &&
            map[row - i][col] == map[row - i + 2][col] &&
            map[row - i][col] == map[row - i + 3][col] &&
            map[row - i][col] == map[row - i + 4][col]) {
            switchWin(row, col);
            return;
        }
        // Horizontal
        if (col - i > 0 && col - i + 4 < kBoardSizeNum &&
            map[row][col - i] == map[row][col - i + 1] &&
            map[row][col - i] == map[row][col - i + 2] &&
            map[row][col - i] == map[row][col - i + 3] &&
            map[row][col - i] == map[row][col - i + 4]) {
            switchWin(row, col);
            return;
        }
        // Lower right
        if (row - i > 0 && row - i + 4 < kBoardSizeNum &&
            col - i > 0 && col - i + 4 < kBoardSizeNum &&
            map[row - i][col - i] == map[row - i + 1][col - i + 1] &&
            map[row - i][col - i] == map[row - i + 2][col - i + 2] &&
            map[row - i][col - i] == map[row - i + 3][col - i + 3] &&
            map[row - i][col - i] == map[row - i + 4][col - i + 4]) {
            switchWin(row, col);
            return;
        }
        // Higher right
        if (row + i - 4 > 0 && row + i < kBoardSizeNum &&
            col - i > 0 && col - i + 4 < kBoardSizeNum &&
            map[row + i][col - i] == map[row + i - 1][col - i + 1] &&
            map[row + i][col - i] == map[row + i - 2][col - i + 2] &&
            map[row + i][col - i] == map[row + i - 3][col - i + 3] &&
            map[row + i][col - i] == map[row + i - 4][col - i + 4]) {
            switchWin(row, col);
            return;
        }
    }
}

void Game::switchWin(int row, int col) {
    switch (map[row][col]) {
        case WHITE:
            isWin = AI;
            break;
        case BLACK:
            isWin = PERSON;
            break;
        default:
            break;
    }
}
