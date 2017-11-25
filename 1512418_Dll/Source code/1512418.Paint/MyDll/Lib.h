#pragma once
#include "Paint.h"

#ifdef MATHLIBRARY_EXPORTS
#define MATHLIBRARY_API __declspec(dllexport) 
#else
#define MATHLIBRARY_API __declspec(dllimport) 
#endif

extern "C"
{
	MATHLIBRARY_API void DrawRect_Square(ObjectFactory* prototype1, int isChosen, int shift, bool isDrawing, int currentX, int currentY, int lastX, int lastY, HDC memHDC, Graphics* graphics);
	MATHLIBRARY_API void DrawEllipse_Circle(ObjectFactory* prototype1, int isChosen, int shift, bool isDrawing, int currentX, int currentY, int lastX, int lastY, HDC memHDC, Graphics* graphics);

	MATHLIBRARY_API void DrawRect_Square1(AbstracFactory* factory, int isChosen, int shift, bool isDrawing, int currentX, int currentY, int x, int y, vector<CShape*> &shapes);
	MATHLIBRARY_API void DrawEllipse_Circle1(AbstracFactory* factory, int isChosen, int shift, bool isDrawing, int currentX, int currentY, int x, int y, vector<CShape*> &shapes);

}