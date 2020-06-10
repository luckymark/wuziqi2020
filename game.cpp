//
// Created by pointkab on 2020/4/24.
//

#include "game.h"
#include <ctime>

extern int alpha0, beta0;

int Qipan_Array[QIPAN_SIZE][QIPAN_SIZE] = {0};

int ChessNums = 0;

struct currentchess CurrentChess[225];

int Game_Body()
{
    int Who_Is_Win;
    while (1)
    {
        /*这里可以加菜单部分*/

        /*开始游戏*/

        Player_Play();
        Sleep(50);
        if ((Who_Is_Win = EvaluateAllChess(1)) != 0)
        {
            JudgeWin(Who_Is_Win);
            int temp = Restart();
            if (temp)
            {
                continue;
            }
            break;
        }
        if (ChessNums >= 225)
        {
            JudgeWin(Who_Is_Win);
            int temp = Restart();
            if (temp)
            {
                continue;
            }
            break;
        }
        AI_Play();
        if ((Who_Is_Win = EvaluateAllChess(1)) != 0)
        {
            JudgeWin(Who_Is_Win);
            int temp = Restart();
            if (temp)
            {
                continue;
            }
            break;
        }
        Sleep(50);
    }
}

int Player_Play()
{
    mouse_msg msg = {0};
    for (;is_run();delay_fps(60))
    {
        while(mousemsg())
        {
            msg = getmouse();
        }
        if(msg.is_left())
        {
            int Value = PutItems(msg.x,msg.y,1,1);
            if(Value == 1)
            {
                break;
            }
        }
    }
}

void AI_Play(){
    if(ChessNums == 1)
    {
        srand((unsigned)time(NULL));
        int a;
        int b;
        int temp_a;
        int temp_b;
        do{
            a = rand()%3-1;
            b = rand()%3-1;
            temp_a = a + CurrentChess[ChessNums-1].coord.X;
            temp_b = b + CurrentChess[ChessNums-1].coord.Y;
        }while((a == 0&&b == 0)|| temp_a > 14||temp_a < 0||temp_b > 14 || temp_b < 0);
        PutItems(temp_a, temp_b, 0, 0);
    } else {
        Search_Tree(4, alpha0, beta0);
        int x = Delocation.coord.X;
        int y = Delocation.coord.Y;
        PutItems(x, y, 0, 0);
    }

    return;
}

int Restart(){
    int Is_continue;
    outtextxy(478, 40, "press any key");
    outtextxy(478, 60, "to continue");
    if (getch())
    {
        InitWindow();
        ChessNums = 0;
        memset(Qipan_Array,0,15*15*sizeof(int));
        Is_continue = 1;
    } else {
        Is_continue = 0;
    }
    return Is_continue;
}

void JudgeWin(int result){
    if (result == -1)
    {
        //ai is win
        outtextxy(478, 20, "You lose!");
    }
    if (result == 0)
    {
        //draw
        outtextxy(478, 20, "Draw!");
    }
    if (result == 1)
    {
        //player is win
        outtextxy(478, 20, "You win!");
    }
}
