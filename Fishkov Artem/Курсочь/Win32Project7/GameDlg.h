#pragma once
#include "header.h"

class InfoH
{
public:
	HBITMAP NORMAL;
	HBITMAP TAKE_DMG;
	HBITMAP ATTACK;
	HWND DMG;
	HWND HP;
	HWND SH;
	HWND EN;
	HWND NAME;
	void SetHP(int hp)
	{
		TCHAR str[30];
		_itot_s(hp,str,10);
		SetWindowText(HP, str);
	}
	void SetSH(int hp)
	{
		TCHAR str[30];
		_itot_s(hp, str, 10);
		SetWindowText(SH, str);
	}
	void SetNAME(TCHAR * name)
	{
		SetWindowText(NAME, name);
	}
	void SetEN(int hp)
	{
		TCHAR str[30];
		_itot_s(hp, str, 10);
		SetWindowText(EN, str);
	}
	void SetDMG(int dmg)
	{
		dmg = -dmg;
		TCHAR str[30];
		_stprintf_s(str, 30, L"%d", dmg);
		SetWindowText(DMG, str);
	}
};
class InfoM
{
public:
	HBITMAP NORMAL;
	HBITMAP TAKE_DMG;
	HBITMAP ATTACK;
	HWND DMG;
	HWND HP;
	HWND SH;
	HWND TIMING;
	HWND NAME;
	HWND ATTAK;
	void SetHP(int hp)
	{
		TCHAR str[30];
		_itot_s(hp, str, 10);
		SetWindowText(HP, str);
	}
	void SetSH(int hp)
	{
		TCHAR str[30];
		_itot_s(hp, str, 10);
		SetWindowText(SH, str);
	}
	void SetNAME(TCHAR * name)
	{
		SetWindowText(NAME, name);
	}
	void SetTIMER(int curT,int T)
	{
		TCHAR str[30];
		_stprintf_s(str,30, L"(%d/%d)", curT, T);
		SetWindowText(TIMING, str);
	}
	void SetATTAK(int att)
	{
		TCHAR str[30];
		_stprintf_s(str, 30, L"%d", att);
		SetWindowText(ATTAK, str);
	}
	void SetDMG(int dmg)
	{
		dmg = -dmg;
		TCHAR str[30];
		_stprintf_s(str, 30, L"%d", dmg);
		SetWindowText(DMG, str);
	}
};

class GameDlg
{
public:
	GameDlg(void);
public:
	~GameDlg(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static GameDlg* ptr;
	void Cls_OnClose(HWND hwnd);
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnCreate(HWND hwnd);
	void UpdateAll();
	bool trig;
	HWND hwnd;
	InfoH HeroInfo;
	InfoM MonstrInfo;
	Game game;
	HBITMAP Back;
	HANDLE HeroIconSpace;
	HANDLE MonstrIconSpace;
	HBITMAP Hero;
	HBITMAP Monstr;
	HBITMAP icons[6];
	HANDLE* field[10][20];

};
