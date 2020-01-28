// dllmain.cpp : Defines the entry point for the DLL application.
#include <Windows.h>

#include "stdafx.h"
#include "resource.h"
#include "simpledll.h"

void __declspec(naked) __declspec(noreturn) UninjectSelf(HMODULE Module)
{
	__asm
	{
		//push -2
		//push 0
		//push Module
		//mov eax, TerminateThread
		//push eax
		//mov eax, FreeLibrary
		//jmp eax
		push -2
		push 0
		push Module
		push TerminateThread
		jmp FreeLibrary
	}
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
				case IDC_Solve:
				{
					showmines();
					return 0;
				}
				case IDOK:
				{
					DestroyWindow(hWnd);
					return 0;
				}
				case IDCANCEL:
				{
					DestroyWindow(hWnd);
					return 0;
				}
			}
		}
		case WM_DESTROY:
		{
			DestroyWindow(hWnd);
			return 0;
		}
	}
	return 0;
}

DWORD WINAPI MainWin(HMODULE hModule)
{
	Sleep(500);
	DialogBox(hModule, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
	UninjectSelf(hModule);
	return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) MainWin, hModule, 0, NULL);
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
         break;
	}
	return TRUE;
}

