// dllmain.cpp : 定义 DLL 应用程序的入口点。
#pragma once
#include <string.h>
#include <stdio.h>
#include "pch.h"
#include "GameEngine.h"
#include "UnitTest.h"
#define DllExport   __declspec( dllexport )

//global
GameEngine globalEngine;
int globalPlayerColor, globalBlackBanned;

//prototype (also interface)
DllExport int _stdcall GetNextMove(int map[225], int move);
DllExport void _stdcall Reset();
DllExport void _stdcall SetColor(int color);
DllExport void _stdcall SetIsBlackBanned(int state);
DllExport int _stdcall IsBlackBannedSupported();
DllExport int _stdcall UnitTest();


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
DllExport int _stdcall GetNextMove(int map[225], int move)
{
    
    return 0;
}

DllExport void _stdcall Reset()
{
    memset(&globalEngine, 0, sizeof(GameEngine));
}

DllExport void _stdcall SetColor(int color)
{
    globalEngine.playerColor = color;
    globalPlayerColor = color;
}

DllExport void _stdcall SetIsBlackBanned(int state)
{
    globalEngine.blackBanned = state;
    globalBlackBanned = state;
}

DllExport int _stdcall IsBlackBannedSupported()
{
    return 0;
}

DllExport int _stdcall UnitTest()
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