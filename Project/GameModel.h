#ifndef GAMEMODEL_H
#define GAMEMODEL_H
#include <vector>
enum GameType           // 游戏类型，选择是人机还是人人
{
    PERSON,
    BOT
};
enum GameStatus
{
    GAMING,
    WIN,
    DEAD
};
const int brdSz = 17;    // 棋盘尺寸设定，为了放置bug边缘不能落子，所以实际上还是15*15
class GameModel
{
public:
    GameModel();
public:
    std::vector<std::vector<int>> gmVc; // 储存当前游戏棋盘和棋子的情况
    std::vector<std::vector<int>> scVc;
    bool plOpt;
    GameType gameType;
    GameStatus gameStat;
    void startGame(GameType type);
    void scrCal();
    void PlayerAct(int row, int col);
    void AIAct(int &clickRow, int &clickCol);
    void MapUpd(int row, int col);
    bool isWin(int row, int col); // 判断是否有一方取得胜利
    bool isDead(); // 判断是否出现了僵局
};
#endif
