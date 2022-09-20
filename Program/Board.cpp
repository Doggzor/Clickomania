#include "Board.h"

Board::Board(int columns, int rows)
	:
	columns(columns),
	rows(rows)
{
	tiles.reserve(rows * columns);
	for (int y = 0; y < rows; ++y) {
		for (int x = 0; x < columns; ++x) {
			tiles.emplace_back(std::make_unique<Tile>(Vector2i(x, y), RandomColor()));
		}
	}
}

void Board::Draw()
{
	Vector2i offset = {
		(int)( (float)gfx::ScreenWidth * 0.5f - (float)columns * 0.5f * (float)Tile::SIZE ),
		(int)( (float)gfx::ScreenHeight * 0.5f - (float)rows * 0.5f * (float)Tile::SIZE )
	};
	for (int i = 0; i < (int)tiles.size(); ++i) {
		tiles[i]->Draw(offset);
	}
}

Color Board::RandomColor()
{
	return Color(TILE_COLORS[Random::Int(0, MAX_COLORS - 1)]);
}
