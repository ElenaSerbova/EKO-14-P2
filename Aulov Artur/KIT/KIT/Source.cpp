#include "Library.h"
int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpszCmdLine, int nCmdShow)
{
	srand(time(0));
	INITCOMMONCONTROLSEX icc = { sizeof(INITCOMMONCONTROLSEX) };
	icc.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&icc);
	MenuDlg dlg;
	return DialogBox(hInst, MAKEINTRESOURCE(MAIN_MENU), NULL, MenuDlg::DlgProc);
}