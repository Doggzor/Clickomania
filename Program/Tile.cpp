#include "Tile.h"

Tile::Tile(Vector2i location, Color color)
	:
	location(location),
	color(color)
{
}

void Tile::Draw(Vector2i topleftOffset)
{
	gfx::DrawRect(topleftOffset + location * SIZE, SIZE, SIZE, color);
}
