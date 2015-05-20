#pragma once
#include "Library.h"

class VictoryDlg
{
public:
	VictoryDlg(int orders, int score, bool pl);
	~VictoryDlg(void);

	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static VictoryDlg* ptr;
	void Cls_OnClose(HWND hwnd);
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);

	HBITMAP VBG1, VBG2, VBG3, VBGP;
	RECT cd;

	int orders, score;
	bool pl;
};