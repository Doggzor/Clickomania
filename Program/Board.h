#pragma once
#include <vector>
#include <memory>
#include "gfx.h"
#include "Tile.h"

class Board
{
public:
	Board(int columns, int rows);

	void Draw();
private:
	std::vector< std::unique_ptr <Tile> > tiles;
	static constexpr int padding = 1;
	static constexpr Color tileColors[5] = {
		Colors::BLUE,
		Colors::GREEN,
		Colors::RED,
		Colors::YELLOW,
		Colors::ORANGE
	};
};

