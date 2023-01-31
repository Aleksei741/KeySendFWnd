#pragma once

typedef struct _MYHOOKDATA
{
    int nType;
    HOOKPROC hkprc;
    HHOOK hhook;
} MYHOOKDATA;



LRESULT WINAPI SetHook(HWND hwndMain, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI DelHook(HWND hwndMain, UINT uMsg, WPARAM wParam, LPARAM lParam);