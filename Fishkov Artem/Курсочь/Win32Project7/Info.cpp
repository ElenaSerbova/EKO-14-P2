#include "resource.h"
#include "Info.h"

InfoDlg* InfoDlg::ptr = NULL;
BOOL CALLBACK InfoDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}

void InfoDlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	EndDialog(hwnd, 0);
}

BOOL InfoDlg::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	/*pages[0] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP21));
	Static = GetDlgItem(hwnd,IDC_STATIC);
	SendMessage((HWND)Static, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)pages[0]);
*/
	return 0;
}


void InfoDlg::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}



InfoDlg::InfoDlg(void)
{
	ptr = this;
}

InfoDlg::~InfoDlg(void)
{

}