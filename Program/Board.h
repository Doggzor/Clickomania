#pragma once
#include <vector>
#include <memory>
#include "gfx.h"
#include "Tile.h"
#include "Random.h"

class Board
{
public:
	Board(int columns, int rows);

	void Draw();

private:
	Color RandomColor();
private:
	std::vector< std::unique_ptr <Tile> > tiles;
	int columns, rows;
	static constexpr int PADDING = 1;
	static constexpr int MAX_COLORS = 5;
	static constexpr Color TILE_COLORS[MAX_COLORS] = {
		Colors::BLUE,
		Colors::GREEN,
		Colors::RED,
		Colors::YELLOW,
		Colors::ORANGE
	};
};

