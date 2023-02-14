#include "main.h"

int SelectedItem;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
	g_hInst = hInst;
	WNDCLASS SoftwareMainClass = NewWindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInst, LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1)), L"MainWindClass", SoftwareMainProcedure);

	if (!RegisterClass(&SoftwareMainClass)) { return -1; }
	MSG SoftwareMainMessege = { 0 };

	hWndMainWindow = CreateWindow(L"MainWindClass", L"Посылатель батонов неактивным окнам 3000", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 700, 300, NULL, NULL, NULL, NULL);
	ShowWindow(hWndMainWindow, SW_SHOW);
	while (GetMessage(&SoftwareMainMessege, NULL, NULL, NULL))
	{
		TranslateMessage(&SoftwareMainMessege);
		DispatchMessageW(&SoftwareMainMessege);
	}

	return 0;
}

WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure)
{
	WNDCLASS NWC = { 0 };

	NWC.hIcon = Icon;
	NWC.hCursor = Cursor;
	NWC.hInstance = hInst;
	NWC.lpszClassName = Name;
	NWC.hbrBackground = BGColor;
	NWC.lpfnWndProc = Procedure;

	return NWC;
}

LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	UINT uNotify;
	TCHAR szBuf[128];
	int wmId = LOWORD(wp);

	switch (msg)
	{
	case WM_COMMAND:
		switch (wmId)
		{
		case ClickButtonRefreshListbox:
			WindowsProcCnt = 0;
			SendMessage(hWndLBParentWndText, LB_RESETCONTENT, NULL, NULL);
			EnumWindows(EnumWndProc, 0);
			break;		

		case ID_LIST1:
			SelectedItem = WindowsProcCnt - 1 - (int)SendMessage(hWndLBParentWndText, LB_GETCURSEL, 0, 0L);
			StringCchPrintf(szBuf, 128 / sizeof(CHAR), L"Num: %d\0", SelectedItem);
			SetWindowText(hWndCurrentWndNum, szBuf);

			StringCchPrintf(szBuf, 128 / sizeof(CHAR), L"Text: %s\0", WindowsProcList[SelectedItem].bufftext);
			SetWindowText(hWndCurrentWndText, szBuf);

			StringCchPrintf(szBuf, 128 / sizeof(CHAR), L"Class: %s\0", WindowsProcList[SelectedItem].buffclass);
			SetWindowText(hWndCurrentWndClass, szBuf);

			StringCchPrintf(szBuf, 128 / sizeof(CHAR), L"HWnd: %d\0", (DWORD)WindowsProcList[SelectedItem].hWnd);
			SetWindowText(hWndCurrentWndHWnd, szBuf);
			break;

		case ClickButtonSendMassage:			
			break;
		}
		break;

	case WM_CREATE:	//вызывается при создании окна		
		srand(1792);
		MainWindAddWidgets(hWnd);
		SetHook(hWnd, NULL, NULL, NULL);
		hTreadMain = CreateThread(NULL, 0, MainThread, 0, 0, NULL);
		break;

	case WM_DESTROY:	//взывается при закрытии окна
		CloseHandle(hTreadMain);
		DelHook(hWnd, NULL, NULL, NULL);
		PostQuitMessage(0);
		break;

	case WM_TIMER:
		break;

	case WM_NOTIFY:
		break;

	default: return DefWindowProc(hWnd, msg, wp, lp);
	}

	return NULL;
}

BOOL CALLBACK EnumWndProc(HWND hWnd, LPARAM lParam)
{
	TCHAR     bufftext[100];
	TCHAR     buffclass[100];

	if (IsWindowVisible(hWnd))
	{
		GetClassName(hWnd, buffclass, 100);
		GetWindowText(hWnd, bufftext, 100);

		if (lstrlen(bufftext) == 0)
		{
			return TRUE;
		}

		WindowsProcCnt++;

		lstrcpyn(WindowsProcList[WindowsProcCnt-1].buffclass, buffclass, 100);
		lstrcpyn(WindowsProcList[WindowsProcCnt-1].bufftext, bufftext, 100);
		WindowsProcList[WindowsProcCnt - 1].hWnd = hWnd;

		SendMessage(hWndLBParentWndText, LB_INSERTSTRING, 0, (LPARAM)bufftext);
	}
	return TRUE;
}

void MainWindAddWidgets(HWND hWnd)
{
	hWndLBParentWndText = CreateWindow(L"listbox", NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL  | LBS_STANDARD | LBS_WANTKEYBOARDINPUT, 350, 10, 300, 200, hWnd, (HMENU)ID_LIST1, g_hInst, NULL);
	CreateWindow(L"static", L"Выбор активного окна", WS_CHILD | WS_VISIBLE, 10, 10, 200, 30, hWnd, (HMENU)ClickButtonRefreshListbox, g_hInst, NULL);
	CreateWindow(L"button", L"Обновить", WS_CHILD | WS_VISIBLE, 10, 40, 80, 30, hWnd, (HMENU)ClickButtonRefreshListbox, g_hInst, NULL);
	hWndCurrentWndNum = CreateWindowA("static", "Num: ", WS_VISIBLE | WS_CHILD, 10, 80, 200, 20, hWnd, NULL, g_hInst, NULL);
	hWndCurrentWndText = CreateWindowA("static", "Text: ", WS_VISIBLE | WS_CHILD, 10, 110, 340, 50, hWnd, NULL, g_hInst, NULL);
	hWndCurrentWndClass = CreateWindowA("static", "Class: ", WS_VISIBLE | WS_CHILD, 10, 165, 340, 50, hWnd, NULL, g_hInst, NULL);
	hWndCurrentWndHWnd = CreateWindowA("static", "Class: ", WS_VISIBLE | WS_CHILD, 10, 200, 340, 50, hWnd, NULL, g_hInst, NULL);

	//CreateWindow(L"button", L"send", WS_CHILD | WS_VISIBLE, 10, 350, 80, 30, hWnd, (HMENU)ClickButtonSendMassage, g_hInst, NULL);

	hWndKeyPressDown = CreateWindowA("static", "Down: ", WS_VISIBLE | WS_CHILD, 10, 220, 100, 50, hWnd, NULL, g_hInst, NULL);
	hWndKeyPressUp = CreateWindowA("static", "Up: ", WS_VISIBLE | WS_CHILD, 150, 220, 100, 50, hWnd, NULL, g_hInst, NULL);

	hWndErrorMassage = CreateWindowA("static", "  ", WS_VISIBLE | WS_CHILD, 300, 220, 100, 50, hWnd, NULL, g_hInst, NULL);
}

DWORD WINAPI MainThread(CONST LPVOID lpParam)
{
	TCHAR szBuf[128];
	TCHAR bKeyPressDown = 0;
	TCHAR bKeyPressUp = 0;
	TCHAR ErrorCode = 0;
	TCHAR FlagSecure = 0;
	
	while (1)
	{
		StringCchPrintf(szBuf, 128 / sizeof(CHAR), L"Down: %d\0", bKeyPressDown);
		SetWindowText(hWndKeyPressDown, szBuf);

		StringCchPrintf(szBuf, 128 / sizeof(CHAR), L"Up: %d\0", KeyPressUp);
		SetWindowText(hWndKeyPressUp, szBuf);

		StringCchPrintf(szBuf, 128 / sizeof(CHAR), L"Error: %d\0", ErrorCode);
		SetWindowText(hWndErrorMassage, szBuf);

		if (KeyPressDown != 0)
		{
			switch (KeyPressDown)
			{
			case 81:

				KeyPress(0x31);
				break;
			case 87:
				KeyPress(0x32);
				break;
			case 69:
				KeyPress(0x33);
				break;
			case 82:
				KeyPress(0x34);
				break;
			case 84:
				KeyPress(0x35);
				break;
			case 89:
				KeyPress(0x36);
				break;
			}
			bKeyPressDown = KeyPressDown;
			KeyPressDown = 0;

			if(ErrorCode==0)
				ErrorCode = GetLastError();
		}
		Sleep(RangedRand(100, 180));
	}
	return NULL;
}

UINT KeyPress(UCHAR Key)
{
	UINT ScanCode;
	LPARAM KeyParam = 0;

	ScanCode = MapVirtualKey(Key, 0);
	PostMessage(WindowsProcList[SelectedItem].hWnd, WM_ACTIVATE, 0, 0);
	KeyParam = ScanCode << 16;
	KeyParam = KeyScanCodeDown << 16;
	KeyParam |= 1;
	PostMessage(WindowsProcList[SelectedItem].hWnd, WM_KEYDOWN, Key, KeyParam);
	Sleep(RangedRand(120, 200));
	KeyParam |= 1 << 30;
	KeyParam |= 1 << 31;
	PostMessage(WindowsProcList[SelectedItem].hWnd, WM_KEYUP, Key, KeyParam);

	return NULL;
}

/*PostMessage(WindowsProcList[SelectedItem].hWnd, WM_ACTIVATE, 0, 0);
SendMessage(WindowsProcList[SelectedItem].hWnd, WM_KEYDOWN, VK_F6, 0x002C0001);
PostMessage(WindowsProcList[SelectedItem].hWnd, WM_KEYDOWN, VK_F6, 0x00020001);
PostMessage(WindowsProcList[SelectedItem].hWnd, WM_KEYDOWN, 0x36, 0x00020001);
Sleep(150);
PostMessage(WindowsProcList[SelectedItem].hWnd, WM_KEYUP, 0x36, 0xC0020001);*/

DWORD RangedRand(DWORD range_min, DWORD range_max)
{
	DWORD r;
	r = ((double)rand() / RAND_MAX) * (range_max - range_min) + range_min;
	return r;
}