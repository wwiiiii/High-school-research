#include <Windows.h>
#include <vector>
#include <utility>
#include <cstdlib>
#include <ctime>
#include "Road.h"
#include "RobotClass.h"
#include "InitAndDisplay.h"
#include "Repeat.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("GSSH TEAM PROJECT");
std::vector<cRobot> RobotContainer;
cRoad mainRoad;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_CROSS);
	WndClass.hIcon = LoadIcon(NULL, IDI_ASTERISK);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass,
		lpszClass,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL);
	ShowWindow(hWnd, SW_SHOWMAXIMIZED);

	while (GetMessage(&Message, NULL, 0, 0)){
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	int nx, ny, MAXx = 0, MAXy = 0, Rsize = 20;
	PAINTSTRUCT ps;	cRobot tt;
	RECT rect; HDC hdc, hdcMem, hdcBm;
	HBITMAP hbmOld, hbmMem, hbmMemOld;
	switch (iMessage)
	{
	case WM_CREATE:
		srand(time(NULL));
		Initi(hWnd,mainRoad, RobotContainer);
		mainRoad.PassiveID = 1; mainRoad.scalex = mainRoad.scaley = 1.0;
		SetTimer(hWnd, 1, 1, NULL);
		InvalidateRect(hWnd, NULL, true);
		SendMessage(hWnd, WM_PAINT, 1, 0);
		//SendMessage(hWnd, WM_TIMER, 1, 0);
		return 0;
	case WM_TIMER:
		hdc = GetDC(hWnd);
		RepeatedTask(mainRoad,RobotContainer);
		ShowWindow(hWnd, SW_SHOWMAXIMIZED);
		InvalidateRect(hWnd, NULL, false);
		//SendMessage(hWnd, WM_PAINT, 1, 0);
		ReleaseDC(hWnd, hdc);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rect);
		hdcMem = CreateCompatibleDC(hdc);//2
		hbmMem = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);//3
		hbmMemOld = (HBITMAP)SelectObject(hdcMem, hbmMem);//4
		Display(hWnd,hdcMem,ps,RobotContainer,mainRoad);
		BitBlt(hdc, 0, 0, rect.right, rect.bottom, hdcMem, 0, 0, SRCCOPY);
		SelectObject(hdcMem, hbmMemOld); //-4
		DeleteObject(hbmMem); //-3
		DeleteDC(hdcMem); //-2
		EndPaint(hWnd, &ps);
		return 0;
	case WM_LBUTTONDOWN:
		return 0;
	case WM_KEYDOWN:
		if (GetAsyncKeyState(VK_TAB) & 0x8000)
		{
			++mainRoad.PassiveID;
			mainRoad.PassiveID %= RobotContainer.size();
		}
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			RobotContainer[mainRoad.PassiveID].NowCoord.x -= 10;
			//RobotContainer[mainRoad.PassiveID].fRenewForce(-1000, 0);
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			RobotContainer[mainRoad.PassiveID].NowCoord.x += 10;
			//RobotContainer[mainRoad.PassiveID].fRenewForce(1000, 0);
		}
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			RobotContainer[mainRoad.PassiveID].NowCoord.y -= 10;
			//RobotContainer[mainRoad.PassiveID].fRenewForce(0,-1000);
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			RobotContainer[mainRoad.PassiveID].NowCoord.y += 10;
			//RobotContainer[mainRoad.PassiveID].fRenewForce(0,1000);
		}
		if (GetAsyncKeyState(VK_PRIOR) & 0x8000)
		{
			mainRoad.scalex /= 1.1; mainRoad.scaley /= 1.1;
		}
		if (GetAsyncKeyState(VK_NEXT) & 0x8000)
		{
			mainRoad.scalex *= 1.1; mainRoad.scaley *= 1.1;
		}
		InvalidateRect(hWnd, NULL, FALSE);
		//InvalidateRect(hWnd, &rt1, TRUE);
		//InvalidateRect(hWnd, &rt2, TRUE);
		return 0;
	case WM_DESTROY:
		MessageBox(hWnd, TEXT("Exit?"), TEXT("Kev is Chicken!"), MB_OK);
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

