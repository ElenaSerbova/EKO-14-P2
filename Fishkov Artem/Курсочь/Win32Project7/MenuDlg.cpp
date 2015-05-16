#include "MenuDlg.h"
#include "GameDlg.h"

MenuDlg* MenuDlg::ptr = NULL;

BOOL CALLBACK MenuDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}

void MenuDlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{

	GameDlg dlg;
	ShowWindow(hwnd, SW_HIDE);
	DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG1), NULL, GameDlg::DlgProc);
	ShowWindow(hwnd, SW_SHOW);	

	
}

BOOL MenuDlg::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
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