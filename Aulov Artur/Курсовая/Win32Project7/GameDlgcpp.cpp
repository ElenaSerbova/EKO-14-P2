#include "GameDlg.h"
#pragma once
GameDlg* GameDlg::ptr = NULL;

GameDlg::GameDlg(bool cgame)
{
	this->cgame = cgame;
	ptr = this;
	if (cgame == false)
	{
		hp = 10;
		level = 0;
		coins = 0;
		score = 0;
		anim = 0;
		orders = 0;
	}
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
	HP = GetDlgItem(hwnd, IDC_STATIC_HP);
	TCHAR tmpbuf[10];
	_itot_s(hp, tmpbuf, 10);
	SetWindowText(HP, tmpbuf);

	build_on = CreateWindow(L"STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_BITMAP, 540, 20, 300, 220, hwnd, NULL, GetModuleHandle(NULL), NULL);
	GetClientRect(hwnd, &cd);
	phase = 0;
	ptr->trig = 0;

	ptr->build[0][0] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP10));
	ptr->build[0][1] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP11));
	ptr->build[0][2] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP12));
	ptr->build[0][3] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP13));
	ptr->build[0][4] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP13));

	ptr->icons[0] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP2));
	ptr->icons[1] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP3));
	ptr->icons[2] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP4));
	ptr->icons[3] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP5));
	ptr->icons[4] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP6));
	ptr->icons[5] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP7));
	ptr->icons[6] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP8));

	for (int i = 0; i < 11; i++)
	for (int j = 0; j < 10; j++)
	{
		TCHAR nom[10];
		field[i][j] = new HANDLE;
		*field[i][j] = CreateWindowEx(NULL, L"BUTTON",nom, WS_CHILD | WS_VISIBLE | BS_FLAT, 20+j*50, 20+i*50, 50, 50, hwnd, NULL, GetModuleHandle(0), NULL);
		SetWindowLong((HWND)*field[i][j], GWL_STYLE, ::GetWindowLong((HWND)*field[i][j], GWL_STYLE) | BS_BITMAP | BS_FLAT);
	}

	SendMessage(build_on, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)ptr->build[level][anim]);

	for (int i = 0; i < 11; i++)
		for (int j = 0; j < 10; j++)
		{
		SendMessage((HWND)*field[i][j], BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)ptr->icons[game.Get(i, j)]);
		}
	return 0;
}

void GameDlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if (id == IDC_BUTTON1)
	{
		hp = hp - game.count_stone();
		game.stone_on();
		TCHAR tmpbuf[10];
		_itot_s(hp, tmpbuf, 10);
		SetWindowText(HP, tmpbuf);
		game.generatefield();
	}
	if (phase == 0)
	{
		TCHAR nom[10];
		for (int i = 0; i < 11; i++)
			for (int j = 0; j < 10; j++)
			{
			if (hwndCtl == *field[i][j])
			{
				game.Click(i, j);

				if (game.getss())
				{
					if (game.isswap())
					{
						game.swap();
						phase++;
						SetTimer(hwnd, NULL, 100, NULL);
					}
					else
					{
						game.unselect();
						game.setbs(i, j);
					}
				}
			}
			}
	}
	for (int i = 0; i < 11; i++)
	for (int j = 0; j < 10; j++)
	{
		SendMessage((HWND)*field[i][j], BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)ptr->icons[game.Get(i,j)]);
	}


	SendMessage(build_on, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)ptr->build[level][anim]);
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
	case WM_TIMER:
		switch (ptr->phase)
		{
			case 1:
				ptr->game.ClearSelect();
				if (ptr->game.select3match())
				{
					while (ptr->game.select3match())
					{
						ptr->game.delete3match();

						for (int j = 0; j < 10; j++)
							ptr->game.FallColone(j);

						ptr->game.unselect();
					}
				}
				else
				{
					ptr->game.swap();
					ptr->game.unselect();
					ptr->phase = 0;
					KillTimer(hwnd,NULL);
					for (int i = 0; i < 11; i++)
						for (int j = 0; j < 10; j++)
						{
						SendMessage((HWND)*ptr->field[i][j], BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)ptr->icons[ptr->game.Get(i, j)]);
						}
					break;
				}
				ptr->phase = 0;
				KillTimer(hwnd, NULL);
				for (int i = 0; i < 11; i++)
					for (int j = 0; j < 10; j++)
					{
					SendMessage((HWND)*ptr->field[i][j], BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)ptr->icons[ptr->game.Get(i, j)]);
					}
		}

		break;
	
		return 0;
	}
	return FALSE;
}