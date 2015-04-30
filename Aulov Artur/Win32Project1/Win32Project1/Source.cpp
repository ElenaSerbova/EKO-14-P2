
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#define width 416
#define height 438

//char szText1[]="Клетка занята";
bool Field[20][20];
int FieldCheck[20][20];
bool firstClick = true;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

BOOL Line(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL); //сделать текущими координаты x1, y1
	return LineTo(hdc, x2, y2);
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX windowClass;
	HWND hWnd;
	MSG uMsg;

	memset(&windowClass, 0, sizeof(WNDCLASSEX));
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	windowClass.hInstance = hInstance;
	windowClass.lpfnWndProc = WindowProc;
	windowClass.lpszClassName = L"5InARow";

	RegisterClassEx(&windowClass);

	hWnd = CreateWindow(windowClass.lpszClassName, L"5InARow",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		(GetSystemMetrics(SM_CXSCREEN) - width) / 2, (GetSystemMetrics(SM_CYSCREEN) - height) / 2,
		width, height, NULL, NULL, NULL, NULL);

	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&uMsg, hWnd, NULL, NULL))
	{
		TranslateMessage(&uMsg);
		DispatchMessage(&uMsg);
	}

	return uMsg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
	PAINTSTRUCT ps;
	HDC hdc = GetDC(hWnd);
	RECT r;
	int f = 20;
	int x, y; //координаты
	switch (uMsg)
	{
	case WM_CLOSE:
		ExitProcess(0);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		for (int j = 0; j < 400; j += 20)
		{
			for (int i = 0; i < 400; i += 20)
			{
				Rectangle(hdc, j, i, f + j, f + i);
			}
		}
	case WM_LBUTTONDOWN:

		if (!firstClick)
		{
			//char *str;
			HDC hDC;
			//Field[0][0] = true;
			hDC = GetDC(hWnd);
			x = LOWORD(lParam); //узнаём координаты
			y = HIWORD(lParam);

			/*_itoa(x, szText, 10);
			TextOut(hDC, x, y, szText, strlen(szText));
			_itoa(y, szText, 10);
			TextOut(hDC, x, y+20, szText, strlen(szText));
			_itoa(Field[x/20][y/20],szText, 10);
			TextOut(hDC, x, y+40, szText, strlen(szText));*/
			if (Field[x / 20][y / 20] == false)
			{
				Field[x / 20][y / 20] = true;
				for (int i = 0; i < 20; i++)
				{
					for (int j = 0; j < 20; j++)
					{
						if (Field[i][j])
						{
							Line(hDC, i * 20 + 2, j * 20 + 2, i * 20 + 18, j * 20 + 18);
							Line(hDC, i * 20 + 18, j * 20 + 2, i * 20 + 2, j * 20 + 18);
						}
					}
				}
			}
		}
		else firstClick = false;
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

}