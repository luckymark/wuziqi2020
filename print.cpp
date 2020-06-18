//
// Created by 20694 on 2020/6/17.
//
#include "print.h"
#include <windows.h>

HANDLE hin;

void ShadowWindowLine(const char* s,int left,int top,int right,int bottom,int shadow,int color){
    HANDLE hout =GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO bInfo;
    SMALL_RECT rc;
    WORD att0,att1,attText;
    int i,chNum=strlen(s);
    GetConsoleScreenBufferInfo(hout,&bInfo);
    rc.Left=left;
    rc.Top=top;
    rc.Right=rc.Left+chNum;
    rc.Bottom=rc.Top+4;
    att0=BACKGROUND_INTENSITY;
    if(color==red){att1=FOREGROUND_RED |FOREGROUND_GREEN |FOREGROUND_BLUE | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE;}
    if(color==blue){att1=FOREGROUND_RED |FOREGROUND_GREEN |FOREGROUND_BLUE | FOREGROUND_INTENSITY | BACKGROUND_BLUE;}
    attText=FOREGROUND_RED |FOREGROUND_INTENSITY;
    COORD posShadow={(short)(rc.Left+1),(short)(rc.Top+1)},posText={(short)(rc.Left),(short)(rc.Top)};
    DWORD a= NULL;
    if(shadow==yes){
        for(i=0;i<5;i++){
          FillConsoleOutputAttribute(hout, att0,chNum+4, posShadow,&a);
          posShadow.Y++;
        }
    }
    for (i=0;i<5;i++)
    {
        FillConsoleOutputAttribute(hout, att1,chNum + 4, posText, &a);
        posText.Y++;
    }
    posText.X=rc.Left+2;
    posText.Y=rc.Top+2;
    WriteConsoleOutputCharacter(hout,s,strlen(s),posText, &a);
    SetConsoleTextAttribute(hout,bInfo.wAttributes);
}


