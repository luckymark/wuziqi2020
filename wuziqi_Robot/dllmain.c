// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include <string.h>
#include <stdio.h>
#include "pch.h"
#include "GameEngine.h"

//global
GameEngine engine;

//prototype (also interface)
int _stdcall GetNextMove(int map[225], int move);
void _stdcall Reset();
void _stdcall SetColor(int color);
void _stdcall SetIsBlackBanned(int state);

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

int _stdcall GetNextMove(int map[225], int move)
{
    return 0;
}

void _stdcall Reset()
{
    memset(&engine, 0, sizeof(GameEngine));
}

void _stdcall SetColor(int color)
{
    engine.aiPlayerColor = color;
}

void _stdcall SetIsBlackBanned(int state)
{
    engine.blackBanned = state;
}