// 1512418Paint.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

#include "1512418Paint.h"
#include "RibbonFramework.h"
#include "RibbonIDs.h"
#include <Objbase.h>
#pragma comment(lib, "Ole32.lib")
#include "CommandHandler.h"
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "ComCtl32.lib")
#define MAX_LOADSTRING 100
//thu vien graphic
#include <objidl.h>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")
using namespace Gdiplus;
GdiplusStartupInput gdiplusStartupInput;
ULONG_PTR           gdiplusToken;
Graphics* graphics;

int isChosen = 0;

class CShape {
public:
	virtual void Draw(HDC hdc, Graphics* graphics) = 0;
	virtual void Draw(HDC hdc, int a, int b, int c, int d, Graphics* graphics) = 0;//ve co xem truoc
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
	void Draw(HDC hdc, Graphics* graphics) {
		
		graphics = new Graphics(hdc);
		int lineWidth = 1;
		Pen* pen = new Pen(Color(255, 0, 0, 0), lineWidth);

		graphics->DrawLine(pen, x1, y1, x2, y2);
	}
	void Draw(HDC hdc, int a, int b, int c, int d, Graphics* graphics) {
		
		graphics = new Graphics(hdc);
		int lineWidth = 1;
		Pen* pen = new Pen(Color(255, 0, 0, 0), lineWidth);

		graphics->DrawLine(pen, a, b, c, d);

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
	void Draw(HDC hdc, Graphics* graphics) {
		graphics = new Graphics(hdc);
		int lineWidth = 1;
		Pen* pen = new Pen(Color(255, 0, 0, 0), lineWidth);

		graphics->DrawRectangle(pen, x1, y1, x2, y2);
	}
	void Draw(HDC hdc, int a, int b, int c, int d, Graphics* graphics) {
		graphics = new Graphics(hdc);
		int lineWidth = 1;
		Pen* pen = new Pen(Color(255, 0, 0, 0), lineWidth);
		
		graphics->DrawRectangle(pen, a, b, c, d);

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
	void Draw(HDC hdc, Graphics* graphics) {
		graphics = new Graphics(hdc);
		int lineWidth = 1;
		Pen* pen = new Pen(Color(255, 0, 0, 0), lineWidth);

		graphics->DrawEllipse(pen, x1, y1, x2, y2);

	}
	void Draw(HDC hdc, int a, int b, int c, int d, Graphics* graphics) {
		graphics = new Graphics(hdc);
		int lineWidth = 1;
		Pen* pen = new Pen(Color(255, 0, 0, 0), lineWidth);
		graphics->DrawEllipse(pen, a, b, c, d);

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
	void Draw(HDC hdc, Graphics* graphics) {
		graphics = new Graphics(hdc);
		int lineWidth = 1;
		Pen* pen = new Pen(Color(255, 0, 0, 0), lineWidth);

		graphics->DrawRectangle(pen, x1, y1, x2, y2);
	}
	void Draw(HDC hdc, int a, int b, int c, int d, Graphics* graphics) {
		graphics = new Graphics(hdc);
		int lineWidth = 1;
		Pen* pen = new Pen(Color(255, 0, 0, 0), lineWidth);

		graphics->DrawRectangle(pen, a, b, c, d);
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
	void Draw(HDC hdc, Graphics* graphics) {
		graphics = new Graphics(hdc);
		int lineWidth = 1;
		Pen* pen = new Pen(Color(255, 0, 0, 0), lineWidth);

		graphics->DrawEllipse(pen, x1, y1, x2, y2);
	}
	void Draw(HDC hdc, int a, int b, int c, int d, Graphics* graphics) {
		graphics = new Graphics(hdc);
		int lineWidth = 1;
		Pen* pen = new Pen(Color(255, 0, 0, 0), lineWidth);
		graphics->DrawEllipse(pen, a, b, c, d);
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
		default:
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
	//DRAW
	void DrawLine(HDC hdc, int a, int b, int c, int d, Graphics* graphics)
	{
		Prototypes[LINE]->Draw(hdc, a, b, c, d, graphics);

	}
	void DrawRetangle(HDC hdc, int a, int b, int c, int d, Graphics* graphics)
	{
		Prototypes[RECTANGLE]->Draw(hdc, a, b, c, d, graphics);

	}
	void DrawEllipse(HDC hdc, int a, int b, int c, int d, Graphics* graphics)
	{
		Prototypes[ELLIPSE]->Draw(hdc, a, b, c, d, graphics);

	}
	void DrawCircle(HDC hdc, int a, int b, int c, int d, Graphics* graphics)
	{
		Prototypes[CIRCLE]->Draw(hdc, a, b, c, d, graphics);

	}
	void DrawSquare(HDC hdc, int a, int b, int c, int d, Graphics* graphics)
	{
		Prototypes[SQUARE]->Draw(hdc, a, b, c, d, graphics);

	}
};

vector<int> vx1;
vector<int> vy1;
vector<int> vx2;
vector<int> vy2;
vector<int> types;
bool isDrawing = FALSE;
int currentX;
int currentY;
int lastX;
int lastY;

HDC memHDC;
HDC hdc1;
int x;
int y;
int shift = 0;//an shift
CShape* shape;
vector<CShape*> shapes;
AbstracFactory* factory; //

CShape* currentShape;		// đối tượng đang vẽ

// ----------------------------------- dll -----------------------------------------------
typedef void(__cdecl *MYPROC)(ObjectFactory*, int, int, bool, int, int, int, int, HDC, Graphics*);
HINSTANCE hinstLib;
MYPROC ProcAdd;

typedef void(__cdecl *MYPROC1)(AbstracFactory*, int, int, bool, int, int, int, int, vector<CShape*> &a);
MYPROC1 ProcAdd1;

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
	CoInitialize(NULL);

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_1512418PAINT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_1512418PAINT));

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

	CoUninitialize();
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
	wcex.style = 0; //CS_HREDRAW | CS_VREDRAW;
    //wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_1512418PAINT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_1512418PAINT);
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

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
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
		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);


		InitializeFramework(hWnd);
		break;
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

			rect->SetData(currentX, currentY, x, y);
			shapes.push_back(rect);
		}

		/*DrawRect_Square( factory, isChosen, shift, isDrawing, currentX, currentY, x, y, shapes);

		DrawEllipse_Circle( factory, isChosen, shift, isDrawing, currentX, currentY, x, y, shapes);*/

		//load dll
		hinstLib = LoadLibrary(L"MyDLL.dll");
		if (hinstLib) {
			ProcAdd1 = (MYPROC1)GetProcAddress(hinstLib, "DrawRect_Square1");
			if (ProcAdd1 != NULL) {
				ProcAdd1(factory, isChosen, shift, isDrawing, currentX, currentY, x, y, shapes);
			}
			ProcAdd1 = (MYPROC1)GetProcAddress(hinstLib, "DrawEllipse_Circle1");
			if (ProcAdd1 != NULL) {
				ProcAdd1(factory, isChosen, shift, isDrawing, currentX, currentY, x, y, shapes);
			}
		}
		isDrawing = FALSE;
		shift = 0;
		InvalidateRect(hWnd, NULL, TRUE);

	}break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
			
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
		HDC hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rect);
		int width = rect.right + 100;
		int height = rect.bottom;
		rect.top += GetRibbonHeight();

		
		memHDC = CreateCompatibleDC(hdc);
		HBITMAP memBitmap;
		memBitmap = CreateCompatibleBitmap(hdc, width, height);
		HANDLE hOld = SelectObject(memHDC, memBitmap);
		int savedDC = SaveDC(memHDC);

		
		FillRect(memHDC, &rect, HBRUSH(GetBkColor(memHDC)));

		for (int i = 0; i < shapes.size(); i++) {
			shapes[i]->Draw(memHDC, graphics);
		}

		ObjectFactory* prototype1 = new ObjectFactory();
		prototype1->initialize();
		if (isDrawing && (isChosen == LINE)) {//cho xem truoc hinh ve
			prototype1->DrawLine(memHDC, currentX, currentY, lastX, lastY, graphics);//mau prototype
		}
	
		//DrawRect_Square(prototype1, isChosen, shift, isDrawing, currentX, currentY, lastX, lastY, memHDC, graphics);

		//DrawEllipse_Circle(prototype1, isChosen, shift, isDrawing, currentX, currentY, lastX, lastY, memHDC, graphics);

		//--------------------------------------------------------------------------------------------------------------
		//load dll
		hinstLib = LoadLibrary(L"MyDLL.dll");
		if (hinstLib) {
			ProcAdd = (MYPROC)GetProcAddress(hinstLib, "DrawRect_Square");
			if (ProcAdd != NULL) {
				ProcAdd(prototype1, isChosen, shift, isDrawing, currentX, currentY, lastX, lastY, memHDC, graphics);
			}
			ProcAdd = (MYPROC)GetProcAddress(hinstLib, "DrawEllipse_Circle");
			if (ProcAdd != NULL) {
				ProcAdd(prototype1, isChosen, shift, isDrawing, currentX, currentY, lastX, lastY, memHDC, graphics);
			}
		}
		

		SetBkMode(memHDC, TRANSPARENT);
		BitBlt(hdc, 0, 0, rect.right + 100, rect.bottom, memHDC, 0, 0, SRCCOPY);
		
		SelectObject(memHDC, memBitmap);

		
		//delete pen;
		delete graphics;
		EndPaint(hWnd, &ps);
        }
        break;
	case WM_ERASEBKGND:
		return 1;
    case WM_DESTROY:
		DestroyFramework();

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


