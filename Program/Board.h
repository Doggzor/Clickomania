#pragma once
#include <vector>
#include <memory>
#include "gfx.h"
#include "Tile.h"
#include "Random.h"
#include "Particles.h"
#include <string>

class Board
{
public:
	struct Settings {
		Settings(int columns, int rows, int colors, bool particles = true, bool is3D = true, int animSpeed = 2)
			:
			columns(columns), rows(rows), colors(colors),
			areParticlesEnabled(particles), areAnimationEnabled(animSpeed % 4), is3D(is3D),
			animSpeedMultiplier(animSpeed % 4)
		{}
		int columns, rows, colors;
		bool areParticlesEnabled, areAnimationEnabled, is3D;
		int animSpeedMultiplier;
	};
public:
	Board(const Settings& settings);
	Board(int columns, int rows, int colors);

	void Draw() const;
	void Update(float dt);
	void AnimateTiles(float dt);
	void UpdateParticles(float dt);
	bool GetValidMoves() const;
	bool ShouldAnimate() const;
	void ChangeAnimationSpeed();
	//Turn particle effects ON and OFF
	void SwitchParticles();
	void Switch3DView();
	std::string GetAnimSpeedString() const;
	std::string GetParticlesEnabledString() const;
	std::string GetViewString() const; //Is the board in 2D or 3D mode
	int GetScore() const;
	const Settings& GetSettings() const;
	

private:
	void DestroyTile(const Vec2i& boardPos);
	bool CheckColor(const Vec2i& boardPos, const Color& color) const;
	/// <summary>
	/// Compares the colors of the neighboring tiles (excluding diagonal tiles) and the tile at "boardPos"
	/// </summary>
	/// <param name="boardPos">: Board position of the tile whose neighbors to check</param>
	/// <returns>True if any of the checked tiles is the same color as the tile at "boardPos"</returns>
	bool CheckNeighborColors(const Vec2i& boardPos) const;
	/// <summary>
	/// Destroys all neighboring tiles (excluding diagonal tiles) that share the same color as the tile at "boardPos"
	/// </summary>
	/// <param name="boardPos">: Board position of the tile whose neighbors to destroy</param>
	/// <param name="tileColor">: Color of the tiles that are to be destroyed</param>
	void DestroyNeighborTiles(const Vec2i& boardPos, const Color tileColor);
	void UpdateTilePositions();
	/// <summary>
	/// Moves all tiles above "boardPos" one tile down
	/// </summary>
	/// <param name="boardPos">: Indicates where should the tiles be moved</param>
	void MoveAllAboveTiles(const Vec2i& boardPos);
	/// <summary>
	/// Moves the columns to the left
	/// </summary>
	/// <param name="firstColumnIndex">: Index of the first column to be moved,
	/// all columns to the right will be moved as well</param>
	void MoveAllColumnsToTheLeft(int firstColumnIndex);
	//Returns true if there are still valid moves, false otherwise
	bool CheckForValidMoves() const;
	void DrawParticles() const;
	Color RandomColor(int nColors);
private:
	std::vector< std::vector < std::unique_ptr <Tile> > > tiles;
	std::vector < std::unique_ptr <Particles> > particles;
	Rect borderRect;
	static constexpr int BORDER_THICKNESS = 5;
	float score = 0;
	bool validMoves = true;
	static constexpr Color TILE_COLORS[6] = {
		Colors::BLUE,
		Colors::GREEN,
		Colors::RED,
		Colors::YELLOW,
		Colors::ORANGE,
		Colors::MAGENTA
	};
	Settings settings;
#pragma region Animations
	bool isMovingDown = false, isMovingLeft = false;
	float animSpeed = 100.0f;
#pragma endregion
};

