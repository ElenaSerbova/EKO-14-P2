#include "MenuDlg.h"
#include "GameDlg.h"
#include "Comix.h"

MenuDlg* MenuDlg::ptr = NULL;

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
		SelectObject(hmdc, ptr->Back); //Выбирает объект картинку
		GetObject(ptr->Back, sizeof(bm), (LPSTR)&bm); //получаем высоту и ширину картинки 
		BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, hmdc, 0, 0, SRCCOPY); //Помещает картинку на экран в точку 10, 10
		//из памяти (hmdc) 
		DeleteDC(hmdc); //удаляем из памяти контекст
		//Конец рисования картинки

		EndPaint(hwnd, &ps);

		return 0;
	}
	return FALSE;
}

void MenuDlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	
	if (hwndCtl == StartB)
	{

		GameDlg dlg;
		ShowWindow(hwnd, SW_HIDE);
		ComixDlg begin;
		begin.pages[0] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP34));
		begin.pages[1] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP35));
		begin.page_count = 1;
		DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG4), NULL, ComixDlg::DlgProc);
		DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG6), NULL, GameDlg::DlgProc);
		ShowWindow(hwnd, SW_SHOW);
	}
	else if (hwndCtl == HelpB)
	{
	}
	else if (hwndCtl == ExitB)
	{
		EndDialog(hwnd,0);
	}
	
}

BOOL MenuDlg::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	Back = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP28));
	Help = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP21));
	Start = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP30));
	Exit = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP29));
	StartB = GetDlgItem(hwnd, IDC_START);
	HelpB = GetDlgItem(hwnd, IDC_HELP);
	ExitB = GetDlgItem(hwnd, IDC_EXIT);
	SetWindowLong((HWND)StartB, GWL_STYLE, ::GetWindowLong((HWND)StartB, GWL_STYLE) | BS_BITMAP | BS_FLAT);
	SetWindowLong((HWND)HelpB, GWL_STYLE, ::GetWindowLong((HWND)HelpB, GWL_STYLE) | BS_BITMAP | BS_FLAT);
	SetWindowLong((HWND)ExitB, GWL_STYLE, ::GetWindowLong((HWND)ExitB, GWL_STYLE) | BS_BITMAP | BS_FLAT);
	SendMessage((HWND)StartB, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)ptr->Start);
	SendMessage((HWND)HelpB, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)ptr->Help);
	SendMessage((HWND)ExitB, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)ptr->Exit);
	return 0;
}


void MenuDlg::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}



MenuDlg::MenuDlg(void)
{
	ptr = this;
}

MenuDlg::~MenuDlg(void)
{

}