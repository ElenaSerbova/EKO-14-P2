#include "GameDlg.h"

GameDlg* GameDlg::ptr = NULL;

GameDlg::GameDlg(void)
{
	ptr = this;
}

GameDlg::~GameDlg(void)
{

}

void GameDlg::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}



BOOL GameDlg::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	for (int i = 0; i < 10;i++)
	for (int j = 0; j < 20; j++)
	{
		TCHAR nom[10];
		field[i][j] = new HANDLE;
		_itot_s(game.Get(j, i), nom, 9);
		*field[i][j] = CreateWindowEx(NULL, L"BUTTON",nom, WS_CHILD | WS_VISIBLE | BS_FLAT, j*50, i*50, 50, 50, hwnd, NULL, GetModuleHandle(0), NULL);
	}
	return 0;
}

void GameDlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	TCHAR nom[10];
	for (int i = 0; i < 10; i++)
	for (int j = 0; j < 20; j++)
	{
		if (hwndCtl == *field[i][j])
		{
			game.PointTo(j, i);
		}
	}
	for (int i = 0; i < 10; i++)
	for (int j = 0; j < 20; j++)
	{
		_itot_s(game.Get(j, i), nom, 9);
		SetWindowText((HWND)*field[i][j], nom);
	}
}

BOOL CALLBACK GameDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}