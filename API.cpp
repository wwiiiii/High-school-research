#include <Windows.h>
#include <vector>
#include <utility>
#include <cstdlib>
#include <ctime>
#include "Road.h"
#include "RobotClass.h"
#include "InitAndDisplay.h"
#include "Repeat.h"
#define N 30

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
	int nx, ny; mainRoad.scalex = mainRoad.scaley = 1;
	int Rsize = 20;
	HDC hdc;
	PAINTSTRUCT ps;
	static RECT rDisplay;///rDisplay :: zoomed scene area
	static bool isMouseClicked = false;
	switch (iMessage)
	{
	case WM_CREATE:
		srand(time(NULL));
		//Initi(hWnd,mainRoad, RobotContainer);
		SetTimer(hWnd, 1, 1, NULL);
		InvalidateRect(hWnd, NULL, true);
		SendMessage(hWnd, WM_PAINT, 1, 0);
		SendMessage(hWnd, WM_TIMER, 1, 0);
		return 0;
	case WM_TIMER:
		hdc = GetDC(hWnd);
		//RepeatedTask(mainRoad,RobotContainer);
		InvalidateRect(hWnd, NULL, true);
		//SendMessage(hWnd, WM_PAINT, 1, 0);
		ReleaseDC(hWnd, hdc);
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		Display(hWnd,hdc,ps,RobotContainer,mainRoad);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_KEYDOWN:
		if (isMouseClicked) return 0;
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			InvalidateRect(hWnd, NULL, TRUE);
			//MessageBox(hWnd, TEXT("Ini!"), TEXT("백교풍비둘기"), MB_OK);
			ShowWindow(hWnd, SW_SHOWMAXIMIZED);
			return 0;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		//InvalidateRect(hWnd, &rt1, TRUE);
		//InvalidateRect(hWnd, &rt2, TRUE);
		return 0;
	case WM_DESTROY:
		//MessageBox(hWnd, TEXT("종료하시겠습니까?"), TEXT("백교풍비둘기"), MB_OK);
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

