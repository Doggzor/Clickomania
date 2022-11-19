#include "Board.h"

Board::Board(const Settings& settings)
	:
	settings(settings)
{
	Vec2i offset = gfx::ScreenCenter - Vec2i(settings.columns, settings.rows) / 2 * Tile::SIZE;
	borderRect = Rect(
		offset.x - BORDER_THICKNESS,
		offset.y - BORDER_THICKNESS,
		settings.columns * Tile::SIZE + 2 * BORDER_THICKNESS,
		settings.rows * Tile::SIZE + 2 * BORDER_THICKNESS);
	tiles.resize(settings.rows);
	//GAVE UP ON ANIMATED BOARD INITIALIZATION
	//if (settings.areAnimationEnabled) {
	//	const int smth = borderRect.y + borderRect.height + settings.rows * (Tile::SIZE + 10);
	//	for (int y = 0; y < settings.rows; ++y) {
	//		tiles[y].reserve(settings.columns);
	//		for (int x = 0; x < settings.columns; ++x) {
	//			const Vec2i xy = Vec2i(x, y) * Tile::SIZE;
	//			tiles[y].emplace_back(std::make_unique<Tile>(offset + xy - Vec2i(0, smth + (x - y) * (Tile::SIZE + 10)), RandomColor(settings.colors)));
	//			tiles[y][x]->MoveTargetRectTo(offset + xy);
	//			isMovingDown = true;
	//		}
	//	}
	//}
	for (int y = 0; y < settings.rows; ++y) {
		tiles[y].reserve(settings.columns);
		for (int x = 0; x < settings.columns; ++x) {
			tiles[y].emplace_back(std::make_unique<Tile>(offset + Vec2i(x, y) * Tile::SIZE, RandomColor(settings.colors)));
		}
	}
	validMoves = CheckForValidMoves();
}

Board::Board(int columns, int rows, int colors)
	:
	Board(Settings(columns, rows, colors))
{
}
void Board::Draw() const
{
	if (settings.is3D)
		gfx::DrawRectEmpty3D(borderRect.Resized(BORDER_THICKNESS), BORDER_THICKNESS * 2, BORDER_THICKNESS, Colors::GRAY);
	else
		gfx::DrawRectEmpty(borderRect, BORDER_THICKNESS, Colors::GRAY);

	for (int y = 0; y < settings.rows; ++y) {
		for (int x = 0; x < settings.columns; ++x) {
			if (tiles[y][x]) {
				tiles[y][x]->Draw(settings.is3D);
			}
		}
	}

	DrawParticles();
}

void Board::Update(float dt)
{
	if (ShouldAnimate()) {
		AnimateTiles(dt);
	}
	else if (Mouse::IsInputEnabled()) {
		score -= dt;
		if (Mouse::IsLButtonPressed()) {
			Vec2i currentTilePos;
			Color currentTileColor;
			for (int y = 0; y < settings.rows; ++y) {
				for (int x = 0; x < settings.columns; ++x) {
					currentTilePos = Vec2i(x, y);
					if (tiles[y][x] && tiles[y][x]->IsClicked() && CheckNeighborColors(currentTilePos)) {
						currentTileColor = tiles[y][x]->GetColor();
						DestroyTile(currentTilePos);
						DestroyNeighborTiles(currentTilePos, currentTileColor);
						UpdateTilePositions();
						validMoves = CheckForValidMoves();
					}
				}
			}
		}
	}
}

void Board::AnimateTiles(float dt)
{
	const float realAnimSpeed = animSpeed * (float)settings.animSpeedMultiplier;
	if (isMovingDown) {
		isMovingDown = false;
		for (int y = 0; y < settings.rows; ++y) {
			for (int x = 0; x < settings.columns; ++x) {
				if (tiles[y][x] && !tiles[y][x]->IsAtTargetY()) {
					tiles[y][x]->MoveDownTowardsTargetRect(realAnimSpeed , dt);
					isMovingDown = true;
				}
			}
		}
	}

	if (!isMovingDown && isMovingLeft) {
		isMovingLeft = false;
		for (int y = 0; y < settings.rows; ++y) {
			for (int x = 0; x < settings.columns; ++x) {
				if (tiles[y][x] && !tiles[y][x]->IsAtTargetX()) {
					tiles[y][x]->MoveLeftTowardsTargetRect(realAnimSpeed, dt);
					isMovingLeft = true;
				}
			}
		}
	}

	//Safety measure in case animations are turned off mid animation
	if (!settings.areAnimationEnabled) {
		for (int y = 0; y < settings.rows; ++y) {
			for (int x = 0; x < settings.columns; ++x) {
				if (tiles[y][x] && !tiles[y][x]->IsAtTargetRect()) {
					tiles[y][x]->SyncRectWithTarget();
					isMovingDown = false;
					isMovingLeft = false;
				}
			}
		}
	}
}

bool Board::GetValidMoves() const
{
	return validMoves;
}

bool Board::ShouldAnimate() const
{
	return isMovingDown || isMovingLeft;
}

void Board::ChangeAnimationSpeed()
{
	++settings.animSpeedMultiplier %= 4;
	settings.areAnimationEnabled = settings.animSpeedMultiplier;
}

void Board::SwitchParticles()
{
	settings.areParticlesEnabled = !settings.areParticlesEnabled;
}

void Board::Switch3DView()
{
	settings.is3D = !settings.is3D;
}

std::string Board::GetAnimSpeedString() const
{
	std::string base = "AnimSpeed: ";
	std::string appendix = settings.animSpeedMultiplier ? std::to_string(settings.animSpeedMultiplier) + "  " : "OFF";
	return base + appendix;
}

std::string Board::GetParticlesEnabledString() const
{
	std::string base = "Particles: ";
	std::string appendix = settings.areParticlesEnabled ? "ON " : "OFF";
	return base + appendix;
}

std::string Board::GetViewString() const
{
	std::string base = "View: ";
	std::string appendix = settings.is3D ? "3D" : "2D";
	return base + appendix;
}

bool Board::CheckForValidMoves() const
{
	Vec2i currentTilePos;
	for (int x = 0; x < settings.columns; ++x) {
		for (int y = 0; y < settings.rows; ++y) {
			currentTilePos = Vec2i(x, y);
			if (CheckNeighborColors(currentTilePos))
				return true; //There are still valid moves a player can make
		}
	}
	return false; //There are no more valid moves on the board
}

void Board::UpdateParticles(float dt)
{
	for (auto it = particles.begin(), end = particles.end(); it != end; ) {
		it->get()->Update(dt);
		if (it->get()->Expired()) {
			it = particles.erase(it);
			end = particles.end();
		}
		else
			++it;
	}
}

void Board::DrawParticles() const
{
	for (const auto& p : particles) {
		p->Draw();
	}
}

int Board::GetScore() const
{
	return (int)score;
}

const Board::Settings& Board::GetSettings() const
{
	return settings;
}

void Board::DestroyTile(const Vec2i& boardPos)
{
	if (tiles[boardPos.y][boardPos.x]) {
		if (settings.areParticlesEnabled) {
			particles.emplace_back(std::make_unique<Particles>(tiles[boardPos.y][boardPos.x]->GetCenter(), 80, tiles[boardPos.y][boardPos.x]->GetColor()));
		}
		tiles[boardPos.y][boardPos.x].reset();
		score += Tile::SCORE;
	}
}

bool Board::CheckColor(const Vec2i& boardPos, const Color& color) const
{
	return tiles[boardPos.y][boardPos.x] && tiles[boardPos.y][boardPos.x]->GetColor() == color;
}

bool Board::CheckNeighborColors(const Vec2i& boardPos) const
{
	if (!tiles[boardPos.y][boardPos.x]) return false;
	Color color = tiles[boardPos.y][boardPos.x]->GetColor();
	return (boardPos.x > 0 && CheckColor(Vec2i(boardPos.x - 1, boardPos.y), color))
		|| (boardPos.x < settings.columns - 1 && CheckColor(Vec2i(boardPos.x + 1, boardPos.y), color))
		|| (boardPos.y > 0 && CheckColor(Vec2i(boardPos.x, boardPos.y - 1), color))
		|| (boardPos.y < settings.rows - 1 && CheckColor(Vec2i(boardPos.x, boardPos.y + 1), color));
}

void Board::DestroyNeighborTiles(const Vec2i& boardPos, const Color tileColor)
{
	Vec2i currentTilePos = Vec2i(boardPos.x - 1, boardPos.y);
	//Left
	if (boardPos.x > 0 && CheckColor(currentTilePos, tileColor)) {
		DestroyTile(currentTilePos);
		DestroyNeighborTiles(currentTilePos, tileColor);
	}
	//Right
	currentTilePos = Vec2i(boardPos.x + 1, boardPos.y);
	if (boardPos.x < settings.columns - 1 && CheckColor(currentTilePos, tileColor)) {
		DestroyTile(currentTilePos);
		DestroyNeighborTiles(currentTilePos, tileColor);
	}
	//Up
	currentTilePos = Vec2i(boardPos.x, boardPos.y - 1);
	if (boardPos.y > 0 && CheckColor(currentTilePos, tileColor)) {
		DestroyTile(currentTilePos);
		DestroyNeighborTiles(currentTilePos, tileColor);
	}
	//Down
	currentTilePos = Vec2i(boardPos.x, boardPos.y + 1);
	if (boardPos.y < settings.rows - 1 && CheckColor(currentTilePos, tileColor)) {
		DestroyTile(currentTilePos);
		DestroyNeighborTiles(currentTilePos, tileColor);
	}
}

void Board::UpdateTilePositions()
{
	//Moving tile down
	bool flag = false;
	for (int x = 0; x < settings.columns; ++x) {
		flag = false;
		for (int y = 0; y < settings.rows; ++y) {
			if (tiles[y][x]) flag = true;
			else if (flag) {
				MoveAllAboveTiles(Vec2i(x, y));
			}
		}
	}
	//Moving columns to the left
	flag = false;
	for (int x = settings.columns - 1; x >= 0; --x) {
		if (tiles[settings.rows - 1][x]) flag = true;
		else if (flag) {
			MoveAllColumnsToTheLeft(x + 1);
		}
	}
}

void Board::MoveAllAboveTiles(const Vec2i& boardPos)
{
	for (int y = boardPos.y; y > 0; --y) {
		//Break out if there are no more tiles above this position
		if (!tiles[y - 1][boardPos.x]) break;
		tiles[y][boardPos.x] = std::move(tiles[y - 1][boardPos.x]);
		tiles[y][boardPos.x]->MoveTargetRectDown();
		if (settings.areAnimationEnabled) isMovingDown = true;
		else tiles[y][boardPos.x]->MoveDown();
	}
}

void Board::MoveAllColumnsToTheLeft(int columnIndex)
{
	for (int x = columnIndex; x < settings.columns; ++x) {
		for (int y = settings.rows - 1; y >= 0; --y) {
			//Break out if there are no more tiles in the current column
			if (!tiles[y][x]) break;
			tiles[y][x - 1] = std::move(tiles[y][x]);
			tiles[y][x - 1]->MoveTargetRectLeft();
			if (settings.areAnimationEnabled) isMovingLeft = true;
			else tiles[y][x - 1]->MoveLeft();
		}
	}
}

Color Board::RandomColor(int nColors)
{
	return Color(TILE_COLORS[Random::Int(0, nColors - 1)]);
}
