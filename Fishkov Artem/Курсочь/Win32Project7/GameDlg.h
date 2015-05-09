#pragma once
#include "header.h"

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
	bool trig;
	Game game;
	HBITMAP Back;
	HANDLE HeroIconSpace;
	HANDLE MonstrIconSpace;
	HBITMAP Hero;
	HBITMAP Monstr;
	HBITMAP icons[5];
	HANDLE* field[10][20];
};
