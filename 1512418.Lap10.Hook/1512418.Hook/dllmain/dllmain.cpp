// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

#define EXPORT __declspec(dllexport) 

bool i = false;
HHOOK hHook = NULL;
HINSTANCE hinstLib;

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	hinstLib = hModule;
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}


LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{

	PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;
	if (nCode < 0) // không xử lý message 
		return CallNextHookEx(hHook, nCode, wParam, lParam);
	// xử lý message: Ctrl + s		
	if (nCode == HC_ACTION)
	{
		if (wParam == WM_KEYDOWN)
		{
			if ((p->vkCode == 0x53) && GetAsyncKeyState(VK_CONTROL))
			{
				if (i == true)
				{

					i = false;
					SwapMouseButton(i);
					MessageBox(0, L"Bạn sẽ chuyển chuột trái thành chuột phải bình thường như ban đầu", L"Thông báo", MB_OK);

				}
				else
				{
					MessageBox(0, L"Bạn sẽ chuyển chuột phải thành chuột trái", L"Thông báo", MB_OK);
					i = true;
					SwapMouseButton(i);

				}

				return TRUE;
			}
		}
		
	}
	return CallNextHookEx(0, nCode, wParam, lParam);
}
extern "C"
{
	EXPORT void _doInstallHook(HWND hWnd)
	{
		if (hHook != NULL) return;

		hHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)KeyboardProc, hinstLib, 0);
		if (hHook)
			MessageBox(hWnd, L"Setup hook successfully \r\nPress CTRL + S to swap mouse button\r\nPress ALT to uninstall hook", L"Result", MB_OK);
		else
			MessageBox(hWnd, L"Setup hook fail", L"Result", MB_OK);
	}

	EXPORT void _doRemoveHook(HWND hWnd)
	{
		if (hHook == NULL) return;
		UnhookWindowsHookEx(hHook);
		hHook = NULL;
		MessageBox(hWnd, L"Remove hook successfully", L"Result", MB_OK);
	}
}