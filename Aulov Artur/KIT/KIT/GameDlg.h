#pragma once
#include "Library.h"
#include "Game.h"
class GameDlg
{
public:
	GameDlg(void);
public:
	~GameDlg(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static GameDlg* ptr;
	HWND CreateToolTip(int toolID, HWND hDlg, PTSTR pszText);

	Game game;

	void Cls_OnClose(HWND hwnd);
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);

	void clearbonus() { block = false, blocki = false, blockj = false; }

	HBITMAP Back;
	HBITMAP icons[7];
	HBITMAP catapult_b[4];
	HBITMAP build[3][5];

	HWND build_on, HP, COINS, SCORE, LEVEL;	

	HANDLE* catapult[10];
	HANDLE* field[11][10];

	RECT cd;

	int coins, score, level, orders, anim, hp, count_but, phase;
	bool block = false, blocki = false, blockj = false;
};
