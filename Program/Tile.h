#pragma once
#include "gfx.h"
#include "Vector2i.h"

class Tile
{
public:
	Tile(Vector2i location, Color color);

	void Draw(Vector2i topleftOffset);

public:
	static constexpr int SIZE = 25;
private:
	Vector2i location;
	Color color;
};

