#include "Shop.h"

ShopDlg* ShopDlg::ptr = NULL;

BOOL CALLBACK ShopDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}

void ShopDlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
		
}

BOOL ShopDlg::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	List = GetDlgItem(hwnd, IDC_LIST1);
	SendMessage(List, LB_ADDSTRING, NULL, (WPARAM)L"Перегруппировка \1 Эликсир\1");
	return 0;
}


void ShopDlg::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}


ShopDlg::ShopDlg(void)
{
	ptr = this;
}

ShopDlg::~ShopDlg(void)
{

}