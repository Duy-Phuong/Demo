#pragma once
#include <windowsx.h>
#include <windows.h>
#include <iostream>
#include <vector>
using namespace std;


#define LINE 0
#define RECTANGLE 1
#define CIRCLE 2
#define ELLIPSE 3
#define SQUARE 4

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
