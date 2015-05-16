#include "GameDlg.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
DWORD WINAPI PlayEffect(PVOID lpParam)
{
	PlaySound(MAKEINTRESOURCE(IDR_WAVE1), GetModuleHandle(NULL), SND_RESOURCE);
	return 0;
}

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

void GameDlg::UpdateAll()
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 20; j++)
		{

		SendMessage((HWND)*field[i][j], BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)ptr->icons[game.Get(j, i)]);

		}

	ptr->HeroInfo.SetHP(ptr->game.hero.hp);
	ptr->HeroInfo.SetSH(ptr->game.hero.defence, ptr->game.hero.shildcurtime, ptr->game.hero.shildtime);
	ptr->HeroInfo.SetEN(ptr->game.hero.concentration);
	ptr->HeroInfo.SetNAME(ptr->game.hero.name);
	ptr->HeroInfo.SetDMG(ptr->game.hero.TakenDMG);
	if (game.hero.Heal)
	ptr->HeroInfo.SetHEAL(ptr->game.hero.Heal);

	ptr->MonstrInfo.SetHP(ptr->game.monstr.hp);
	ptr->MonstrInfo.SetSH(ptr->game.monstr.defence);
	ptr->MonstrInfo.SetTIMER(ptr->game.monstr.curentTime, ptr->game.monstr.timeng);
	ptr->MonstrInfo.SetNAME(ptr->game.monstr.name);
	ptr->MonstrInfo.SetATTAK(ptr->game.monstr.attack);
	ptr->MonstrInfo.SetDMG(ptr->game.monstr.TakenDMG);
	if (game.monstr.Heal)
	ptr->MonstrInfo.SetHEAL(ptr->game.monstr.Heal);
	if (game.monstr.Heal)
	{
		ShowWindow(ptr->MonstrInfo.HEAL, SW_SHOW);
		SetTimer(ptr->hwnd, NULL, 2000, NULL);
		SendMessage((HWND)MonstrIconSpace, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)ptr->game.monstr.pic[0]);
	}
	else
		ShowWindow(ptr->MonstrInfo.HEAL, SW_HIDE);

	if (game.hero.Heal)
	{
		SendMessage((HWND)HeroIconSpace, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)ptr->ptr->game.hero.pic[0]);
		ShowWindow(ptr->HeroInfo.HEAL, SW_SHOW);
		SetTimer(ptr->hwnd, NULL, 2000, NULL);
	}
	else
		ShowWindow(ptr->HeroInfo.HEAL, SW_HIDE);


	if (game.monstr.attacket != 0)
	{
		ShowWindow(ptr->MonstrInfo.DMG, SW_SHOW);
		SetTimer(ptr->hwnd, NULL, 20, NULL);
		SendMessage((HWND)MonstrIconSpace, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)ptr->game.monstr.pic[2]);
		SendMessage((HWND)HeroIconSpace, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)ptr->ptr->game.hero.pic[1]);
		CreateThread(NULL, 0,PlayEffect, NULL, 0, NULL);
	}

	if (game.hero.attacket != 0)
	{

		ShowWindow(ptr->HeroInfo.DMG, SW_SHOW);
		SetTimer(ptr->hwnd, NULL, 2000, NULL);
		SendMessage((HWND)MonstrIconSpace, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)game.monstr.pic[1]);
		SendMessage((HWND)HeroIconSpace, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)ptr->ptr->game.hero.pic[2]);
	}
	else
		ShowWindow(ptr->HeroInfo.DMG, SW_HIDE);
	
}

BOOL GameDlg::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	monsterstep = 0;
	ptr->hwnd = hwnd;
	ptr->HeroInfo.HP = GetDlgItem(hwnd, H_HP);
	ptr->HeroInfo.SH = GetDlgItem(hwnd, H_SHIELD);
	ptr->HeroInfo.EN = GetDlgItem(hwnd, H_ENERGY);
	ptr->HeroInfo.NAME = GetDlgItem(hwnd, Name);
	ptr->HeroInfo.DMG = GetDlgItem(hwnd, HDMG);
	ptr->HeroInfo.HEAL = GetDlgItem(hwnd, H_HEAL);

	ptr->MonstrInfo.HP = GetDlgItem(hwnd, M_HP);
	ptr->MonstrInfo.SH = GetDlgItem(hwnd, M_SH);
	ptr->MonstrInfo.TIMING = GetDlgItem(hwnd, M_TIMER);
	ptr->MonstrInfo.NAME = GetDlgItem(hwnd, MonstrName);
	ptr->MonstrInfo.ATTAK = GetDlgItem(hwnd, M_ATK);
	ptr->MonstrInfo.DMG = GetDlgItem(hwnd, MDMG);
	ptr->MonstrInfo.HEAL = GetDlgItem(hwnd, M_HEAL);
	ShowWindow(ptr->MonstrInfo.DMG, SW_HIDE);
	ShowWindow(ptr->HeroInfo.DMG, SW_HIDE);
	ShowWindow(ptr->MonstrInfo.HEAL, SW_HIDE);
	ShowWindow(ptr->HeroInfo.HEAL, SW_HIDE);
	ptr->trig = 0;
	ptr->Back = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP1));
	
	HeroIconSpace = CreateWindow(L"STATIC", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP,10,520, 275, 353,hwnd, NULL, GetModuleHandle(0),NULL);
	MonstrIconSpace = CreateWindow(L"STATIC", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 820, 520, 275, 353, hwnd, NULL, GetModuleHandle(0), NULL);
	ptr->HeroInfo.NORMAL = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP12));
	ptr->HeroInfo.ATTACK = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP16));
	ptr->HeroInfo.TAKE_DMG = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP17));
	ptr->icons[0] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP2));
	ptr->icons[1] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP3));
	ptr->icons[2] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP4));
	ptr->icons[3] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP5));
	ptr->icons[4] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP6));
	ptr->icons[5] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP7));
	ptr->icons[6] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP8));
	

	for (int i = 0; i < 10;i++)
	for (int j = 0; j < 20; j++)
	{
		TCHAR nom[10];
		field[i][j] = new HANDLE;
		_itot_s(game.Get(j, i), nom, 9);
		*field[i][j] = CreateWindowEx(NULL, L"BUTTON",nom, WS_CHILD | WS_VISIBLE | BS_FLAT, 50+j*50, 15+i*50, 50, 50, hwnd, NULL, GetModuleHandle(0), NULL);
		SetWindowLong((HWND)*field[i][j], GWL_STYLE, ::GetWindowLong((HWND)*field[i][j], GWL_STYLE) | BS_BITMAP | BS_FLAT);
	}
	SendMessage((HWND)HeroIconSpace, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)ptr->game.hero.pic[0]);
	SendMessage((HWND)MonstrIconSpace, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)ptr->game.monstr.pic[0]);

	UpdateAll();
	
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
	UpdateAll();
	if (ptr->game.gameover == 1)
	{
		MessageBox(hwnd, L"YOU LOSE!", L"YOU LOSE!", MB_OK);
		ptr->game.Restart();
		UpdateAll();
		
	}
	if (ptr->game.win == 1)
	{
		MessageBox(hwnd, L"YOU WON!", L"YOU WON!", MB_OK);
		ptr->game.Restart();
		UpdateAll();
		
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
		hdc = BeginPaint(hwnd, &ps);
		hmdc = CreateCompatibleDC(hdc); //Создаёт совместимый с оконным контекст памяти
		SelectObject(hmdc, ptr->Back); //Выбирает объект картинку
		GetObject(ptr->Back, sizeof(bm), (LPSTR)&bm); //получаем высоту и ширину картинки 
		BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, hmdc, 0, 0, SRCCOPY); //Помещает картинку на экран в точку 10, 10
		//из памяти (hmdc) 
		DeleteDC(hmdc); //удаляем из памяти контекст
		//Конец рисования картинки

		EndPaint(hwnd, &ps);

		return 0;
	case WM_TIMER:
		

		SendMessage((HWND)ptr->MonstrIconSpace, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)ptr->game.monstr.pic[0]);
			SendMessage((HWND)ptr->HeroIconSpace, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)ptr->game.hero.pic[0]);
			ShowWindow(ptr->MonstrInfo.DMG, SW_HIDE);


			ShowWindow(ptr->HeroInfo.DMG, SW_HIDE);
			ShowWindow(ptr->MonstrInfo.HEAL, SW_HIDE);


			ShowWindow(ptr->HeroInfo.HEAL, SW_HIDE);
			KillTimer(hwnd, NULL);
			return 0;
			
	

	}
	return FALSE;
}