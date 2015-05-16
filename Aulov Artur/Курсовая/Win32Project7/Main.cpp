#include <Windows.h>
#include "MenuDlg.h"

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpszCmdLine, int nCmdShow)
{
	srand(time(0));
	INITCOMMONCONTROLSEX icc = { sizeof(INITCOMMONCONTROLSEX) };
	icc.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&icc);
	MenuDlg dlg;
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG2), NULL, MenuDlg::DlgProc);
}