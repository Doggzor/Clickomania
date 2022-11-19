#pragma once
#include "Vec2.h"
struct Rect
{
	constexpr Rect() : x(0), y(0), width(0), height(0) {}
	constexpr Rect(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {}

	int x, y, width, height;

	bool operator==(const Rect& other) const {
		return x == other.x && y == other.y && width == other.width && height == other.height;
	}

	void operator=(const Rect& other) {
		x = other.x;
		y = other.y;
		width = other.width;
		height = other.height;
	}

	template<typename T>
	bool Contains(Vec2<T> pt) const {
		return (int)pt.x >= x && (int)pt.x <= x + width && (int)pt.y >= y && (int)pt.y <= y + height;
	}

	void Resize(int nPixels) {
		x -= nPixels;
		y -= nPixels;
		width += nPixels * 2;
		height += nPixels * 2;
	}

	Rect Resized(int nPixels) const {
		Rect resized = *this;
		resized.Resize(nPixels);
		return resized;
	}

	void Move(int xPixels, int yPixels) {
		x += xPixels;
		y += yPixels;
	}

	Vec2i GetCenter() const {
		return { x + width / 2, y + height / 2 };
	}
};