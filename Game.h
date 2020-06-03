#ifndef WUZIQI2020_GAME_H
#define WUZIQI2020_GAME_H

const int kBoardSizeNum = 15;
const int maxDeep = 2;
const int firstSteps = 15;

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

typedef struct step {
    int row, col;
    int point;
    int nextLength;
    struct step *nextSteps[225];
} Step;

class Game {
public:
    Chess map[kBoardSizeNum][kBoardSizeNum]{SPACE};
    Player player{PERSON};
    Player isWin{NONE};

    bool chessByPerson(int clickPosRow, int clickPosCol);
    void chessByAI();

private:
    int steps{0};
    Step rootStep{};

    bool available(int row, int col);
    static int calc(int same, int dead, Chess chess);
    int evaluate();
    void gen_steps(Step *step, int deep);
    void destroy_steps(Step *step, int deep);
    void checkWin(int row, int col);
    void switchWin(int row, int col);
};


#endif //WUZIQI2020_GAME_H
