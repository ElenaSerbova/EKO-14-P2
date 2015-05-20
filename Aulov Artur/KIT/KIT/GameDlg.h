#pragma once
#include "Library.h"
#include "Game.h"
#include "VictoryDlg.h"

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
	HBITMAP order[2];
	HBITMAP music;

	HWND build_on, HP, COINS, SCORE, LEVEL, music_by;	

	HANDLE* catapult[10];
	HANDLE* field[11][10];
	HANDLE* orders_on[3];

	RECT cd;

	int bonus_coins, bonus_score, score, level, anim, hp, count_but, phase = 0, orders = 3;
	bool block = false, blocki = false, blockj = false, platinum = true;
};
