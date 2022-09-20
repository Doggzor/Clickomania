#pragma once
#include "gfx.h"
#include "Mouse.h"
#include "Random.h"
#include "Board.h"

class Game
{
	friend int APIENTRY wWinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPWSTR, _In_ int);
private:
	Game() = default;
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	~Game() = default;
	void Initialize();
	void Update(float dt);
	void Draw();

private:

	//Rect rect = { 0, 0, 80, 50 };
	//Vector2i dir = { 180, 180 };
	//bool isRectActive = true;
	Board board = Board(12, 18);
};

