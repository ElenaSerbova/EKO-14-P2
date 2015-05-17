#pragma once
#include "header.h"

class GameDlg
{
public:
	GameDlg(bool cgame);
public:
	~GameDlg(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static GameDlg* ptr;
	void Cls_OnClose(HWND hwnd);
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnCreate(HWND hwnd);
	bool trig;
	int phase;
	Game game;
	HBITMAP Back;
	HBITMAP icons[7];
	HANDLE* catapult[10];
	HBITMAP build[3][5];
	HWND build_on, HP;
	HANDLE* field[11][10];
	bool cgame;
	RECT cd;
	int coins, score, level, orders, anim, hp;
};
