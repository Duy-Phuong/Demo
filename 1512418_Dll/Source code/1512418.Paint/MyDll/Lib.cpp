#include "stdafx.h"
#include "Lib.h"

//2 ham ve hinh cho nguoi dung xem truoc
void DrawRect_Square(ObjectFactory* prototype1, int isChosen, int shift, bool isDrawing, int currentX, int currentY, int lastX, int lastY, HDC memHDC, Graphics* graphics)
{
	if (isDrawing && (isChosen == RECTANGLE))
	{
		if (shift & 0x8000)//hinh vuong
		{
			int width = abs(lastX - currentX);

			if (lastX > currentX && lastY > currentY)//góc 2
			{
				prototype1->DrawSquare(memHDC, currentX, currentY, width, width, graphics);//mau prototype

			}
			if (lastX < currentX && lastY < currentY)//góc 4
			{
				prototype1->DrawSquare(memHDC, lastX, lastY + (abs(lastY - currentY) - width), width, width, graphics);//mau prototype

			}
			if (lastX > currentX && lastY < currentY)//góc 1
			{
				prototype1->DrawSquare(memHDC, currentX, lastY + (abs(lastY - currentY) - width), width, width, graphics);//mau prototype

			}
			if (lastX < currentX && lastY > currentY)//góc 3
			{
				prototype1->DrawSquare(memHDC, lastX, currentY, width, width, graphics);//mau prototype

			}
		}
		else
		{
			//x, y, dài, rộng
			if (lastX > currentX && lastY > currentY)//góc 2
			{
				prototype1->DrawRetangle(memHDC, currentX, currentY, abs(lastX - currentX), abs(lastY - currentY), graphics);//mau prototype

			}
			if (lastX < currentX && lastY < currentY)//góc 4
			{
				prototype1->DrawRetangle(memHDC, lastX, lastY, abs(lastX - currentX), abs(lastY - currentY), graphics);//mau prototype

			}
			if (lastX > currentX && lastY < currentY)//góc 1
			{
				prototype1->DrawRetangle(memHDC, currentX, lastY, abs(lastX - currentX), abs(lastY - currentY), graphics);//mau prototype

			}
			if (lastX < currentX && lastY > currentY)//góc 3
			{
				prototype1->DrawRetangle(memHDC, lastX, currentY, abs(lastX - currentX), abs(lastY - currentY), graphics);//mau prototype

			}

		}

	}
}

void DrawEllipse_Circle(ObjectFactory* prototype1, int isChosen, int shift, bool isDrawing, int currentX, int currentY, int lastX, int lastY, HDC memHDC, Graphics* graphics)
{
	if (isDrawing && (isChosen == ELLIPSE)) {
		if (shift & 0x8000)
		{
			int width1 = abs(lastX - currentX);
			if (lastX > currentX && lastY > currentY)//góc 2
			{
				prototype1->DrawCircle(memHDC, currentX, currentY, width1, width1, graphics);//mau prototype

			}
			if (lastX < currentX && lastY < currentY)//góc 4
			{
				prototype1->DrawCircle(memHDC, lastX, lastY + (abs(lastY - currentY) - width1), width1, width1, graphics);//mau prototype

			}
			if (lastX > currentX && lastY < currentY)//góc 1
			{
				prototype1->DrawCircle(memHDC, currentX, lastY + (abs(lastY - currentY) - width1), width1, width1, graphics);//mau prototype

			}
			if (lastX < currentX && lastY > currentY)//góc 3
			{
				prototype1->DrawCircle(memHDC, lastX, currentY, width1, width1, graphics);//mau prototype

			}
		}
		else
		{
			if (lastX > currentX && lastY > currentY)//góc 2
			{
				prototype1->DrawEllipse(memHDC, currentX, currentY, abs(lastX - currentX), abs(lastY - currentY), graphics);//mau prototype

			}
			if (lastX < currentX && lastY < currentY)//góc 4
			{
				prototype1->DrawEllipse(memHDC, lastX, lastY, abs(lastX - currentX), abs(lastY - currentY), graphics);//mau prototype

			}
			if (lastX > currentX && lastY < currentY)//góc 1
			{
				prototype1->DrawEllipse(memHDC, currentX, lastY, abs(lastX - currentX), abs(lastY - currentY), graphics);//mau prototype

			}
			if (lastX < currentX && lastY > currentY)//góc 3
			{
				prototype1->DrawEllipse(memHDC, lastX, currentY, abs(lastX - currentX), abs(lastY - currentY), graphics);//mau prototype

			}

		}
	}
}

//2 hàm vẽ khi nhả chuột

void DrawRect_Square1(AbstracFactory* factory, int isChosen, int shift, bool isDrawing, int currentX, int currentY, int x, int y, vector<CShape*> &shapes)
{
	if (isDrawing && (isChosen == RECTANGLE)) {
		if (shift & 0x8000)
		{
			CShape* rect = factory->Create(SQUARE); //su dang mau thiet ke factory de tao doi tuong
			int l = abs(x - currentX);
			if (x > currentX && y > currentY)//góc 2
			{
				rect->SetData(currentX, currentY, l, l);

			}
			if (x < currentX && y < currentY)//góc 4
			{
				rect->SetData(x, y + (abs(y - currentY) - l), l, l); //phai cong them 1 khoang de khi width = l thi ve hinh ra goc duoi se k change

			}
			if (x > currentX && y < currentY)//góc 1
			{
				rect->SetData(currentX, y + (abs(y - currentY) - l), l, l);
			}
			if (x < currentX && y > currentY)//góc 3
			{
				rect->SetData(x, currentY, l, l);
			}
			shapes.push_back(rect);
		}
		else
		{
			CShape* rect = factory->Create(RECTANGLE); //su dang mau thiet ke factory de tao doi tuong
			if (x > currentX && y > currentY)//góc 2
			{
				rect->SetData(currentX, currentY, abs(x - currentX), abs(y - currentY));

			}
			if (x < currentX && y < currentY)//góc 4
			{
				rect->SetData(x, y, abs(x - currentX), abs(y - currentY));

			}
			if (x > currentX && y < currentY)//góc 1
			{
				rect->SetData(currentX, y, abs(x - currentX), abs(y - currentY));
			}
			if (x < currentX && y > currentY)//góc 3
			{
				rect->SetData(x, currentY, abs(x - currentX), abs(y - currentY));
			}
			shapes.push_back(rect);
		}

	}
}

void DrawEllipse_Circle1(AbstracFactory* factory, int isChosen, int shift, bool isDrawing, int currentX, int currentY, int x, int y, vector<CShape*> &shapes)
{
	if (isDrawing && (isChosen == ELLIPSE)) {
		if (shift & 0x8000)
		{
			CShape* rect = factory->Create(CIRCLE); //su dang mau thiet ke factory de tao doi tuong
			int length1 = 0;
			length1 = abs(x - currentX);
			if (x > currentX && y > currentY)//góc 2
			{
				rect->SetData(currentX, currentY, length1, length1);

			}
			if (x < currentX && y < currentY)//góc 4
			{
				rect->SetData(x, y + (abs(y - currentY) - length1), length1, length1);

			}
			if (x > currentX && y < currentY)//góc 1
			{
				rect->SetData(currentX, y + (abs(y - currentY) - length1), length1, length1);
			}
			if (x < currentX && y > currentY)//góc 3
			{
				rect->SetData(x, currentY, length1, length1);
			}
			shapes.push_back(rect);
		}
		else
		{
			CShape* rect = factory->Create(ELLIPSE); //su dang mau thiet ke factory de tao doi tuong

			if (x > currentX && y > currentY)//góc 2
			{
				rect->SetData(currentX, currentY, abs(x - currentX), abs(y - currentY));

			}
			if (x < currentX && y < currentY)//góc 4
			{
				rect->SetData(x, y, abs(x - currentX), abs(y - currentY));

			}
			if (x > currentX && y < currentY)//góc 1
			{
				rect->SetData(currentX, y, abs(x - currentX), abs(y - currentY));
			}
			if (x < currentX && y > currentY)//góc 3
			{
				rect->SetData(x, currentY, abs(x - currentX), abs(y - currentY));
			}
			shapes.push_back(rect);
		}

	}
}