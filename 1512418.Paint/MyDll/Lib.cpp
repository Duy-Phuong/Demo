#include "stdafx.h"
#include "Lib.h"

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