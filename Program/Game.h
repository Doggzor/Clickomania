#pragma once
#include "gfx.h"
#include "Mouse.h"

class Game
{
public:
	Game() = default;
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	~Game() = default;
	void Run();
private:
	void Update();
	void Draw();


	Rect rect = { 0, 0, 80, 50 };
	Vector2i dir = { 3, 3 };
	bool isRectActive = true;
};

