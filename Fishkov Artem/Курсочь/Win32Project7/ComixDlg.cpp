#include "Comix.h"

ComixDlg* ComixDlg::ptr = NULL;

BOOL CALLBACK ComixDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	

	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}

void ComixDlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	SendMessage((HWND)ptr->PageStatic, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)ptr->pages[1]);
	if (hwndCtl == Close)
	{
		EndDialog(hwnd, 0);
	}
	if (hwndCtl == Next)
	{
		ptr->curent_page++;
		if (curent_page > page_count)
		{
			EndDialog(hwnd, 0);
		}
		
	}
	SendMessage((HWND)ptr->PageStatic, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)ptr->pages[ptr->curent_page]);
	
}

BOOL ComixDlg::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{

	ptr->curent_page = 0;
	ptr->Close = GetDlgItem(hwnd, IDCANCEL);
	ptr->Next = GetDlgItem(hwnd, IDC_NEXT);
	ptr->Prev = GetDlgItem(hwnd, IDC_PREV);
	ptr->PageStatic = GetDlgItem(hwnd, IDC_PIC);
	SetWindowLong((HWND)ptr->PageStatic, GWL_STYLE, ::GetWindowLong((HWND)ptr->PageStatic, GWL_STYLE) | SS_BITMAP);
	SendMessage((HWND)ptr->PageStatic, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)ptr->pages[ptr->curent_page]);
	return 0;
}


void ComixDlg::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}


ComixDlg::ComixDlg(void)
{
	ptr = this;
}

ComixDlg::~ComixDlg(void)
{

}