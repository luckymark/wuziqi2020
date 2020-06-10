//
// Created by pointkab on 2020/4/23.
//

#include "initWindow.h"
#include "game.h"

void InitWindow(){
    int i;
    setinitmode(0);
    initgraph(600, 485);//打开一个长640像素，宽480像素的窗口
    setfont(18,0,"宋体");
    setcaption("wuziqi");
    setbkcolor(WHITE);
    setcolor(BLACK);
    for (i = 0; i < 15; i++)
    {
        line(START_X + DXY * i, START_Y, START_X + DXY * i, START_Y + 14 * DXY);
        line(START_X, START_Y+ DXY * i, START_X + 14 * DXY, START_Y + DXY * i);
    }
    PIMAGE qipan;
    qipan = newimage();
    getimage(qipan, "qipan.jpg");
    putimage(0,0,qipan);
}

int PutItems(const int x, const int y, const int Is_B_OR_W, const int Ai_Or_Player){
    int chessValue = -1;
    int Temp_x,Temp_y;
    int Judge_x, Judge_y;
    int tx, ty;
    if (Ai_Or_Player ==1) {
        Judge_x = Accurate_Coord(x, 1);
        Judge_y = Accurate_Coord(y, -1);
        Temp_x = START_X + DXY * Judge_x;
        Temp_y = START_Y + DXY * Judge_y;
        tx = Judge_x;
        ty = Judge_y;
    }else{
        Temp_x = START_X + DXY * x;
        Temp_y = START_Y + DXY * y;
        tx = x;
        ty = y;
    }

    if (x > RIGHT_BODER||Judge_Is_Empty(tx, ty))
    {
        return chessValue;
    }

    if (Is_B_OR_W == 1){
        setfillcolor(BLACK);
    } else if(Is_B_OR_W == 0){
        setfillcolor(WHITE);
    }

    fillellipse(Temp_x, Temp_y, 15, 15);

    if (Ai_Or_Player == 1) {
        Qipan_Array[Judge_y][Judge_x] = PLAYER_CHESS;
        CurrentChess[ChessNums].coord.X= Judge_x;
        CurrentChess[ChessNums].coord.Y = Judge_y;
        CurrentChess[ChessNums].type = -1;
        ChessNums++;
    } else if (Ai_Or_Player == 0){
        Qipan_Array[y][x] = AI_CHESS;
        CurrentChess[ChessNums].coord.X= x;
        CurrentChess[ChessNums].coord.Y= y;
        CurrentChess[ChessNums].type = 1;
        ChessNums++;
    }
    return 1;
}

int Accurate_Coord(const int coord_value, const int coord_type)
{
    int Accurate_coord;
    int Type;
    if(coord_type == 1){
        //x coord
        Type = START_X;
    }if(coord_type == -1)
    {
        //y coord
        Type = START_Y;
    }
    Accurate_coord = (coord_value - Type)/DXY;
    int temp = (coord_value - Type)%DXY;
        if(temp <= TOLERANCE&& Accurate_coord >= 0)
        {
            return Accurate_coord;
        }
        else if(Judge(temp, Accurate_coord)){
            return Accurate_coord + 1;
        }
        else{
            return -1;//无效区域
        }
}
//判断点击是在哪
int Judge(int temp, int Accurate_coord)
{
    return (temp >= -TOLERANCE && temp <= 0 && Accurate_coord == 0) || (temp > (31-TOLERANCE) && Accurate_coord <= 14);
}

int Judge_Is_Empty(const int x, const int y)
{
    if(x == -1||y == -1)
    {
        return 1;
    } else if(Qipan_Array[y][x] != 0)
    {
        return 1;
    }
    return 0;
}