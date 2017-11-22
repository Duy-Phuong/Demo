// 1512418MidTermFinance.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "1512418MidTermFinance.h"
#include "windows.h"
#include "windowsx.h"
#define MAX_LOADSTRING 100
//
#include <cstddef>         // std::size_t
size_t tem;
#include "vector"
#include "iostream"
using namespace std;
#include "string"
#include "fstream"
string file_open = "quanli.txt";
#include "sstream"
fstream f;
wstring ketqua;
int check = 0;
int sum = 0; ///tong tien
WCHAR* bufferOpen = NULL;
wstring text1;
wstring text;
string outtext;
fstream f1;
int choice = 0;
//
wstring type1[6] = {
	TEXT("An uong"), TEXT("Di chuyen"), TEXT("Nha cua"), TEXT("Xe co"),	TEXT("Nhu yeu pham"), TEXT("Dich vu")
};
TCHAR type[6][20] =
{
	TEXT("An uong"), TEXT("Di chuyen"), TEXT("Nha cua"), TEXT("Xe co"),	TEXT("Nhu yeu pham"), TEXT("Dich vu")
};
string comContent; //noi dung chon trong combobox
//lấy font ht
#include <winuser.h>
#include <commctrl.h>
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "ComCtl32.lib")

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name


HWND txt1;
HWND txt2;
HWND txtKetQua;
HWND btn;
///2 ô text box
WCHAR* buffer1 = NULL;
WCHAR* buffer2 = NULL;
WCHAR* bufferKQ = new WCHAR[255];
WCHAR* b1 = new WCHAR[255];
//biến để cho chạy dòng đầu lưu tiêu đề
int flag = 0;
// chuoi chua so de tinh sum

string to_utf8(const wchar_t* buffer, int len);
string to_utf8(const std::wstring& str);
// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


////

int StringToWString(wstring &ws, string &s);
string convert(float a);// chuyen tu % sang chuoi

////

//ve bieu do
#include <objidl.h>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")
using namespace Gdiplus;
int num1 = 0;
int num2 = 0;
int num3 = 0;
int num4 = 0;
int num5 = 0;
int num6 = 0;
HBITMAP bitmap;
HBITMAP bitmap1;

float num11[7];
float phanTram[7] = {0, 0, 0, 0, 0, 0, 0 };
HWND tx1;
HWND tx2;
HWND tx3;
HWND tx4;
HWND tx5;
HWND tx6;
wstring data;
wstring data1;





int toadoy = 440;
void Draw(Graphics* graphics, HDC hdc, int num, int width, int toadox, int toadoy);
void Draw1(Graphics* graphics, HDC hdc, int num);

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
    LoadStringW(hInstance, IDC_1512418MIDTERMFINANCE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_1512418MIDTERMFINANCE));

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
    wcex.hbrBackground  = (HBRUSH)(COLOR_MENU +1);//COLOR_MENU
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_1512418MIDTERMFINANCE);
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

   HWND hWnd = CreateWindowW(szWindowClass, _T("QUẢN LÍ CHI TIÊU"), WS_OVERLAPPEDWINDOW,
      300, 10, 825, 700, nullptr, nullptr, hInstance, nullptr);

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

int vtx;
GdiplusStartupInput gdiplusStartupInput;
ULONG_PTR           gdiplusToken;
Graphics* graphics;


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case  WM_CREATE :
	{
		bitmap = (HBITMAP)LoadImage(NULL, L"title1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		bitmap1 = (HBITMAP)LoadImage(NULL, L"demo.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);


		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
		///---------
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

		HWND hWndComboBox = CreateWindow(L"combobox", TEXT(""), CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 10, 130, 200, 100, hWnd, (HMENU)ID_CMBCHOICE, hInst, NULL);
		SendMessage(hWndComboBox, WM_SETFONT, WPARAM(hFont), TRUE);



		TCHAR A[20];
		int  k = 0;

		memset(&A, 0, sizeof(A));
		for (k = 0; k <= 5; k += 1)
		{
			wcscpy_s(A, sizeof(A) / sizeof(TCHAR), (TCHAR*)type[k]);

			// Add string to combobox.
			SendMessage(hWndComboBox, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)A);
		}

		// Send the CB_SETCURSEL message to display an initial item 
		//  in the selection field  
		SendMessage(hWndComboBox, CB_SETCURSEL, (WPARAM)2, (LPARAM)0);


		//tao cac static field
		HWND hwnd = CreateWindowEx(0, L"STATIC", L"LOẠI CHI TIÊU:", WS_CHILD | WS_VISIBLE | SS_LEFT, 10, 100, 200, 25, hWnd, NULL, hInst, NULL);
		SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

		hwnd = CreateWindowEx(0, TEXT("STATIC"), TEXT("NỘI DUNG:"), WS_CHILD | WS_VISIBLE | SS_LEFT, 300, 100, 200, 25, hWnd, NULL, hInst, NULL);
		SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

		hwnd = CreateWindowEx(0, TEXT("STATIC"), TEXT("SỐ TIỀN:"), WS_CHILD | WS_VISIBLE | SS_LEFT, 600, 100, 200, 25, hWnd, NULL, hInst, NULL);
		SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

		hwnd = CreateWindowEx(0, TEXT("STATIC"), TEXT("THÊM MỘT LOẠI CHI TIÊU:"), WS_CHILD | WS_VISIBLE | SS_LEFT, 10, 60, 200, 25, hWnd, NULL, hInst, NULL);
		SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

		hwnd = CreateWindowEx(0, TEXT("STATIC"), TEXT("TOÀN BỘ DANH SÁCH CÁC CHI TIÊU:"), WS_CHILD | WS_VISIBLE | SS_LEFT, 10, 180, 200, 25, hWnd, NULL, hInst, NULL);
		SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

		hwnd = CreateWindowEx(0, TEXT("STATIC"), TEXT("THÔNG TIN THỐNG KÊ:"), WS_CHILD | WS_VISIBLE | SS_LEFT, 10, 410, 200, 25, hWnd, NULL, hInst, NULL);
		SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

		hwnd = CreateWindowEx(0, TEXT("STATIC"), TEXT("TỔNG CỘNG:"), WS_CHILD | WS_VISIBLE | SS_LEFT, 500, 500, 80, 25, hWnd, NULL, hInst, NULL);
		SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);
		//tao cac edit box
		txt1 = CreateWindowEx(0, TEXT("EDIT"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER, 300, 130, 200, 25, hWnd, NULL, hInst, NULL);
		SendMessage(txt1, WM_SETFONT, WPARAM(hFont), TRUE);

		txt2 = CreateWindowEx(0, TEXT("EDIT"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER, 600, 130, 200, 25, hWnd, NULL, hInst, NULL);
		SendMessage(txt2, WM_SETFONT, WPARAM(hFont), TRUE);

		txtKetQua = CreateWindowEx(0, TEXT("EDIT"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER, 600, 500, 200, 25, hWnd, NULL, hInst, NULL);
		SendMessage(txtKetQua, WM_SETFONT, WPARAM(hFont), TRUE);

		//tao button
		hwnd = CreateWindowEx(0, TEXT("BUTTON"), TEXT("THÊM"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 600, 170, 200, 25, hWnd, (HMENU)ID_ADD, hInst, NULL);
		SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

		hwnd = CreateWindowEx(0, TEXT("BUTTON"), TEXT("CHÚ THÍCH"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 500, 200, 25, hWnd, (HMENU)ID_INFO, hInst, NULL);
		SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

		hwnd = CreateWindowEx(0, TEXT("BUTTON"), TEXT("THOÁT"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 600, 560, 200, 25, hWnd, (HMENU)ID_THOAT, hInst, NULL);
		SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);
		//danh sách
		btn = CreateWindowEx(0, L"EDIT", nullptr, WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_LEFT | WS_VSCROLL| WS_BORDER, 
			10, 200, 790, 200, hWnd, (HMENU)NULL, (HINSTANCE)GetWindowLong(hWnd, GWLP_HINSTANCE), nullptr);
		SendMessage(btn, WM_SETFONT, WPARAM(hFont), TRUE);

		///load
		//read----------------------------------------------------------------------------------------
		f.open(file_open, ios::in);
		ketqua = L"";
		int dem = 0;
		sum = 0;// moi lan doc file se khoi tao lai
		num1 = 0;
		num2 = 0;
		num3 = 0;
		num4 = 0;
		num5 = 0;

		while (!f.eof())
		{
			string a;
			fflush(stdin);
			getline(f, a);
			if (a == "") //TH dọc vào k có gì
				break;
			if (dem == 0 && a == "LOAI CHI TIEU				NOI DUNG CHI				SO TIEN")//neu file có dong dau roi
			{
				flag = 1;
			}
			//xu li tinh tong
			if (dem != 0)//tranh dong dau
			{
				string b;
				string c;
				int value = 0;
				b = a;
				//tinh de ve chart
				tem = b.find_first_of("\t");
				c = b.substr(0, tem);//"An uong"), TEXT("Di chuyen"), TEXT("Nha cua"), TEXT("Xe co"),	TEXT("Nhu yeu pham"), TEXT("Dich vu")


										 //
				tem = b.find_last_of("\t");
				b = b.substr(tem + 1);
				string::size_type sz;

				value = stoi(b, &sz);
				b.clear();
				//
				if (c == "An uong")
				{
					num1 += value;
				}
				if (c == "Di chuyen")
				{
					num2 += value;
				}
				if (c == "Nha cua")
				{
					num3 += value;
				}
				if (c == "Xe co")
				{
					num4 += value;
				}
				if (c == "Nhu yeu pham")
				{
					num5 += value;
				}
				if (c == "Dich vu")
				{
					num6 += value;
				}
				sum += value;

				
			}
			//getline(f, text1);
			dem++;
			StringToWString(text1, a);///****

			ketqua += text1;

			ketqua += L"\r\n";
			
			a.clear();
			if (f.eof())
				break;

		}

		bufferOpen = new WCHAR[ketqua.length() + 1];
		for (int i = 0; i < ketqua.length(); i++)
		{
			bufferOpen[i] = ketqua[i];
		}
		bufferOpen[ketqua.length()] = '\0';
		SetWindowText(btn, bufferOpen);

		//tong
		wsprintf(bufferKQ, L"%d", sum);

		SetWindowText(txtKetQua, bufferKQ);
		//chart 
		num11[1] = ((float)num1 / sum) * 750.0;
		num11[2] = ((float)num2 / sum) * 750.0;
		num11[3] = ((float)num3 / sum) * 750.0;
		num11[4] = ((float)num4 / sum) * 750.0;
		num11[5] = ((float)num5 / sum) * 750.0;
		num11[6] = ((float)num6 / sum) * 750.0;//800 là chiều dài sum

		//luu lại %
		for (int i = 1; i <= 6; i++)
		{
			phanTram[i] = (num11[i] * 100) / 750;
		}

		/*
		tinh ra so %
		100% --> 800px
		?% ---> xpx

		=> số px lm chiều rộng chart
		*/
		
		tx1 = CreateWindowEx(0, TEXT("EDIT"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER, 40, 530, 30, 25, hWnd, NULL, hInst, NULL);
		SendMessage(tx1, WM_SETFONT, WPARAM(hFont), TRUE);

		tx2 = CreateWindowEx(0, TEXT("EDIT"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER, 40, 560, 30, 25, hWnd, NULL, hInst, NULL);
		SendMessage(tx2, WM_SETFONT, WPARAM(hFont), TRUE);

		tx3 = CreateWindowEx(0, TEXT("EDIT"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER, 40, 590, 30, 25, hWnd, NULL, hInst, NULL);
		SendMessage(tx3, WM_SETFONT, WPARAM(hFont), TRUE);

		tx4 = CreateWindowEx(0, TEXT("EDIT"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER, 180, 530, 30, 25, hWnd, NULL, hInst, NULL);
		SendMessage(tx4, WM_SETFONT, WPARAM(hFont), TRUE);

		tx5 = CreateWindowEx(0, TEXT("EDIT"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER, 180, 560, 30, 25, hWnd, NULL, hInst, NULL);
		SendMessage(tx5, WM_SETFONT, WPARAM(hFont), TRUE);

		tx6 = CreateWindowEx(0, TEXT("EDIT"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER, 180, 590, 30, 25, hWnd, NULL, hInst, NULL);
		SendMessage(tx6, WM_SETFONT, WPARAM(hFont), TRUE);
		if (flag == 0)//chua co gi
		{
			for (int i = 0; i <= 6; i++)
			{
				phanTram[i] = 0;
			}
		}
		int aa = (int)phanTram[1];
		wsprintf(b1, L"%d %%", aa);//de in kí tu % dung %%

		SetWindowText(tx1, b1);

		aa = (int)phanTram[2];
		wsprintf(b1, L"%d %%", aa);

		SetWindowText(tx2, b1);
		aa = (int)phanTram[3];
		wsprintf(b1, L"%d %%", aa);

		SetWindowText(tx3, b1);

		aa = (int)phanTram[4];
		wsprintf(b1, L"%d %%", aa);

		SetWindowText(tx4, b1);

		aa = (int)phanTram[5];
		wsprintf(b1, L"%d %%", aa);

		SetWindowText(tx5, b1);
		aa = (int)phanTram[6];
		wsprintf(b1, L"%d %%", aa);

		SetWindowText(tx6, b1);

		////////-------------------end-------------------------------
		f.close();

	}
		break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
			int notifycode = HIWORD(wParam);
			HWND combobox = (HWND)lParam;
            // Parse the menu selections:
            switch (wmId)
            {
			case ID_THOAT:
			{
				int result = MessageBox(
					NULL,      // Không có owner windows
					(LPCWSTR)L"Bạn có muốn thoát không?",      // thông điệp chính
					(LPCWSTR)L"Caution",     // văn bản trên title bar
					MB_YESNO + MB_ICONQUESTION + MB_DEFBUTTON1);
				// hiển thị nút Yes No, kèm Icon Question và nút Yes là mặc định

				// Nếu người dùng chọn Yes
				if (result == IDYES)
				{
					DestroyWindow(hWnd);

				}

			}
				break;
			case ID_CMBCHOICE:
			{
				if (notifycode == CBN_SELCHANGE) {
					choice = ComboBox_GetCurSel(combobox);
					//MessageBox(hWnd, type[i], L"Lựa chọn", MB_OK);
				}
			}
				
				break;
			case ID_ADD:
			{

				//MessageBox(NULL, L"1 test", L"info ", MB_ICONINFORMATION);
				

				WCHAR* bufferKQ2 = NULL;

				int size1;
				int size2;
				int sizeKQ;

				int so1;
				int so2;
				int kq;

				size1 = GetWindowTextLength(txt1);
				size2 = GetWindowTextLength(txt2);

				buffer1 = new WCHAR[size1 + 1];
				buffer2 = new WCHAR[size2 + 1];

				GetWindowText(txt1, buffer1, size1 + 1);
				GetWindowText(txt2, buffer2, size2 + 1);

				so2 = _wtoi(buffer2);

				bufferKQ2 = new WCHAR[255];
				
					//TH1: khong nhap so cho tien
					if (size2 == 0)
					{
						
						if (size2 == 0)
						{
							wsprintf(bufferKQ2, L"Bạn nên nhập giá trị tiền vào!");
							MessageBox(NULL, bufferKQ2, L"info ", MB_ICONINFORMATION);
						}
					}					
					if (so2 < 0)
					{
						wsprintf(bufferKQ2, L"Bạn nên nhập vào giá trị > 0 cho tiền !");
						MessageBox(NULL, bufferKQ2, L"info ", MB_ICONINFORMATION);
					}
						
					
				//save --------------------------------------------------------------------------------
					if (size1 > 0 && size2 > 0 && so2 > 0)//neu co noi dung va tien > 0
					{
						f1.open(file_open, ios::out | ios::app);
						text = type1[choice];
						outtext = to_utf8(text); // chuyen thanh string
						if (flag == 0)
						{
							f1 << "LOAI CHI TIEU				NOI DUNG CHI				SO TIEN";
							flag = 1;
						}
						f1 << "\n";//xuong hang

						f1 << outtext;
						switch (choice)
						{
						case 0: case 2: case 3: case 5:

							f1 << "\t\t\t\t\t";
							break;
						case 4: case 1:
							f1 << "\t\t\t\t";
							break;
						}
						outtext.clear();
						outtext = to_utf8(buffer1); // chuyen thanh string

						f1 << outtext;
						f1 << "\t\t\t\t\t";
						outtext.clear();
						outtext = to_utf8(buffer2); // chuyen thanh string
						f1 << outtext;

						f1.close();
						text.clear();
						outtext.clear();
						if (buffer1 != NULL)
						{
							delete[] buffer1;
						}
						if (buffer2 != NULL)
						{
							delete[] buffer2;
						}
					}
					
				//read----------------------------------------------------------------------------------------
				f.open(file_open, ios::in);
				ketqua = L"";
				int dem = 0;
				sum = 0;// moi lan doc file se khoi tao lai
				num1 = 0;
				num2 = 0;
				num3 = 0;
				num4 = 0;
				num5 = 0;
				num6 = 0;
				
				while (!f.eof())
				{
					string a;
					fflush(stdin);
					getline(f, a);

					//xu li tinh tong
					if (dem != 0)//tranh dong dau
					{
						string b;
						string c;
						int value = 0;
						b = a;
						//tinh de ve chart
						tem = b.find_first_of("\t");
						c = b.substr(0, tem);


											 //
						tem = b.find_last_of("\t");
						b = b.substr(tem + 1);
						string::size_type sz1;

						value = stoi(b, &sz1);
						b.clear();
						//
						if (c == "An uong")
						{
							num1 += value;
						}
						if (c == "Di chuyen")
						{
							num2 += value;
						}
						if (c == "Nha cua")
						{
							num3 += value;
						}
						if (c == "Xe co")
						{
							num4 += value;
						}
						if (c == "Nhu yeu pham")
						{
							num5 += value;
						}
						if (c == "Dich vu")
						{
							num6 += value;
						}
						sum += value;


					}
					dem++;
					StringToWString(text1, a);///****

					ketqua += text1;

					ketqua += L"\r\n";

					a.clear();
					if (f.eof())
						break;

				}

				bufferOpen = new WCHAR[ketqua.length() + 1];
				for (int i = 0; i < ketqua.length(); i++)
				{
					bufferOpen[i] = ketqua[i];
				}
				bufferOpen[ketqua.length()] = '\0';
				SetWindowText(btn, bufferOpen);
				//in ra tong tien -------------------------------------------------------------------------------
				wsprintf(bufferKQ, L"%d", sum);

				SetWindowText(txtKetQua, bufferKQ);
				///--chart
				num11[1] = ((float)num1 / sum) * 750.0;
				num11[2] = ((float)num2 / sum) * 750.0;
				num11[3] = ((float)num3 / sum) * 750.0;
				num11[4] = ((float)num4 / sum) * 750.0;
				num11[5] = ((float)num5 / sum) * 750.0;
				num11[6] = ((float)num6 / sum) * 750.0;
				//luu lại %
				for (int i = 1; i <= 6; i++)
				{
					phanTram[i] = (num11[i] * 100)/ 750;
				}

				if (flag == 0)//chua co gi
				{
					for (int i = 0; i <= 6; i++)
					{
						phanTram[i] = 0;
					}
				}

				int aa = (int)phanTram[1];
				wsprintf(b1, L"%d %%", aa);

				SetWindowText(tx1, b1);

				aa = (int)phanTram[2];
				wsprintf(b1, L"%d %%", aa);

				SetWindowText(tx2, b1);
				aa = (int)phanTram[3];
				wsprintf(b1, L"%d %%", aa);

				SetWindowText(tx3, b1);

				aa = (int)phanTram[4];
				wsprintf(b1, L"%d %%", aa);

				SetWindowText(tx4, b1);

				aa = (int)phanTram[5];
				wsprintf(b1, L"%d %%", aa);

				SetWindowText(tx5, b1);
				aa = (int)phanTram[6];
				wsprintf(b1, L"%d %%", aa);

				SetWindowText(tx6, b1);
				//ve chart
				PAINTSTRUCT ps1;
				vtx = 10;
				HDC hdc1 = BeginPaint(hWnd, &ps1);
				// TODO: Add any drawing code that uses hdc here...
				int vtx = 10;
				for (int i = 1; i <= 6; i++)
				{
					Draw(graphics, hdc1, i, num11[i], vtx, toadoy);
					vtx += num11[i];
				}
				InvalidateRect(hWnd, NULL, TRUE);

				EndPaint(hWnd, &ps1);

				////////-------------------end-------------------------------
				f.close();
				check = 1;
				if (bufferOpen != NULL)
				{
					delete[] bufferOpen;
				}
			}
			break;
			case ID_INFO:
			{

				MessageBox(NULL, L"1 màu xanh nhạt: An uong\n2 màu đỏ: Di chuyen\n3 màu da trời: Nha cua\n4 màu xanh lá cây: Xe co\n5 màu xanh da trời nhạt: Nhu yeu pham\n6 màu tím: Dich vu\n ", L"Chú thích ", MB_ICONINFORMATION);
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
			vtx = 10;
			for (int i = 1; i <= 6; i++)
			{
				Draw(graphics, hdc, i, num11[i], vtx, toadoy);
				vtx += num11[i];
			}

			for (int i = 1; i <= 6; i++)
			{
				Draw1(graphics, hdc, i);
				vtx += num11[i];
			}
			//them hinh

			HDC hMemDC = CreateCompatibleDC(hdc);
			::SelectObject(hMemDC, bitmap);
			//BitBlt(hdc, 700, 10, 100, 50, hMemDC, 0, 0, SRCCOPY);
			BitBlt(hdc, 300, 10, 720, 80, hMemDC, 0, 0, SRCCOPY);
			::DeleteDC(hMemDC);
			
			HDC hMemDC1 = CreateCompatibleDC(hdc);
			::SelectObject(hMemDC1, bitmap1);
			BitBlt(hdc, 300, 490, 200, 200, hMemDC1, 0, 0, SRCCOPY);
			::DeleteDC(hMemDC1);

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
		GdiplusShutdown(gdiplusToken);

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

int StringToWString(wstring &ws, string &s)
{
	std::wstring wsTmp(s.begin(), s.end());

	ws = wsTmp;

	return 0;
}

//save

string to_utf8(const wchar_t* buffer, int len)
{
	int nChars = ::WideCharToMultiByte(CP_UTF8, 0, buffer, len, NULL, 0, NULL, NULL);
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

//draw
void Draw(Graphics* graphics, HDC hdc, int num, int width, int toadox, int toadoy)
{
	graphics = new Graphics(hdc);
	int lineWidth = 1;
	Pen* pen = new Pen(Color(255, 0, 0, 0), lineWidth);
	if (num == 1)
	{
		graphics->DrawRectangle(pen, toadox, toadoy, width, 25);

		HatchBrush* myHatchBrush = new HatchBrush(
			HatchStyleCross,
			Color(255, 169, 244, 1),
			Color(255, 169, 244, 1));

		graphics->FillRectangle(myHatchBrush, toadox, toadoy, width, 25);
	}
	if (num == 2)
	{
		graphics->DrawRectangle(pen, toadox, toadoy, width, 25);

		HatchBrush* myHatchBrush = new HatchBrush(
			HatchStyleCross,
			Color(255, 255, 0, 0),
			Color(255, 255, 0, 0));

		graphics->FillRectangle(myHatchBrush, toadox, toadoy, width, 25);
	}
	if (num == 3)
	{
		graphics->DrawRectangle(pen, toadox, toadoy, width, 25);

		HatchBrush* myHatchBrush = new HatchBrush(
			HatchStyleCross,
			Color(255, 0, 0, 255),
			Color(255, 0, 0, 255));

		graphics->FillRectangle(myHatchBrush, toadox, toadoy, width, 25);
	}
	if (num == 4)
	{
		graphics->DrawRectangle(pen, toadox, toadoy, width, 25);

		HatchBrush* myHatchBrush = new HatchBrush(
			HatchStyleCross,
			Color(255, 0, 255, 0),
			Color(255, 0, 255, 0));

		graphics->FillRectangle(myHatchBrush, toadox, toadoy, width, 25);
	}
	if (num == 5)
	{
		graphics->DrawRectangle(pen, toadox, toadoy, width, 25);

		HatchBrush* myHatchBrush = new HatchBrush(
			HatchStyleCross,
			Color(255, 0, 255, 255),
			Color(255, 0, 255, 255));


		graphics->FillRectangle(myHatchBrush, toadox, toadoy, width, 25);
	}
	if (num == 6)
	{
		graphics->DrawRectangle(pen, toadox, toadoy, width, 25);

		HatchBrush* myHatchBrush = new HatchBrush(
			HatchStyleCross,
			Color(255, 255, 0, 255),
			Color(255, 255, 0, 255));


		graphics->FillRectangle(myHatchBrush, toadox, toadoy, width, 25);
	}


	delete pen;
	delete graphics;
}

void Draw1(Graphics* graphics, HDC hdc, int num)
{
	graphics = new Graphics(hdc);
	int lineWidth = 1;
	Pen* pen = new Pen(Color(255, 0, 0, 0), lineWidth);
	
		if (num == 1)
		{
			graphics->DrawRectangle(pen, 10, 530, 25, 25);
			HatchBrush* myHatchBrush = new HatchBrush(
				HatchStyleCross,
				Color(255, 169, 244, 1),
				Color(255, 169, 244, 1));
			graphics->FillRectangle(myHatchBrush, 10, 530, 25, 25);

		}
		if (num == 2)
		{
			graphics->DrawRectangle(pen, 10, 560, 25, 25);

			HatchBrush* myHatchBrush = new HatchBrush(
				HatchStyleCross,
				Color(255, 255, 0, 0),
				Color(255, 255, 0, 0));

			graphics->FillRectangle(myHatchBrush, 10, 560, 25, 25);
		}
		if (num == 3)
		{
			graphics->DrawRectangle(pen, 10, 590, 25, 25);

			HatchBrush* myHatchBrush = new HatchBrush(
				HatchStyleCross,
				Color(255, 0, 0, 255),
				Color(255, 0, 0, 255));

			graphics->FillRectangle(myHatchBrush, 10, 590, 25, 25);
		}
		if (num == 4)
		{
			graphics->DrawRectangle(pen, 150, 530, 25, 25);

			HatchBrush* myHatchBrush = new HatchBrush(
				HatchStyleCross,
				Color(255, 0, 255, 0),
				Color(255, 0, 255, 0));

			graphics->FillRectangle(myHatchBrush, 150, 530, 25, 25);
		}
		if (num == 5)
		{
			graphics->DrawRectangle(pen, 150, 560, 25, 25);

			HatchBrush* myHatchBrush = new HatchBrush(
				HatchStyleCross,
				Color(255, 0, 255, 255),
				Color(255, 0, 255, 255));


			graphics->FillRectangle(myHatchBrush, 150, 560, 25, 25);
		}
		if (num == 6)
		{
			graphics->DrawRectangle(pen, 150, 590, 25, 25);

			HatchBrush* myHatchBrush = new HatchBrush(
				HatchStyleCross,
				Color(255, 255, 0, 255),
				Color(255, 255, 0, 255));


			graphics->FillRectangle(myHatchBrush, 150, 590, 25, 25);

		}
	
	delete pen;
	delete graphics;
}

string convert(float a)
{
	stringstream ss;
	ss << a;
	return ss.str();
}