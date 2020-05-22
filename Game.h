#ifndef WUZIQI2020_GAME_H
#define WUZIQI2020_GAME_H

const int kBoardSizeNum = 15;

enum Player {
    PERSON,
    AI
};

enum Chess {
    SPACE,
    BLACK,
    WHITE
};

class Game {
public:
    Chess map[kBoardSizeNum][kBoardSizeNum] {SPACE};
    Player player {PERSON};
    bool chessByPerson(int clickPosRow, int clickPosCol);
    void chessByAI();
};


#endif //WUZIQI2020_GAME_H
