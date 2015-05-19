#pragma once
#include "header.h"

class ComixDlg
{
public:
	ComixDlg(void);
public:
	~ComixDlg(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static ComixDlg* ptr;
	void Cls_OnClose(HWND hwnd);
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnCreate(HWND hwnd);
	HWND Next,Prev,Close;
	HBITMAP pages[5];
	HWND PageStatic;
	int curent_page;
	int page_count;
};
