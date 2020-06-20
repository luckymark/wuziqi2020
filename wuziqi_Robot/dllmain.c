// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include "GameEngine.h"
#include "MaxMinSearch.h"
#include "UnitTest.h"

//global
GameEngine globalEngine;

//prototype (also interface)
int _stdcall GetNextMove(int map[225], int move);
void _stdcall Reset();
void _stdcall SetColor(int color);
void _stdcall SetLevel(int level);
int _stdcall UnitTest();


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

//function
int _stdcall GetNextMove(int map[225], int move)
{
    int i, j,result;
    for (i = 0; i < 15; i++)
        for (j = 0; j < 15; j++)
            globalEngine.squareMap.map[i][j] = map[15 * i + j];
    result = getBestMove_MaxMinSearch(globalEngine);
    return result;
}

void _stdcall Reset()
{
    memset(&globalEngine, 0, sizeof(GameEngine));
}

void _stdcall SetColor(int color)
{
    globalEngine.playerColor = color;
}

void _stdcall SetLevel(int level)
{

}

int _stdcall UnitTest()
{
    int counter = 1, tmpErrCode = 0;

    tmpErrCode = testTupleFive();
    if (0 != tmpErrCode)
    { 
        return 10 * counter + tmpErrCode;
    }
    counter++;

    tmpErrCode = testGlobalEvaluation();
    if (0 != tmpErrCode)
    {
        return 10 * counter + tmpErrCode;
    }
    counter++;

    return 0;
}