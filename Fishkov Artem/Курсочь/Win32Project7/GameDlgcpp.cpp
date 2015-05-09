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
	ptr->trig = 0;
	ptr->Back = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP1));
	HeroIconSpace = CreateWindow(L"STATIC", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP,10,520, 275, 353,hwnd, NULL, GetModuleHandle(0),NULL);
	MonstrIconSpace = CreateWindow(L"STATIC", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 820, 520, 275, 353, hwnd, NULL, GetModuleHandle(0), NULL);
	ptr->Hero = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP8));
	ptr->Monstr = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP8));
	ptr->icons[0] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP2));
	ptr->icons[1] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP3));
	ptr->icons[2] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP4));
	ptr->icons[3] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP5));
	ptr->icons[4] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP6));
	ptr->icons[5] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP7));
	for (int i = 0; i < 10;i++)
	for (int j = 0; j < 20; j++)
	{
		TCHAR nom[10];
		field[i][j] = new HANDLE;
		_itot_s(game.Get(j, i), nom, 9);
		*field[i][j] = CreateWindowEx(NULL, L"BUTTON",nom, WS_CHILD | WS_VISIBLE | BS_FLAT, 50+j*50, 15+i*50, 50, 50, hwnd, NULL, GetModuleHandle(0), NULL);
		SetWindowLong((HWND)*field[i][j], GWL_STYLE, ::GetWindowLong((HWND)*field[i][j], GWL_STYLE) | BS_BITMAP | BS_FLAT);
	}
	SendMessage((HWND)HeroIconSpace, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)Hero);
	SendMessage((HWND)MonstrIconSpace, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)Monstr); 

	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 20; j++)
		{

		SendMessage((HWND)*field[i][j], BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)ptr->icons[game.Get(j, i)]);

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
		
		SendMessage((HWND)*field[i][j], BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)ptr->icons[game.Get(j,i)]);

	}
}

BOOL CALLBACK GameDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	case WM_PAINT:
		HDC hdc, hmdc;
		PAINTSTRUCT ps;
		BITMAP bm;
		hdc = GetDC(hwnd);
		hmdc = CreateCompatibleDC(hdc); //Создаёт совместимый с оконным контекст памяти
		SelectObject(hmdc, ptr->Back); //Выбирает объект картинку
		GetObject(ptr->Back, sizeof(bm), (LPSTR)&bm); //получаем высоту и ширину картинки 
		BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, hmdc, 0, 0, SRCCOPY); //Помещает картинку на экран в точку 10, 10
		//из памяти (hmdc) 
		DeleteDC(hmdc); //удаляем из памяти контекст
		//Конец рисования картинки

		DeleteDC(hdc);

		return 0;

	}
	return FALSE;
}