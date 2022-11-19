#pragma once
#include <string>
#include "Rect.h"
struct Color;

class Sprite
{
public:
	Sprite() = default;
	Sprite(const std::string& filename);
	Sprite(int width, int height);
	~Sprite();
	Sprite(const Sprite&);
	Sprite& operator=(const Sprite&);
	Color& GetPixel(int x, int y) const;
	int GetWidth() const;
	int GetHeight() const;
	void SetPixel(int x, int y, Color c);
private:

private:
	int width = 0, height = 0;
	Color* pixels = nullptr;
};

