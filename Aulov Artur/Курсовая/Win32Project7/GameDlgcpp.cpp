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
	LEVEL = GetDlgItem(hwnd, IDC_STATIC_LEVEL);
	COINS = GetDlgItem(hwnd, IDC_STATIC_COINS2);
	SCORE = GetDlgItem(hwnd, IDC_STATIC_SCORE);
	TCHAR tmpbuf[10];
	_itot_s(hp, tmpbuf, 10);
	SetWindowText(HP, tmpbuf);
	_itot_s(level + 1, tmpbuf, 10);
	SetWindowText(LEVEL, tmpbuf);
	_itot_s(coins, tmpbuf, 10);
	SetWindowText(COINS, tmpbuf);
	_itot_s(score, tmpbuf, 10);
	SetWindowText(SCORE, tmpbuf);

	build_on = CreateWindow(L"STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_BITMAP, 540, 120, 300, 220, hwnd, NULL, GetModuleHandle(NULL), NULL);
	GetClientRect(hwnd, &cd);
	phase = 0;
	ptr->trig = 0;

	ptr->catapult_b[0] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP19));
	ptr->catapult_b[1] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP20));
	ptr->catapult_b[2] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP21));
	ptr->catapult_b[3] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP22));

	ptr->build[0][0] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP10));
	ptr->build[0][1] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP11));
	ptr->build[0][2] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP12));
	ptr->build[0][3] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP13));
	ptr->build[0][4] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP13));

	ptr->build[1][0] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP14));
	ptr->build[1][1] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP15));
	ptr->build[1][2] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP16));
	ptr->build[1][3] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP17));
	ptr->build[1][4] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP18));
	
	ptr->build[2][0] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP23));
	ptr->build[2][1] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP24));
	ptr->build[2][2] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP25));
	ptr->build[2][3] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP26));
	ptr->build[2][4] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP27));

	ptr->icons[0] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP2));
	ptr->icons[1] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP28));
	ptr->icons[2] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP29));
	ptr->icons[3] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP30));
	ptr->icons[4] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP31));
	ptr->icons[5] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP32));
	ptr->icons[6] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP8));

	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			TCHAR nom[10];
			field[i][j] = new HANDLE;
			*field[i][j] = CreateWindowEx(NULL, L"BUTTON", nom, WS_CHILD | WS_VISIBLE | BS_FLAT, 20 + j * 50, 20 + i * 50, 50, 50, hwnd, NULL, GetModuleHandle(0), NULL);
			SetWindowLong((HWND)*field[i][j], GWL_STYLE, ::GetWindowLong((HWND)*field[i][j], GWL_STYLE) | BS_BITMAP | BS_FLAT);
			SendMessage((HWND)*field[i][j], BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)ptr->icons[game.Get(i, j)]);
		}
	}

	for (int j = 0; j < 10; j++)
	{
		TCHAR nom[10];
		catapult[j] = new HANDLE;
		*catapult[j] = CreateWindow(L"STATIC", nom, WS_CHILD | WS_VISIBLE | SS_BITMAP, 20 + j * 50, 570, 50, 50, hwnd, NULL, GetModuleHandle(NULL), NULL);
		SendMessage((HWND)*catapult[j], STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)ptr->catapult_b[0]);
	}

	SendMessage(build_on, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)ptr->build[level][anim]);

	//TOOLINFO ti;
	//HINSTANCE hinst = GetModuleHandle(NULL);
	//HWND hTooltip = CreateWindow(TOOLTIPS_CLASS, NULL, TTS_NOPREFIX | TTS_ALWAYSTIP, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,hwnd, (HMENU)NULL, hinst, NULL);
	//// Прикрепить подсказку к кнопке
	//memset(&ti, 0, sizeof TOOLINFO);
	//ti.cbSize = sizeof TOOLINFO;
	//ti.uFlags = TTF_IDISHWND | TTF_SUBCLASS;
	//ti.uId = (UINT)GetDlgItem(hwnd, IDC_BUTTON1);;
	//ti.lpszText = L"Это подсказка Гагага!";
	//ti.hinst = hinst;
	//SendMessage(hTooltip, TTM_ADDTOOL, 0, (LPARAM)(LPTOOLINFO)&ti);

	return 0;
}

void GameDlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if (id == IDC_DESTROY)
	{
		clearbonus();
		block = true;
	}
	if (id == IDC_DESTROYI)	
	{
		clearbonus();
		blocki = true;
	}
	if (id == IDC_DESTROYJ) 	
	{
		clearbonus();
		blockj = true;
	}
	if (id == IDC_BUTTON1)
	{
		hp = hp - game.count_stone();
		
		if (hp > 0)
		{
			game.stone_on();

			for (int j = 0; j < 10; j++)
			{
				if (game.Get(10, j) == 0)
				{
					SendMessage((HWND)*ptr->catapult[j], STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)ptr->catapult_b[3]);
					Sleep(100);
					SendMessage((HWND)*ptr->catapult[j], STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)ptr->catapult_b[0]);
				}
				else
				{
					SendMessage((HWND)*ptr->catapult[j], STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)ptr->catapult_b[2]);
					Sleep(100);
					SendMessage((HWND)*ptr->catapult[j], STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)ptr->catapult_b[0]);
				}
			}

			game.generatefield();

			if (level == 0)
			{
				if (hp == 6) anim = 1;
				if (hp == 4) anim = 2;
				if (hp == 2) anim = 3;
			}
			if (level == 1)
			{
				if (hp == 12) anim = 1;
				if (hp == 9) anim = 2;
				if (hp == 6) anim = 3;
				if (hp == 3) anim = 4;
			}

			if (level == 2)
			{
				if (hp == 16) anim = 1;
				if (hp == 12) anim = 2;
				if (hp == 7) anim = 3;
				if (hp == 3) anim = 4;
			}

			if (hp < 0) hp = 0;

		}
		else
		{
			game.generatefield();

			for (int j = 0; j < 10; j++)
			{
				SendMessage((HWND)*ptr->catapult[j], STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)ptr->catapult_b[0]);
			}

			anim = 0;
			level++;

			if (level == 1) hp = 15;
			if (level == 2) hp = 20;
			if (level > 2)
			{
				level = 0;
				hp = 10;
			}
		}
	}

	if (!block && !blocki && !blockj)
	{
		if (phase == 0)
		{
			TCHAR nom[10];
			for (int i = 0; i < 11; i++)
			{
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
		}
	}
	else
	{
		for (int i = 0; i < 11; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (hwndCtl == *field[i][j] && block)
				{
					game.ClearSelect();
					game.destroy(i, j);
					game.delete3match();
					clearbonus();
				}
				if (hwndCtl == *field[i][j] && blocki)
				{
					game.ClearSelect();
					game.destroyi(j);
					game.delete3match();
					clearbonus();
				}
				if (hwndCtl == *field[i][j] && blockj)
				{
					game.ClearSelect();
					game.destroyj(i);
					game.delete3match();
					clearbonus();
				}
			}
		}
		for (int j = 0; j < 10; j++)
		{
			game.FallColone(j);
			if (game.Get(10, j) == 6)
			{
				game.Set(10, j, 0);
				SendMessage((HWND)*catapult[j], STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)catapult_b[1]);
			}
		}
		while (game.select3match())
		{
			game.delete3match();

			for (int j = 0; j < 10; j++)
			{
				game.FallColone(j);
				if (game.Get(10, j) == 6)
				{
					game.Set(10, j, 0);
					SendMessage((HWND)*catapult[j], STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)catapult_b[1]);
				}
			}
		}
	}

	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			SendMessage((HWND)*field[i][j], BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)ptr->icons[game.Get(i, j)]);
		}
	}
	score = game.score_();
	TCHAR tmpbuf[10];
	_itot_s(hp, tmpbuf, 10);
	SetWindowText(HP, tmpbuf);
	_itot_s(level + 1, tmpbuf, 10);
	SetWindowText(LEVEL, tmpbuf);
	_itot_s(coins, tmpbuf, 10);
	SetWindowText(COINS, tmpbuf);
	_itot_s(score, tmpbuf, 10);
	SetWindowText(SCORE, tmpbuf);

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
						{
							ptr->game.FallColone(j);
							if (ptr->game.Get(10, j) == 6)
							{
								ptr->game.Set(10, j, 0);
								SendMessage((HWND)*ptr->catapult[j], STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)ptr->catapult_b[1]);
							}
						}

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
				ptr->score = ptr->game.score_();
				TCHAR tmpbuf[10];
				_itot_s(ptr->score, tmpbuf, 10);
				SetWindowText(ptr->SCORE, tmpbuf);
		}
		break;
		return 0;
	}
	return FALSE;
}