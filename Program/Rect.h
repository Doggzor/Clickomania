#pragma once
#include "Vector2i.h"
struct Rect
{
	Rect() : x(0), y(0), width(0), height(0) {}
	Rect(float x, float y, float width, float height) : x(x), y(y), width(width), height(height) {}

	float x, y, width, height;

	bool Contains(Vector2i pt) {
		return (float)pt.x >= x && (float)pt.x <= x + width && (float)pt.y >= y && (float)pt.y <= y + height;
	}

};