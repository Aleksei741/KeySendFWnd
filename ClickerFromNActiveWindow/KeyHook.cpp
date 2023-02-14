#include <windows.h>
#include <strsafe.h>
#include "KeyHook.h"

MYHOOKDATA myhookdata;

LRESULT WINAPI KeyboardProc(int, WPARAM, LPARAM);

LRESULT WINAPI SetHook(HWND hwndMain, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    int index;
    HINSTANCE hInstance = GetModuleHandle(NULL);

    myhookdata.nType = WH_KEYBOARD_LL;
    myhookdata.hkprc = KeyboardProc;
    
    myhookdata.hhook = SetWindowsHookEx(myhookdata.nType, myhookdata.hkprc, (HINSTANCE)hInstance, NULL/*GetCurrentThreadId()*/);

    return NULL;
}

LRESULT WINAPI DelHook(HWND hwndMain, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    int index;

    UnhookWindowsHookEx(myhookdata.hhook);

    return NULL;
}

/****************************************************************
  WH_KEYBOARD hook procedure
 ****************************************************************/
extern CHAR KeyPressUp;
extern CHAR KeyPressDown;
extern CHAR KeyScanCodeDown;
extern CHAR KeyScanCodeUp;
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    KBDLLHOOKSTRUCT* p = (KBDLLHOOKSTRUCT*)lParam;

    if (nCode < 0)  // do not process message 
        return CallNextHookEx(myhookdata.hhook, nCode, wParam, lParam);

    if (HC_ACTION == nCode)
    {
        switch (wParam)
        {
        case WM_KEYDOWN:
            KeyPressDown = p->vkCode;
            KeyScanCodeDown = p->scanCode;
            break;

        case WM_KEYUP:
            KeyPressUp = p->vkCode;
            KeyScanCodeUp = p->scanCode;
            break;
        }
    }
    
    return CallNextHookEx(myhookdata.hhook, nCode, wParam, lParam);
}
