#include <windows.h>
#include "graphics.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
char szProgName[] = "levi";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG lpMsg;
	WNDCLASS w;

	w.lpszClassName = szProgName;
	w.hInstance = hInstance;
	w.lpfnWndProc = WndProc;
	w.hCursor = LoadCursor(NULL, IDC_ARROW);
	w.hIcon = 0;
	w.lpszMenuName = 0;
	w.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	w.cbClsExtra = 0;
	w.style = CS_HREDRAW | CS_VREDRAW;
	w.cbWndExtra = 0;

	if (!RegisterClass(&w))
		return 0;


	hWnd = CreateWindow(szProgName, "Levi Fractal", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, (HWND)NULL, (HMENU)NULL, (HINSTANCE)hInstance, (HINSTANCE)NULL);

	ShowWindow(hWnd, SW_SHOWMAXIMIZED);
	UpdateWindow(hWnd);

	while (GetMessage(&lpMsg, hWnd, 0, 0)) {
		TranslateMessage(&lpMsg);
		DispatchMessage(&lpMsg);
	}

	return (int)lpMsg.wParam;
}

int click = 0;
int iter = 0;
line_t first_line = { {0,0}, {0,0} };

//Функция окна
LRESULT CALLBACK WndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;

	GetClientRect(hWnd, &rect);
	
	switch (messg)
	{
	case WM_LBUTTONDOWN:
	{
		switch (click)
		{
		case 0:
		{
			first_line.beg.x = LOWORD(lParam);
			first_line.beg.y = HIWORD(lParam);
			click = 1;
			break;
		}
		case 1:
		{
			first_line.end.x = LOWORD(lParam);
			first_line.end.y = HIWORD(lParam);
			click = 2;
			break;
		}
		case 2:
		{
			iter = 0;
			click = 0;
			break;
		}
		}
		InvalidateRect(hWnd, &rect, TRUE);
		UpdateWindow(hWnd);
		break;
	}

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
		{
			if (iter > MIN) iter--;
			InvalidateRect(hWnd, &rect, TRUE);
			UpdateWindow(hWnd);
			break;
		}
		case VK_RIGHT:
		{
			if (iter < MAX) iter++;
			InvalidateRect(hWnd, &rect, TRUE);
			UpdateWindow(hWnd);
			break;
		}
		default:
			break;
		}

	case WM_KEYUP:
		if (wParam == 27) ExitProcess(0);
		break;

	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		if (click == 2) Draw(hdc, iter, first_line);
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return(DefWindowProc(hWnd, messg, wParam, lParam));
	}
	return 0;
}