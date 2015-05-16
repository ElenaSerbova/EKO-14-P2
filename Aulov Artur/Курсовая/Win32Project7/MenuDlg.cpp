#include "MenuDlg.h"
#pragma once

MenuDlg* MenuDlg::ptr = NULL;

MenuDlg::MenuDlg(void)
{
	ptr = this;
}

MenuDlg::~MenuDlg(void)
{

}

void MenuDlg::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}



BOOL MenuDlg::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	ptr->MenuBG = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP9));
	GetClientRect(hwnd, &cd);
	return 0;
}

void MenuDlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if (id == IDC_BUTTON1)
	{
		GameDlg dlg;
		ShowWindow(hwnd, SW_HIDE);
		DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG1), NULL, GameDlg::DlgProc);
		ShowWindow(hwnd, SW_SHOW);
	}
	if (id == IDC_BUTTON3)
	{
		ptr->Cls_OnClose(hwnd);
	}
}

BOOL CALLBACK MenuDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
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
		SelectObject(hmdc, ptr->MenuBG); //Выбирает объект картинку
		GetObject(ptr->MenuBG, sizeof(bm), (LPSTR)&bm); //получаем высоту и ширину картинки 
		BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, hmdc, 0, 0, SRCCOPY); //Помещает картинку на экран в точку 10, 10
		//из памяти (hmdc) 
		DeleteDC(hmdc); //удаляем из памяти контекст
		//Конец рисования картинки

		EndPaint(hwnd, &ps);

		return 0;
	}
	return false;
}