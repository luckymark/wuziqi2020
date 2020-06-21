// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include "check.h"

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

int _stdcall Judge(int map[225]);

int _stdcall Judge(int map[225])
{
    /*
    result:
    0 -> no winner
    1 -> black win
    2 -> white win
    3 -> draw
    */
    
    int result;

    result = isDraw(map);
    if (result)
        return result;

    result = checkHorizental(map);
    if (result)
        return result;
    
    result = checkVertical(map);
    if (result)
        return result;

    result = checkObliqueA(map);
    if (result)
        return result;

    result = checkObliqueB(map);
    if (result)
        return result;

    return 0;
}

