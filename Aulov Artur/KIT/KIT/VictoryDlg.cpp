#include "VictoryDlg.h"
#pragma once

VictoryDlg* VictoryDlg::ptr = NULL;

VictoryDlg::VictoryDlg(int orders, int score, bool pl)
{
	ptr = this;
	this->orders = orders;
	this->score = score;
	this->pl = pl;
}

VictoryDlg::~VictoryDlg(void)
{

}

void VictoryDlg::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}



BOOL VictoryDlg::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	ptr->VBG1 = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP23));
	ptr->VBG2 = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP24));
	ptr->VBG3 = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP25));
	ptr->VBGP = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP22));
	GetClientRect(hwnd, &cd);
	return 0;
}

void VictoryDlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	Cls_OnClose(hwnd);
}

BOOL CALLBACK VictoryDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
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
		hmdc = CreateCompatibleDC(hdc); //������ ����������� � ������� �������� ������
		if (ptr->orders == 3 && !ptr->pl)
		{
			SelectObject(hmdc, ptr->VBG3); //�������� ������ ��������
			GetObject(ptr->VBG3, sizeof(bm), (LPSTR)&bm); //�������� ������ � ������ �������� 
		}
		else if (ptr->orders == 2 && !ptr->pl)
		{
			SelectObject(hmdc, ptr->VBG2); //�������� ������ ��������
			GetObject(ptr->VBG2, sizeof(bm), (LPSTR)&bm); //�������� ������ � ������ �������� 
		}
		else if (ptr->orders == 1 && !ptr->pl)
		{
			SelectObject(hmdc, ptr->VBG1); //�������� ������ ��������
			GetObject(ptr->VBG1, sizeof(bm), (LPSTR)&bm); //�������� ������ � ������ �������� 
		}
		else if (ptr->pl)
		{
			SelectObject(hmdc, ptr->VBGP); //�������� ������ ��������
			GetObject(ptr->VBGP, sizeof(bm), (LPSTR)&bm); //�������� ������ � ������ �������� 
		}
		BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, hmdc, 0, 0, SRCCOPY); //�������� �������� �� ����� � ����� 10, 10
		//�� ������ (hmdc) 
		DeleteDC(hmdc); //������� �� ������ ��������
		//����� ��������� ��������

		EndPaint(hwnd, &ps);

		return 0;
	}
	return false;
}