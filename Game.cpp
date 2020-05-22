#include <windows.h>
#include "Game.h"

bool Game::chessByPerson(int clickPosRow, int clickPosCol) {
    if (clickPosRow >= 0 && clickPosRow <= kBoardSizeNum &&
        clickPosCol >= 0 && clickPosCol <= kBoardSizeNum &&
        map[clickPosRow][clickPosCol] == SPACE) {
        map[clickPosRow][clickPosCol] = BLACK;
        player = AI;
        return true;
    }
    return false;
}

void Game::chessByAI() {
    // TODO
    player = PERSON;
}
