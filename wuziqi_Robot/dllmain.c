// dllmain.cpp : 定义 DLL 应用程序的入口点。
#pragma once

#include "pch.h"
#include "GameEngine.h"
#include "UnitTest.h"

//global
GameEngine globalEngine;
int globalPlayerColor, globalBlackBanned;

//prototype (also interface)
int _stdcall GetNextMove(int map[225], int move);
void _stdcall Reset();
void _stdcall SetColor(int color);
void _stdcall SetIsBlackBanned(int state);
int _stdcall IsBlackBannedSupported();
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
    
    return 0;
}

void _stdcall Reset()
{
    memset(&globalEngine, 0, sizeof(GameEngine));
}

void _stdcall SetColor(int color)
{
    globalEngine.playerColor = color;
    globalPlayerColor = color;
}

void _stdcall SetIsBlackBanned(int state)
{
    globalEngine.blackBanned = state;
    globalBlackBanned = state;
}

int _stdcall IsBlackBannedSupported()
{
    return 0;
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

    return 0;
}