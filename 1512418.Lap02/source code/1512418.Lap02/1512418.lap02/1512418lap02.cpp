// 1512418lap02.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "1512418lap02.h"
#include "windows.h"
#include "windowsx.h"

#define MAX_LOADSTRING 100

#include <winuser.h>
#include <commctrl.h>
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "ComCtl32.lib")

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_1512418LAP02, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_1512418LAP02));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_1512418LAP02));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(CTLCOLOR_BTN+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_1512418LAP02);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, L"TINH TIEN", WS_OVERLAPPEDWINDOW,
	   CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
HWND txtSo1;
HWND txtSo2;
HWND txtKetQua;
HWND kqSo1;
HWND kqSo2;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_CREATE:
	{
		INITCOMMONCONTROLSEX icc;
		icc.dwSize = sizeof(icc);
		icc.dwICC = ICC_WIN95_CLASSES;
		InitCommonControlsEx(&icc);

		// Lấy font hệ thống
		LOGFONT lf;
		GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
		HFONT hFont = CreateFont(lf.lfHeight, lf.lfWidth,
			lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
			lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
			lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
			lf.lfPitchAndFamily, lf.lfFaceName);



		HWND hwnd = CreateWindowEx(0, TEXT("BUTTON"), TEXT("TÍNH TOÁN"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 850, 300, 100, 25, hWnd, (HMENU)1, hInst, NULL);
		SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

		hwnd = CreateWindow(TEXT("button"), TEXT("THÔNG TIN VỀ TỈ GIÁ!"), WS_VISIBLE | WS_CHILD, 10, 10, 200, 25, hWnd, (HMENU)2, NULL, NULL);
		SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

		hwnd = CreateWindowEx(0, L"STATIC", L"CHUYỂN ĐỔI TIỀN TỆ: MỜI BẠN NHẬP VÀO GIÁ TIỀN IPAD Ở 2 NƠI: ", WS_VISIBLE | WS_CHILD, 200, 130, 600, 25, hWnd, (HMENU)NULL, hInst, NULL);
		SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);


		hwnd = CreateWindowEx(0, L"STATIC", L"NHẬP TIỀN NHẬT(JPY):", WS_CHILD | WS_VISIBLE | SS_LEFT, 200, 200, 150, 25, hWnd, NULL, hInst, NULL);
		SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

		hwnd = CreateWindowEx(0, TEXT("STATIC"), TEXT("NHẬP TIỀN SINGAPORE(SGD):"), WS_CHILD | WS_VISIBLE | SS_LEFT, 200, 300, 150, 25, hWnd, NULL, hInst, NULL);
		SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

		txtSo1 = CreateWindowEx(0, TEXT("EDIT"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER, 350, 200, 100, 25, hWnd, NULL, hInst, NULL);
		SendMessage(txtSo1, WM_SETFONT, WPARAM(hFont), TRUE);

		txtSo2 = CreateWindowEx(0, TEXT("EDIT"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER, 350, 300, 100, 25, hWnd, NULL, hInst, NULL);
		SendMessage(txtSo2, WM_SETFONT, WPARAM(hFont), TRUE);

		kqSo1 = CreateWindowEx(0, TEXT("EDIT"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER, 500, 200, 350, 25, hWnd, NULL, hInst, NULL);
		SendMessage(kqSo1, WM_SETFONT, WPARAM(hFont), TRUE);

		kqSo2 = CreateWindowEx(0, TEXT("EDIT"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER, 500, 300, 350, 25, hWnd, NULL, hInst, NULL);
		SendMessage(kqSo2, WM_SETFONT, WPARAM(hFont), TRUE);

		hwnd = CreateWindowEx(0, TEXT("STATIC"), TEXT("KẾT QUẢ"), WS_CHILD | WS_VISIBLE | SS_LEFT, 200, 400, 100, 25, hWnd, NULL, hInst, NULL);
		SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

		txtKetQua = CreateWindowEx(0, TEXT("EDIT"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER, 350, 400, 500, 25, hWnd, NULL, hInst, NULL);
		SendMessage(txtKetQua, WM_SETFONT, WPARAM(hFont), TRUE);
	}
	break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
			case 1:
			{
				WCHAR* buffer1 = NULL;
				WCHAR* buffer2 = NULL;
				WCHAR* bufferKQ = NULL;
				WCHAR* bufferKQ1 = NULL;
				WCHAR* bufferKQ2 = NULL;

				int size1;
				int size2;
				int sizeKQ;

				int so1;
				int so2;
				int kq;
				int tienNhat;
				int tienSin;

				size1 = GetWindowTextLength(txtSo1);
				size2 = GetWindowTextLength(txtSo2);

				buffer1 = new WCHAR[size1 + 1];
				buffer2 = new WCHAR[size2 + 1];

				GetWindowText(txtSo1, buffer1, size1 + 1);
				GetWindowText(txtSo2, buffer2, size2 + 1);

				so1 = _wtoi(buffer1);
				so2 = _wtoi(buffer2);

				tienSin = so2 * 17000;
				tienNhat = so1 * 200;
				bufferKQ = new WCHAR[255];
				bufferKQ1 = new WCHAR[255];
				bufferKQ2 = new WCHAR[255];
				if (so1 > 0)
				{
					wsprintf(bufferKQ1, L" = %d VND", tienNhat);

					SetWindowText(kqSo1, bufferKQ1);
				}

				if (so2 > 0)
				{
					wsprintf(bufferKQ2, L" = %d VND", tienSin);

					SetWindowText(kqSo2, bufferKQ2);
				}


				if (so1 > 0 && so2 > 0)
				{
					if (tienNhat > tienSin)
					{
						wsprintf(bufferKQ, L"Bạn nên mua ipad tại SINGAPORE");

						SetWindowText(txtKetQua, bufferKQ);
					}
					else
					{
						if (tienNhat < tienSin)
						{
							wsprintf(bufferKQ, L"Bạn nên mua ipad tại NHẬT");

							SetWindowText(txtKetQua, bufferKQ);
						}
						else
						{

							wsprintf(bufferKQ, L"Bạn nên mua ipad tại đâu cũng được vì giá ngang nhau");

							SetWindowText(txtKetQua, bufferKQ);
						}
					}
				}

				else
				{
					//TH1: khong nhap so cho tien
					if (size1 == 0 || size2 == 0)
					{
						if (size1 == 0)
						{
							wsprintf(bufferKQ1, L"Bạn nên nhập giá trị tiền Nhật vào!");

							SetWindowText(kqSo1, bufferKQ1);
						}
						if (size2 == 0)
						{
							wsprintf(bufferKQ2, L"Bạn nên nhập giá trị tiền Singapore vào!");

							SetWindowText(kqSo2, bufferKQ2);
						}
					}
					//TH2: nhap gia tri < 0 
					if (so1 < 0 || so2 < 0)
					{
						if (so1 < 0)
						{
							wsprintf(bufferKQ1, L"Bạn nên nhập vào giá trị > 0 cho tiền Nhật!");

							SetWindowText(kqSo1, bufferKQ1);
						}
						if (so2 < 0)
						{
							wsprintf(bufferKQ2, L"Bạn nên nhập vào giá trị > 0 cho tiền Singapore!");

							SetWindowText(kqSo2, bufferKQ2);
						}

					}
					//Th3: nhap chuoi vao
					if ((size1 != 0 && so1 == 0) || (size2 != 0 && so2 == 0))
					{
						if (size1 != 0 && so1 == 0)
						{
							wsprintf(bufferKQ1, L"giá trị tiền Nhật không chứa các kí tự chữ cái! Mời bạn nhập lại!");

							SetWindowText(kqSo1, bufferKQ1);
						}
						if (size2 != 0 && so2 == 0)
						{
							wsprintf(bufferKQ2, L"giá trị tiền Singapore không chứa các kí tự chữ cái! Mời bạn nhập lại!");

							SetWindowText(kqSo2, bufferKQ2);
						}

					}
					wsprintf(bufferKQ, L"Bạn nên nhập lại dữ liệu vì phát sinh lỗi!");

					SetWindowText(txtKetQua, bufferKQ);
				}




			}

			break;
			case 2:
				if (LOWORD(wParam) == 2)
				{
					MessageBox(NULL, L"1 PNY = 200 VND ; 1 SGD = 17000 VND", L"exchange rate", MB_ICONINFORMATION);
				}
				break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
