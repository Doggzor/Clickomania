#include "Tile.h"

Tile::Tile(Vec2i boardPosition, Color color)
	:
	color(color)
{
	rect = Rect(boardPosition.x, boardPosition.y, SIZE, SIZE);
	targetRect = rect;
	pos = Vec2f(boardPosition);
}

void Tile::Draw(bool is3D) const
{
	is3D ? gfx::DrawRect3D(rect, HEIGHT_3D, color) : gfx::DrawRect(rect.Resized(-PADDING), color);
}

bool Tile::IsClicked() const
{
	return Mouse::IsLButtonPressed() && rect.Contains(Mouse::GetMousePos());
}

void Tile::MoveDown()
{
	rect.Move(0, SIZE);
	pos.y = (float)rect.y;
}

void Tile::MoveLeft()
{
	rect.Move(-SIZE, 0);
	pos.x = (float)rect.x;
}

Vec2i Tile::GetCenter() const
{
	return rect.GetCenter();
}

const Color Tile::GetColor() const
{
	return color;
}

void Tile::MoveDownTowardsTargetRect(float speed, float dt)
{
	if (rect.y < targetRect.y) {
		pos.y += speed * dt;
		rect.y = (int)pos.y;
	}
	else {
		pos.y = (float)targetRect.y;
		rect.y = targetRect.y;
	}
}

void Tile::MoveLeftTowardsTargetRect(float speed, float dt)
{
	if (rect.x > targetRect.x) {
		pos.x -= speed * dt;
		rect.x = (int)pos.x;
	}
	else {
		pos.x = (float)targetRect.x;
		rect.x = targetRect.x;
	}
}

void Tile::MoveTargetRectDown()
{
	targetRect.Move(0, SIZE);
}

void Tile::MoveTargetRectLeft()
{
	targetRect.Move(-SIZE, 0);
}

void Tile::MoveTargetRectTo(const Vec2i& pos)
{
	targetRect.x = pos.x;
	targetRect.y = pos.y;
}

void Tile::SyncRectWithTarget()
{
	rect = targetRect;
	pos = { (float)rect.x, (float)rect.y };
}

bool Tile::IsAtTargetRect() const
{
	return rect == targetRect;
}

bool Tile::IsAtTargetX() const
{
	return rect.x == targetRect.x;
}

bool Tile::IsAtTargetY() const
{
	return rect.y == targetRect.y;
}
