#pragma comment(lib,"comctl32")
#include<windows.h>
#include<tchar.h>
#include <time.h>
#include "resource.h"
#include <windowsX.h>
#include <ctime>
#include <commctrl.h>
bool gameover;
void Check_Game_Over(HWND);
void Progres();
HWND hBar;
HINSTANCE hInst;
COORD Point;
HWND gamefield[4][4];
BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	INITCOMMONCONTROLSEX icc = { sizeof(INITCOMMONCONTROLSEX) };
	icc.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&icc);

	srand(unsigned(time(0)));
	hInst = hInstance;
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}
BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	Progres();
	int count = 0;
	switch (message)
	{
	case WM_COMMAND:
		
		for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			if ((HWND)lParam == gamefield[i][j])
			{
				TCHAR buf[4];
				TCHAR buf2[4];
				GetWindowText(gamefield[i][j], buf, 4);
				if (lstrcmp(buf, TEXT(" ")))
				{
					if (j - 1 >= 0)
					{
						GetWindowText(gamefield[i][j-1], buf2, 4);
						if (!lstrcmp(buf2, TEXT(" ")))
						{
							SetWindowText(gamefield[i][j - 1], buf);
							SetWindowText(gamefield[i][j], buf2);

						}
					}
					if (j + 1 <4)
					{
						GetWindowText(gamefield[i][j + 1], buf2, 4);
						if (!lstrcmp(buf2, TEXT(" ")))
						{
							SetWindowText(gamefield[i][j + 1], buf);
							SetWindowText(gamefield[i][j], buf2);

						}
					}
					if (i - 1 >= 0)
					{
						GetWindowText(gamefield[i-1][j], buf2, 4);
						if (!lstrcmp(buf2, TEXT(" ")))
						{
							SetWindowText(gamefield[i-1][j], buf);
							SetWindowText(gamefield[i][j], buf2);

						}
					}
					if (i + 1 < 4)
					{
						GetWindowText(gamefield[i + 1][j], buf2, 4);
						if (!lstrcmp(buf2, TEXT(" ")))
						{
							SetWindowText(gamefield[i + 1][j], buf);
							SetWindowText(gamefield[i][j], buf2);

						}
					}
				}
				
			}
		}
	
		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hWnd, 0);
		}
		if (LOWORD(wParam) == Restart)
		{

		
		
		
			for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				ShowWindow(gamefield[i][j], 4);

			TCHAR buf[4];
			TCHAR buf2[4];
			Point.X = 3;
			Point.Y = 3;
			int action;
			bool complite=0;
			count = 1;
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
				{
				if (count == 16)
				{
					SetWindowText(gamefield[i][j], TEXT(" "));
				}
				else
				{
					_stprintf_s(buf, L"%d", count);
					SetWindowText(gamefield[i][j], buf);
					count++;
				}
				}
			for (int i = 0; i < 500; i++)
			{
				
				action = rand() % 4;

				GetWindowText(gamefield[Point.Y][Point.X], buf, 4);
				while (!complite)
				{

					if (action == 0)
					if (Point.X - 1 >= 0)
					{
						GetWindowText(gamefield[Point.Y][Point.X - 1], buf2, 4);


						SetWindowText(gamefield[Point.Y][Point.X - 1], buf);
						SetWindowText(gamefield[Point.Y][Point.X], buf2);
						Point.X--;


						break;
					}
					else
						action++;
					if (action == 1)
					if (Point.X + 1 < 4)
					{
						GetWindowText(gamefield[Point.Y][Point.X + 1], buf2, 4);

						SetWindowText(gamefield[Point.Y][Point.X + 1], buf);
						SetWindowText(gamefield[Point.Y][Point.X], buf2);
						Point.X++;
						break;

					}
					else
						action++;
					if (action == 2)
					if (Point.Y - 1 >= 0)
					{
						GetWindowText(gamefield[Point.Y - 1][Point.X], buf2, 4);


						SetWindowText(gamefield[Point.Y - 1][Point.X], buf);
						SetWindowText(gamefield[Point.Y][Point.X], buf2);
						Point.Y--;
						break;
					}
					else
						action++;
					if (action == 3)
					if (Point.Y + 1 < 4)
					{
						GetWindowText(gamefield[Point.Y + 1][Point.X], buf2, 4);


						SetWindowText(gamefield[Point.Y + 1][Point.X], buf);
						SetWindowText(gamefield[Point.Y][Point.X], buf2);
						Point.Y++;
						break;

					}
					else
						action=0;
					
				}
				Sleep(5);

			}
			
		}
		Check_Game_Over(hWnd);
		return TRUE;

	case WM_INITDIALOG:
		hBar = GetDlgItem(hWnd,IDC_PROGRESS);
		SendMessage(hBar, PBM_SETRANGE32, 0, 15);
		
		ShowWindow(hWnd, 5);
		count = 1;
		for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			
			TCHAR buf[4];
			if (count == 16)
			{
				wcscpy_s(buf, L" ");
			}
			else
			{
				

				_stprintf_s(buf, L"%d", count);
				
			}
			gamefield[i][j] = CreateWindowEx(
				WS_EX_DLGMODALFRAME, 
				TEXT("BUTTON"),
				buf,
				WS_CHILD | WS_VISIBLE,
				110 + j * 50,
				50 + i * 50,
				50,
				50,
				hWnd,
				0,
				hInst,
				0
				);
			
			count++;
			
		}
		return TRUE;
		
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;
	}
	return FALSE;
}
void Check_Game_Over(HWND hWnd)
{
	bool win=1;
	TCHAR buf[4];
	TCHAR buf2[4];
	GetWindowText(gamefield[0][0], buf, 4);
	for (int i = 0; i < 4; i++)
	{
		if (win)
			for (int j = 0; j < 4; j++)
			{

			if (!(j == i && i == 0)&&!(i==3 && j==3))
			{
				GetWindowText(gamefield[i][j], buf2, 4);
				if (_tstoi(buf2) - 1 != _tstoi(buf))
				{
					win = 0;

				}
				wcscpy_s(buf, buf2);

			}
			}
		else
			break;
	}
	if (win)
	{
		MessageBox(hWnd, TEXT("YOU WON"), TEXT("Congratulations"),MB_OK);
	}
}
void Progres()
{
	int progres=0;
	TCHAR buf[4];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (!(i == 3 && j == 3))
			{
				GetWindowText(gamefield[i][j], buf, 4);
				if (_tstoi(buf) == (i) * 4 + (j+1))
				{
					progres++;
				}
			}
		}
	}
	SendMessage(hBar, PBM_SETPOS, progres, 0);



}