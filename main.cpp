#include "main.h"
#include <windows.h>
#include <conio.h>
point best;
int board[col][row]={
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};
int is_empty[row][col]={empty};
int player={black};
int xp,yp;
int PointFlag=0;
int main(int argc,char *argv[]){
    SetConsoleTitle("GoBang");
    ShadowWindowLine("GoBang GAME",2,18,12,26,yes,red);
    ShadowWindowLine("press any key to start",20,18,40,23,no,blue);
    _getch();
    ShadowWindowLine("Game processing!",20,8,40,16,yes,blue);
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE); // 获取标准输入设备句柄
    INPUT_RECORD inRec;
    DWORD res;
    COORD zero={0,0};
    COORD ai={0,0};
    while (1)
    {
        ReadConsoleInput(hInput, &inRec, 1, &res);
        if (inRec.EventType == MOUSE_EVENT) //鼠标左键
        {
            if(inRec.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
            {
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),zero);
                printf("x-%2dy-%2d",inRec.Event.MouseEvent.dwMousePosition.Y,inRec.Event.MouseEvent.dwMousePosition.X);
                Sleep(100);
            }
            if(inRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED){
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),inRec.Event.MouseEvent.dwMousePosition);
                xp=inRec.Event.MouseEvent.dwMousePosition.Y;
                yp=inRec.Event.MouseEvent.dwMousePosition.X;
                if(board[xp][yp]!=empty){ continue;}
                board[xp][yp]=1;
                PointFlag=1;
                if(xp<1||xp>=16||yp<1||yp>=16) { continue;}
                if(is_end(xp,yp,1)){
                    ShadowWindowLine("you win!",20,2,30,6,yes,red);
                    _getch();
                    break;
                }
                printf("x");
                Sleep(100);
            }
            if(PointFlag==1)
            {
                max_min(2,2);
                board[best.x][best.y]=2;
                if(is_end(best.x,best.y,2)){
                    ShadowWindowLine("you lose",20,2,30,6,yes,blue);
                    _getch();
                    break;
                }
                ai={(short)(best.y),(short)best.x};
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),ai);
                printf("o");
                PointFlag=0;
            }
        }
    }
//    int l=is_end(1,1,black);
//    printf("%d",l);
    return 0;
}
