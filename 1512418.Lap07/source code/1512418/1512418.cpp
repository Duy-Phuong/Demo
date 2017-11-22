// 1512418.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "1512418.h"
#include "resource.h"
#define MAX_LOADSTRING 100
#include <windowsx.h>
#include <windows.h>
#include <iostream>
#include <vector>
using namespace std;
vector<int> vx1;
vector<int> vy1;
vector<int> vx2;
vector<int> vy2;
vector<int> types;



#define LINE 0
#define RECTANGLE 1
#define CIRCLE 2
#define ELLIPSE 3
#define SQUARE 4
HDC memHDC;
HDC hdc1;

class CShape {
public:
	virtual void Draw(HDC hdc) = 0;
	virtual void Draw(HDC hdc, int a, int b, int c, int d) = 0;//ve co xem truoc
	virtual CShape* Create() = 0;
	virtual void SetData(int a, int b, int c, int d) = 0;
};

class CLine : public CShape {
public:
	int x1;
	int y1;
	int x2;
	int y2;
public:
	void Draw(HDC hdc) {
		MoveToEx(hdc, x1, y1, NULL);
		LineTo(hdc, x2, y2);
	}
	void Draw(HDC hdc, int a, int b, int c, int d) {
		MoveToEx(hdc, a, b, NULL);
		LineTo(hdc, c, d);
	}
	CShape* Create() { return new CLine; }

	void SetData(int a, int b, int c, int d) {
		x1 = a;
		y1 = b;
		x2 = c;
		y2 = d;
	}
};

class CRectangle : public CShape {
public:
	int x1;
	int y1;
	int x2;
	int y2;
public:
	void Draw(HDC hdc) {
		Rectangle(hdc, x1, y1, x2, y2);
	}
	void Draw(HDC hdc, int a, int b, int c, int d) {
		Rectangle(hdc, a, b, c, d);
	}
	CShape* Create() { return new CRectangle; }

	void SetData(int a, int b, int c, int d) {
		x1 = a;
		y1 = b;
		x2 = c;
		y2 = d;
	}
};
class CEllipse : public CShape {
public:
	int x1;
	int y1;
	int x2;
	int y2;
public:
	void Draw(HDC hdc) {
		Ellipse(hdc, x1, y1, x2, y2);
	}
	void Draw(HDC hdc, int a, int b, int c, int d) {
		Ellipse(hdc, a, b, c, d);
	}
	CShape* Create() { return new CEllipse; }

	void SetData(int a, int b, int c, int d) {
		x1 = a;
		y1 = b;
		x2 = c;
		y2 = d;
	}
};
class CSquare : public CShape {
public:
	int x1;
	int y1;
	int x2;
	int y2;
public:
	void Draw(HDC hdc) {
		Rectangle(hdc, x1, y1, x2, y2);
	}
	void Draw(HDC hdc, int a, int b, int c, int d) {
		Rectangle(hdc, a, b, c, d);
	}
	CShape* Create() { return new CSquare; }

	void SetData(int a, int b, int c, int d) {
		x1 = a;
		y1 = b;
		x2 = c;
		y2 = d;
	}
};
class CCircle : public CShape {
public:
	int x1;
	int y1;
	int x2;
	int y2;
public:
	void Draw(HDC hdc) {
		Ellipse(hdc, x1, y1, x2, y2);
	}
	void Draw(HDC hdc, int a, int b, int c, int d) {
		Ellipse(hdc, a, b, c, d);
	}
	CShape* Create() { return new CCircle; }

	void SetData(int a, int b, int c, int d) {
		x1 = a;
		y1 = b;
		x2 = c;
		y2 = d;
	}
};


//sử dụng mẫu thiết kế factory để tạo object
class AbstracFactory {
public:
	CShape*  Create(int ID)
	{
		switch (ID)
		{
		case LINE:
			return new CLine;
		case RECTANGLE:
			return new CRectangle;
		case ELLIPSE:
			return new CEllipse;
		case SQUARE:
			return new CSquare;
		case CIRCLE:
			return new CCircle;
		default :  
			break;
		}
	}
};

/* Factory quản lí prorotype instances */
class ObjectFactory
{
	vector <CShape*> Prototypes;

public:
	void  initialize()
	{
		Prototypes.push_back(new CLine);
		Prototypes.push_back(new CRectangle);
		Prototypes.push_back(new CEllipse);
		Prototypes.push_back(new CCircle);
		Prototypes.push_back(new CSquare);
	}
	//void SetDataLine(int a, int b, int c, int d) {
	//	Prototypes[LINE]->SetData(a, b, c, d);
	//}
	//void SetDataRetangle(int a, int b, int c, int d) {
	//	Prototypes[RECTANGLE]->SetData(a, b, c, d);
	//}
	//void SetDataEllipse(int a, int b, int c, int d) {
	//	Prototypes[ELLIPSE]->SetData(a, b, c, d);
	//}
	//void SetDataCircle(int a, int b, int c, int d) {
	//	Prototypes[CIRCLE]->SetData(a, b, c, d);
	//}
	//void SetDataSquare(int a, int b, int c, int d) {
	//	Prototypes[SQUARE]->SetData(a, b, c, d);
	//}
	//DRAW
	void DrawLine(HDC hdc, int a, int b, int c, int d)
	{
		Prototypes[LINE]->Draw(hdc, a, b, c, d);

	}
	void DrawRetangle(HDC hdc, int a, int b, int c, int d)
	{
		Prototypes[RECTANGLE]->Draw(hdc, a, b, c, d);

	}
	void DrawEllipse(HDC hdc, int a, int b, int c, int d)
	{
		Prototypes[ELLIPSE]->Draw(hdc, a, b, c, d);

	}
	void DrawCircle(HDC hdc, int a, int b, int c, int d)
	{
		Prototypes[CIRCLE]->Draw(hdc, a, b, c, d);

	}
	void DrawSquare(HDC hdc, int a, int b, int c, int d)
	{
		Prototypes[SQUARE]->Draw(hdc, a, b, c, d);

	}
};

vector<CShape*> shapes;
//vector<CShape*> prototypes;
AbstracFactory* factory; //

CShape* currentShape;		// đối tượng đang vẽ
int isChosen = 0;

bool isDrawing = FALSE;
int currentX;
int currentY;
int lastX;
int lastY;
// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

CShape* shape;

int x;
int y;
int shift = 0;//an shift
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
    LoadStringW(hInstance, IDC_1512418, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_1512418));

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
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_1512418);
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

   HWND hWnd = CreateWindowW(szWindowClass, _T("PAINT"), WS_OVERLAPPEDWINDOW,
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
	case WM_LBUTTONDOWN:
	{
		x = GET_X_LPARAM(lParam);
		y = GET_Y_LPARAM(lParam);

		if (!isDrawing) {
			isDrawing = TRUE;
			currentX = x;
			currentY = y;
		}
			shift = GetKeyState(VK_LSHIFT);//neu bam chuot ta kiem tra shift
		
	}
		break;
	case WM_MOUSEMOVE:
	{
		x = GET_X_LPARAM(lParam);
		y = GET_Y_LPARAM(lParam);

		if (isDrawing) {
			lastX = x;
			lastY = y;
			//WCHAR buffer[200];
			////wsprintf(buffer, L"%d %d", x, y);
			//wsprintf(buffer, L"%d", shapes.size());
			//SetWindowText(hWnd, buffer);
		}
		InvalidateRect(hWnd, NULL, TRUE);
	} break;

	case WM_LBUTTONUP: {
		x = GET_X_LPARAM(lParam);
		y = GET_Y_LPARAM(lParam);
		//neu co an shift
		
		factory = new AbstracFactory;

		if (isDrawing && (isChosen == LINE)) {
			CShape* rect = factory->Create(isChosen); //su dang mau thiet ke factory de tao doi tuong

			//CLine* line = new CLine;
			rect->SetData(currentX, currentY, x, y);
			shapes.push_back(rect);
		}
		if (isDrawing && (isChosen == RECTANGLE) ) {
			if (shift & 0x8000)
			{
				CShape* rect = factory->Create(SQUARE); //su dang mau thiet ke factory de tao doi tuong

				//CSquare* rect = new CSquare;
				rect->SetData(currentX, currentY, x, (x - currentX + currentY));
				shapes.push_back(rect);
			}
			else
			{
				CShape* rect = factory->Create(RECTANGLE); //su dang mau thiet ke factory de tao doi tuong

				//CRectangle* rect = new CRectangle;
				rect->SetData(currentX, currentY, x, y);
				shapes.push_back(rect);
			}
			
		}
		if (isDrawing && (isChosen == ELLIPSE)) {
			if (shift & 0x8000)
			{
				CShape* rect = factory->Create(CIRCLE); //su dang mau thiet ke factory de tao doi tuong

				//CCircle* rect = new CCircle;
				rect->SetData(currentX, currentY, x, (x - currentX + currentY));
				shapes.push_back(rect);
			}
			else
			{
				CShape* rect = factory->Create(ELLIPSE); //su dang mau thiet ke factory de tao doi tuong

				//CEllipse* ell = new CEllipse;
				rect->SetData(currentX, currentY, x, y);
				shapes.push_back(rect);
			}
			
		}
		isDrawing = FALSE;
		shift = 0;
		InvalidateRect(hWnd, NULL, TRUE);

	}break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		HMENU hMenu = GetMenu(hWnd);
		// Parse the menu selections:
		switch (wmId)
		{
		case ID_DRAW_LINE:
			CheckMenuItem(hMenu, ID_DRAW_LINE, MF_CHECKED);
			CheckMenuItem(hMenu, ID_DRAW_RECTANGLE, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_DRAW_ELLIPSE, MF_UNCHECKED);
			isChosen = LINE;
			break;
		case ID_DRAW_RECTANGLE:
			
			CheckMenuItem(hMenu, ID_DRAW_RECTANGLE, MF_CHECKED);
			CheckMenuItem(hMenu, ID_DRAW_ELLIPSE, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_DRAW_LINE, MF_UNCHECKED);

			isChosen = RECTANGLE;

			break;
		case ID_DRAW_ELLIPSE:
			CheckMenuItem(hMenu, ID_DRAW_ELLIPSE, MF_CHECKED);
			CheckMenuItem(hMenu, ID_DRAW_RECTANGLE, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_DRAW_LINE, MF_UNCHECKED);
			isChosen = ELLIPSE;
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

		RECT rect;
		GetClientRect(hWnd, &rect);
		int width = rect.right;
		int height = rect.bottom;


		HDC hdc = BeginPaint(hWnd, &ps);
		memHDC = CreateCompatibleDC(hdc);
		HBITMAP memBitmap;
		memBitmap = CreateCompatibleBitmap(hdc, width, height);
		HBITMAP hOld = (HBITMAP)SelectObject(memHDC, memBitmap);
		int savedDC = SaveDC(memHDC);

		SelectObject(memHDC, memBitmap);
		FillRect(memHDC, &rect, HBRUSH(GetBkColor(memHDC)));
	

		for (int i = 0; i < shapes.size(); i++) {
			shapes[i]->Draw(memHDC);
		}
		
		ObjectFactory* prototype1 = new ObjectFactory();
		prototype1->initialize();
		if (isDrawing && (isChosen == LINE)) {//cho xem truoc hinh ve
			prototype1->DrawLine(memHDC, currentX, currentY, lastX, lastY);//mau prototype
			//MoveToEx(memHDC, currentX, currentY, NULL);
			//LineTo(memHDC, lastX, lastY);
		}
		if (isDrawing && (isChosen == RECTANGLE))
		{
			if (shift & 0x8000)//hinh vuong
			{
				prototype1->DrawSquare(memHDC, currentX, currentY, x, (x - currentX + currentY));//mau prototype
				//Rectangle(memHDC, currentX, currentY, x, (x - currentX + currentY));
							
			}
			else
			{
				prototype1->DrawSquare(memHDC, currentX, currentY, lastX, lastY);//mau prototype

				//Rectangle(memHDC, currentX, currentY, lastX, lastY);

			}

		}
		if (isDrawing && (isChosen == ELLIPSE)) {
			if (shift & 0x8000)
			{
				prototype1->DrawCircle(memHDC, currentX, currentY, x, (x - currentX + currentY));
				//Ellipse(memHDC, currentX, currentY, x, (x - currentX + currentY));

			}
			else
			{
				prototype1->DrawEllipse(memHDC, currentX, currentY, lastX, lastY);
				
				//Ellipse(memHDC, currentX, currentY, lastX, lastY);

			}
		}
		//BitBlt(hdc, 0, 0, width, height, hdc, 0, 0, SRCCOPY);
		SetBkMode(memHDC, TRANSPARENT);
		BitBlt(hdc, 0, 0, width, height, memHDC, 0, 0, SRCCOPY);
		RestoreDC(memHDC, savedDC);

		//FillRect(memHDC, &rect, HBRUSH(GetBkColor(memHDC)));
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_ERASEBKGND:
		return 1;
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
