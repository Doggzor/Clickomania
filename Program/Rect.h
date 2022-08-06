#pragma once
#include "Vector2i.h"
struct Rect
{
	Rect() : x(0), y(0), width(0), height(0) {}
	Rect(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {}

	int x, y, width, height;

	bool IsContainingPoint(Vector2i pt) {
		return pt.x >= x && pt.x <= x + width && pt.y >= y && pt.y <= y + height;
	}

};