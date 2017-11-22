// 1512418Lap03.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "1512418Lap03.h"
#include "windows.h"
#include "windowsx.h"
#include "iostream"
using namespace std;
#include "string"
#include "fstream"

//open file
#include <Commdlg.h>
OPENFILENAME ofn;
// a another memory buffer to contain the file name
TCHAR szFile[100];
#include "atlstr.h"
string file_open;
string file_save;

#define MAX_LOADSTRING 100
#define IDM_FILE_NEW 1000
#define IDM_FILE_OPEN 1001
#define IDM_FILE_SAVE 1002
#define IDM_FILE_EXIT 1003
#define IDM_FILE_ABOUT 1004

#define IDM_FILE_CUT 1005
#define IDM_FILE_COPY 1006
#define IDM_FILE_PASTE 1007
#define ID_EDITCHILD 1008
// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

HWND btntest;
HWND btntext;
HMENU hmenu;
HWND btn;
WCHAR* buffer1 = NULL;

string to_utf8(const wchar_t* buffer, int len);
string to_utf8(const std::wstring& str);

ofstream testFile;
string outtext;
wstring text;
int size1;
int size2;

WCHAR* buffer2 = NULL;

wifstream File1;
wstring text1;
wstring ketqua;
int check = 0;
int check_save = 0;
int result;
void AddMenu(HWND hWnd);
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
    LoadStringW(hInstance, IDC_1512418LAP03, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_1512418LAP03));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_1512418LAP03);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

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

   HWND hWnd = CreateWindowW(szWindowClass, L"NOTEPAD", WS_OVERLAPPEDWINDOW | WS_SIZEBOX,
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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_CREATE:
		AddMenu(hWnd);


		btn  = CreateWindowEx(0, L"EDIT", nullptr, WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_LEFT | WS_HSCROLL | WS_VSCROLL, 0, 0, 200, 200 , hWnd, (HMENU)NULL, (HINSTANCE)GetWindowLong(hWnd, GWLP_HINSTANCE), nullptr);
		break;
	case WM_SIZE:
		MoveWindow(btn, 0, 0, LOWORD(lParam), HIWORD(lParam), TRUE);
		break;
	case WM_SETFOCUS:
		SetFocus(btn);
		break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
			case IDM_FILE_NEW:
				if (check_save == 0)
				{
					result = MessageBox(NULL, L"Bạn có muốn lưu lại hay không", L"Thông báo", MB_YESNO | MB_ICONINFORMATION);
					if (result == IDYES)
					{
						goto E;
					}
				}
			
				//EnableMenuItem(GetMenu(hWnd),IDM_FILE_SAVE, MF_BYCOMMAND | MF_DISABLED );
				SendMessage(btn, WM_SETTEXT, 0, (LPARAM)L"");
				//SendMessage(btn, EM_SETMODIFY, FALSE, 0);

				check_save = 0;// neu luu r se k thong bao lai
				break;
			case IDM_FILE_OPEN:
				ZeroMemory(&ofn, sizeof(ofn));
				//set attribute for
				ofn.lStructSize = sizeof(ofn);
				ofn.hwndOwner = NULL;
				ofn.lpstrFile = szFile;
				ofn.lpstrFile[0] = '\0';
				ofn.nMaxFile = sizeof(szFile);
				ofn.lpstrFilter = (LPCWSTR)L"Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
				ofn.nFilterIndex = 1;
				ofn.lpstrFileTitle = NULL;
				ofn.nMaxFileTitle = 0;
				ofn.lpstrInitialDir = NULL;
				ofn.lpstrDefExt = (LPCWSTR)L"txt";
				ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
				GetOpenFileName(&ofn);
				file_open = CW2A(ofn.lpstrFile);
				File1.open(file_open, ios::in);
				ketqua = L"";
				while (!File1.eof())
				{
					fflush(stdin);
					getline(File1, text1);
					ketqua += text1;
					if (File1.eof())
						break;
					ketqua += L"\r\n";
				}
				
				buffer2 = new WCHAR[ketqua.length() + 1];
				for (int i = 0; i < ketqua.length(); i++)
				{
					buffer2[i] = ketqua[i];
				}
				buffer2[ketqua.length()] = '\0';

				SetWindowText(btn, buffer2);

				File1.close();
				check = 1;
				if (buffer2 != NULL)
				{
					delete[] buffer2;
				}
				break;
			case IDM_FILE_SAVE:
				MessageBeep(MB_OK);
			E:
				if (check == 0)
				{
					ZeroMemory(&ofn, sizeof(ofn));
					//set attribute for
					ofn.lStructSize = sizeof(ofn);
					ofn.hwndOwner = NULL;
					ofn.lpstrFile = szFile;
					ofn.lpstrFile[0] = '\0';
					ofn.nMaxFile = sizeof(szFile);
					ofn.lpstrFilter = (LPCWSTR)L"Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
					ofn.nFilterIndex = 1;
					ofn.lpstrFileTitle = NULL;
					ofn.nMaxFileTitle = 0;
					ofn.lpstrInitialDir = NULL;
					ofn.lpstrDefExt = (LPCWSTR)L"txt";
					ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
					GetSaveFileName(&ofn);
					file_save = CW2A(ofn.lpstrFile);
					int x = 0; 

					if (file_save.find('<') == NULL || file_save.find('>') == NULL || file_save.find('?') == NULL || file_save.find('\\') == NULL || file_save.find(':') == NULL || file_save.find('\"') == NULL || file_save.find('<') == NULL || file_save.find('/') == NULL || file_save.find('|') == NULL || file_save.find('*') == NULL)
					{
						MessageBox(NULL, L"Bạn phải lại nhập tên cho file không chứa kí tự đặc biệt", L"Thông báo", MB_OK | MB_ICONINFORMATION);
					}
					
				}
				else
				{
					file_save = file_open;
					check = 0;
					
				}
				size1 = GetWindowTextLength(btn);
				buffer1 = new WCHAR[size1 + 1];
				GetWindowText(btn, buffer1, size1 + 1);

				text = buffer1;

				testFile.open(file_save, ios::out);

				outtext = to_utf8(text); // chuyen thanh string

				testFile << outtext;

				testFile.close();
				text.clear();
				outtext.clear();
				if (buffer1 != NULL)
				{
					delete[] buffer1;
				}
				check_save = 1;
				break;
			case IDM_FILE_EXIT:
				MessageBeep(MB_OK);
				DestroyWindow(hWnd);
				break;
			case IDM_FILE_CUT:
				SendMessage(btn, WM_CUT, 0, 0);
				break;
			case IDM_FILE_COPY:
				SendMessage(btn, WM_COPY, 0, 0);

				break;
			case IDM_FILE_PASTE:
				SendMessage(btn, WM_PASTE, 0, 0);
				break;
			case IDM_FILE_ABOUT:
				MessageBox(NULL, L"We can save, open and create a file in my NOTEPAD ", L"INFORMATION", MB_ICONINFORMATION);

				break;


            case IDM_ABOUT:
              //  DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
				
			  // EnableWindow(btntest, TRUE); //send message to button

                break;
            case IDM_EXIT:
				result = MessageBox(NULL, L"Bạn có muốn lưu lại hay không", L"Thông báo", MB_YESNO | MB_ICONINFORMATION);
				if (result == IDYES)
				{
					goto E;
				}
				
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

void AddMenu(HWND hWnd)
{
	hmenu = CreateMenu();
	HMENU hFileMenu = CreateMenu();
	HMENU hFileMenu1 = CreateMenu();
	HMENU hFileMenu2 = CreateMenu();
	
	AppendMenu(hmenu, MF_POPUP, (UINT_PTR)hFileMenu, L"File");
	AppendMenu(hFileMenu, MF_STRING, IDM_FILE_NEW, L"New");
	AppendMenu(hFileMenu, MF_STRING, IDM_FILE_OPEN, L"Open...");
	AppendMenu(hFileMenu, MF_STRING, IDM_FILE_SAVE, L"Save");

	AppendMenu(hFileMenu, MF_STRING, IDM_EXIT, L"Exit");
	AppendMenu(hmenu, MF_POPUP, (UINT_PTR)hFileMenu2, L"Edit");
	AppendMenu(hFileMenu2, MF_STRING, IDM_FILE_CUT, L"Cut");
	AppendMenu(hFileMenu2, MF_STRING, IDM_FILE_COPY, L"Copy");
	AppendMenu(hFileMenu2, MF_STRING, IDM_FILE_PASTE, L"Paste");
	//AppendMenu(hmenu, MF_STRING, NULL, L"Format");
	//AppendMenu(hmenu, MF_STRING, NULL, L"View");
	AppendMenu(hmenu, MF_POPUP, (UINT_PTR)hFileMenu1, L"Help");
	AppendMenu(hFileMenu1, MF_STRING, IDM_FILE_ABOUT, L"About");


	SetMenu(hWnd, hmenu);
}

string to_utf8(const wchar_t* buffer, int len)
{
	int nChars = ::WideCharToMultiByte(	CP_UTF8, 0, buffer, len, NULL, 0, NULL, NULL);
	if (nChars == 0) return "";

	string newbuffer;
	newbuffer.resize(nChars);
	::WideCharToMultiByte(
		CP_UTF8,
		0,
		buffer,
		len,
		const_cast< char* >(newbuffer.c_str()),
		nChars,
		NULL,
		NULL);

	return newbuffer;
}

string to_utf8(const std::wstring& str)
{
	return to_utf8(str.c_str(), (int)str.size());
}