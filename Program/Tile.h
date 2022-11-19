#pragma once
#include "gfx.h"
#include "Vec2.h"
#include "Mouse.h"

class Tile
{
public:
	Tile(Vec2i boardPosition, Color color);

	void Draw(bool is3D) const;
	bool IsClicked() const;
	void MoveDown();
	void MoveLeft();
	Vec2i GetCenter() const;
	const Color GetColor() const;	
#pragma region Animations
	void MoveDownTowardsTargetRect(float speed, float dt);
	void MoveLeftTowardsTargetRect(float speed, float dt);
	void MoveTargetRectDown();
	void MoveTargetRectLeft();
	void MoveTargetRectTo(const Vec2i& pos);
	void SyncRectWithTarget();
	bool IsAtTargetRect() const;
	bool IsAtTargetX() const;
	bool IsAtTargetY() const;
#pragma endregion

public:
	static constexpr int SIZE = 25;
	static constexpr int SCORE = 8;
	static constexpr int HEIGHT_3D = SIZE / 8;
private:
	Rect rect;
	static constexpr int PADDING = 1;
	Color color;
#pragma region Animations
	Rect targetRect;
	Vec2f pos;
#pragma endregion
};

