#pragma once
#include <Windows.h>
#include <windowsx.h>
#include <strsafe.h>

#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")

#include "resource.h"
#include "KeyHook.h"

// Enable Visual Style
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
//----------------------------------------------------------------------------------------------------
#define KEY_1 0x1e // Keyboard 1 and !
#define KEY_2 0x1f // Keyboard 2 and @
#define KEY_3 0x20 // Keyboard 3 and #
#define KEY_4 0x21 // Keyboard 4 and $
#define KEY_5 0x22 // Keyboard 5 and %
#define KEY_6 0x23 // Keyboard 6 and ^
#define KEY_7 0x24 // Keyboard 7 and &
#define KEY_8 0x25 // Keyboard 8 and *
#define KEY_9 0x26 // Keyboard 9 and (
#define KEY_0 0x27 // Keyboard 0 and )
#define KEY_MINUS 0x2d // Keyboard - and _
#define KEY_EQUAL 0x2e // Keyboard = and +

#define KEY_F1 0x3a // Keyboard F1
#define KEY_F2 0x3b // Keyboard F2
#define KEY_F3 0x3c // Keyboard F3
#define KEY_F4 0x3d // Keyboard F4
#define KEY_F5 0x3e // Keyboard F5
#define KEY_F6 0x3f // Keyboard F6
#define KEY_F7 0x40 // Keyboard F7
#define KEY_F8 0x41 // Keyboard F8
#define KEY_F9 0x42 // Keyboard F9
#define KEY_F10 0x43 // Keyboard F10
#define KEY_F11 0x44 // Keyboard F11
#define KEY_F12 0x45 // Keyboard F12

#define KEY_L1 0x59 // Keyboard L 1
#define KEY_L2 0x5a // Keyboard L 2
#define KEY_L3 0x5b // Keyboard L 3
#define KEY_L4 0x5c // Keyboard L 4
#define KEY_L5 0x5d // Keyboard L 5
#define KEY_L6 0x5e // Keyboard L 6
#define KEY_L7 0x5f // Keyboard L 7
#define KEY_L8 0x60 // Keyboard L 8
#define KEY_L9 0x61 // Keyboard L 9
#define KEY_L0 0x62 // Keyboard L 0
//----------------------------------------------------------------------------------------------------
struct WindowsProcList_DType
{
	TCHAR     bufftext[100];
	TCHAR     buffclass[100];
	HWND	  hWnd;
};

struct ParametersKey_typedef
{
	UINT	pressKey[10];
	UINT	sendKey[10];
};
//----------------------------------------------------------------------------------------------------
//MainWindow указатели
HINSTANCE g_hInst;
HWND hWndMainWindow;

//Интерфейс
HWND hWndLBParentWndText;
HWND hWndCurrentWndText;
HWND hWndCurrentWndClass;
HWND hWndCurrentWndNum;
HWND hWndCurrentWndHWnd;

HWND hWndKeyEmulation;
HWND hWndErrorMassage;
HWND hWndKeyPressDown;

//Работа
WindowsProcList_DType WindowsProcList[40];
DWORD WindowsProcCnt = 0;
HANDLE hTreadMain;

CHAR KeyPressUp;
CHAR KeyPressDown;
CHAR KeyScanCodeDown;
CHAR KeyScanCodeUp;
struct ParametersKey_typedef ParametersKey = { 0 };
//----------------------------------------------------------------------------------------------------
enum
{
	ID_LIST1,

	ClickButtonRefreshListbox,
	ClickButtonSendMassage,
};
//----------------------------------------------------------------------------------------------------
WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure);
LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
BOOL CALLBACK EnumWndProc(HWND hWnd, LPARAM lParam);
void MainWindAddWidgets(HWND hWnd);
DWORD WINAPI MainThread(CONST LPVOID lpParam);
DWORD RangedRand(DWORD range_min, DWORD range_max);
UINT KeyPress(UCHAR Key);
DWORD ReadParamFile(void);
DWORD WriteParamFile(void);
//----------------------------------------------------------------------------------------------------
