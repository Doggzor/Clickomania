#include "Game.h"

void Game::Initialize()
{
}

void Game::Update(float dt)
{
	rect.x += (float)dir.x * dt;
	rect.y += (float)dir.y * dt;
	if (rect.x + rect.width >= gfx::ScreenWidth || rect.x < 0) dir.x *= -1;
	if (rect.y + rect.height >= gfx::ScreenHeight || rect.y < 0) dir.y *= -1;
	if (Mouse::IsLButtonPressed()) {
		Vector2i p = Mouse::GetMousePos();
		if (rect.Contains(p))
			isRectActive = false;
		else if (!isRectActive) {
			rect.x = min(max(0, p.x - rect.width / 2), gfx::ScreenWidth - rect.width - 1);
			rect.y = min(max(0, p.y - rect.height / 2), gfx::ScreenHeight - rect.height - 1);
			isRectActive = true;
		}
	}
}

void Game::Draw()
{
	if(isRectActive)
		gfx::DrawRect(rect, Colors::ORANGE);

}
