#include <Windows.h>
#include <vector>
#include <utility>
#include <cstdlib>
#include <ctime>
#define N 30
using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("과제연구");
int x = 0, y = 0;
typedef struct { int x; int y; } coord;
vector<coord> container;

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

void MyKeyboard()
{
	int myMove = 3;
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) for (int i = 0; i < N; i++)container[i].x -= myMove;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) for (int i = 0; i < N; i++)container[i].x += myMove;
	if (GetAsyncKeyState(VK_UP) & 0x8000) for (int i = 0; i < N; i++)container[i].y -= myMove;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) for (int i = 0; i < N; i++)container[i].y += myMove;
	if (GetAsyncKeyState(VK_LEFT) & 0x8001) for (int i = 0; i < N; i++)container[i].x -= myMove;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8001) for (int i = 0; i < N; i++)container[i].x += myMove;
	if (GetAsyncKeyState(VK_UP) & 0x8001) for (int i = 0; i < N; i++)container[i].y -= myMove;
	if (GetAsyncKeyState(VK_DOWN) & 0x8001) for (int i = 0; i < N; i++)container[i].y += myMove;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	int nx, ny;
	int Rsize = 20;
	HDC hdc;
	PAINTSTRUCT ps;
	static RECT rt1, rt2;
	static bool isMouseClicked = false;
	switch (iMessage)
	{
	case WM_CREATE:
		srand(time(NULL));
		for (int i = 0; i < N; i++)
		{
			coord now; now.x = now.y = rand()%300;
			container.push_back(now);
		}
		SetTimer(hWnd, 1, 1, NULL);
		SendMessage(hWnd, WM_TIMER, 1, 0);
		return 0;
	case WM_TIMER:
		hdc = GetDC(hWnd);
		for (int i = 0; i < N; i++)
		{
			nx = rand() % 10 - 5;
			ny = rand() % 10 - 5;
			container[i].x += nx; container[i].y += ny;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		//Repeated Task
		ReleaseDC(hWnd, hdc);
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		for (int i = 0; i < N; i++)
		{
			MoveToEx(hdc, container[i].x, container[i].y, NULL);
			Rectangle(hdc, container[i].x - Rsize, container[i].y - Rsize, container[i].x + Rsize, container[i].y + Rsize);
		}
		EndPaint(hWnd, &ps);
		return 0;
	case WM_KEYDOWN:
		if (isMouseClicked) return 0;
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			for (int i = 0; i < N; i++)
			{
				container[i].x = 1024 / 2;
				container[i].y = 864 / 2;
			}
			InvalidateRect(hWnd, NULL, TRUE);
			//MessageBox(hWnd, TEXT("Ini!"), TEXT("백교풍비둘기"), MB_OK);
			ShowWindow(hWnd, SW_SHOWMAXIMIZED);
			return 0;
		}
		//rt1 = { x - 50, y - 50, x + 50, y + 50 };
		MyKeyboard();
		//rt2 = { x - 50, y - 50, x + 50, y + 50 };
		InvalidateRect(hWnd, NULL, TRUE);
		//InvalidateRect(hWnd, &rt1, TRUE);
		//InvalidateRect(hWnd, &rt2, TRUE);
		return 0;
	case WM_LBUTTONDOWN:
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		for (int i = 0; i < N; i++)
		{
			container[i].x = x;
			container[i].y = y;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		isMouseClicked = true;
		return 0;
	case WM_MOUSEMOVE:
		if (isMouseClicked)
		{
			x = LOWORD(lParam);
			y = HIWORD(lParam);
			for (int i = 0; i < N; i++)
			{
				container[i].x = x;
				container[i].y = y;
			}
			InvalidateRect(hWnd, NULL, TRUE);
		}
		return 0;
	case WM_LBUTTONUP:
		isMouseClicked = false;
		return 0;
	case WM_DESTROY:
		//MessageBox(hWnd, TEXT("종료하시겠습니까?"), TEXT("백교풍비둘기"), MB_OK);
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

