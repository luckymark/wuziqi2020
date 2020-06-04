//
// Created by pointkab on 2020/4/24.
//

#include <cstdio>
#include "game.h"
#include <ctime>



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
        Sleep(200);
        AI_Play();
        Sleep(200);
    }
    return Who_Is_Win;
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
//        else if(msg.is_right())
//        {
//            PutItems(msg.x,msg.y,0,0);
//            break;
//        }
    }
}

void AI_Play(){
    /*待修改，电脑下的第一步*/
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
        Search_Tree(4);
        int x = Delocation.coord.X;
        int y = Delocation.coord.Y;
        PutItems(x, y, 0, 0);
    }

    return;
}

