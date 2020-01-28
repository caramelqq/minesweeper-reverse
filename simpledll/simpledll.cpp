// simpledll.cpp : Defines the exported functions for the DLL application.
//
#include <Windows.h>
#include "stdafx.h"
#include "simpledll.h"

void showmines()
{
	char* field = (char*) 0x01005340;

	for(int i = 0; i < 800; ++i)
	{
		if(((*(field+i) & 0x80) != 0) && *(field+i) != 0x10)
		{
			*(field+i) = 0x8E;
		}
	}

	HWND hello = FindWindowA(NULL, "Minesweeper");

	if(hello == NULL)
		MessageBox(NULL, L"Fail", L"Fail", MB_OK);
	
	RECT dim;
	GetWindowRect(hello, &dim);

	LPARAM lParam;
	int rowmax = dim.bottom-dim.top;
	int colmax = dim.right-dim.left;
	for(int i = 55; i < rowmax; i+=10)
	{
		for(int j = 10; j < colmax; j+=10)
		{
			lParam = (i << 16) | j;
			SendMessage(hello, WM_LBUTTONDOWN, MK_LBUTTON, lParam);
			SendMessage(hello, WM_LBUTTONUP, NULL, lParam);
		}
	}
}