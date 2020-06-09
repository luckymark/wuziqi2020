#ifndef WUZIQI2020_GAME_H
#define WUZIQI2020_GAME_H

const int kBoardSizeNum = 15;
const int Deep = 2;

enum Player {
    NONE,
    PERSON,
    AI
};

enum Chess {
    SPACE,
    BLACK, // Player
    WHITE // AI
};

class Game {
public:
    Chess map[kBoardSizeNum][kBoardSizeNum]{SPACE};
    Player player{PERSON};
    Player isWin{NONE};

    bool chessByPerson(int clickPosRow, int clickPosCol);
    void chessByAI();

private:
    int steps{0};

    bool available(int row, int col);
    static int calc(int same, int dead, Chess chess);
    int evaluate();
    Player checkWin();
    Player switchWin(int row, int col);
    void search(int deep);
    int maxmin(int deep, int ab);
    int gen_points(int points[255][2]);
};


#endif //WUZIQI2020_GAME_H
