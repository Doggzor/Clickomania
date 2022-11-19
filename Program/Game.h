#pragma once
#include "gfx.h"
#include "Mouse.h"
#include "Board.h"
#include <memory>
#include "FileRW.h"
#include "SetupMenu.h"
#include "StateMachine.h"

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
	void UpdateButtonLabels();


private:
	std::unique_ptr<Board> board;
	SetupMenu setupMenu;
	int highScore = 0;
	std::string highScoreFileName = "hscore.txt";
	std::unique_ptr<Particles> screenParticles;
	StateMachine stateMachine;
	ScreenTransition screenTransition = ScreenTransition(.5f, .8f);

#pragma region Buttons
	static constexpr int BTN_WIDTH = 175;
	static constexpr int BTN_HEIGHT = 50;
	static constexpr Vec2i BTN_OFFSET = { 10, 10 };

	std::vector<Button> buttons{
		Button(Rect(BTN_OFFSET.x, BTN_OFFSET.y, BTN_WIDTH, BTN_HEIGHT), "Restart", [&]() { stateMachine.ChangeState(State::INITIALIZATION, screenTransition); }),
		Button(Rect(BTN_OFFSET.x, BTN_OFFSET.y + (BTN_HEIGHT + 5), BTN_WIDTH, BTN_HEIGHT), "Change Board", [&]() { stateMachine.ChangeState(State::SETUP, screenTransition); }),
		Button(Rect(BTN_OFFSET.x, BTN_OFFSET.y + (BTN_HEIGHT + 5) * 2, BTN_WIDTH, BTN_HEIGHT), "View", [&]() {
			board->Switch3DView();
			buttons[2].ChangeLabel(board->GetViewString());
			}),
		Button(Rect(BTN_OFFSET.x, BTN_OFFSET.y + (BTN_HEIGHT + 5) * 3, BTN_WIDTH, BTN_HEIGHT), "Particles", [&]() {
			board->SwitchParticles();
			buttons[3].ChangeLabel(board->GetParticlesEnabledString());
			}),
		Button(Rect(BTN_OFFSET.x, BTN_OFFSET.y + (BTN_HEIGHT + 5) * 4, BTN_WIDTH, BTN_HEIGHT), "AnimSpeed", [&]() {
			board->ChangeAnimationSpeed();
			buttons[4].ChangeLabel(board->GetAnimSpeedString());
			}),
		Button(Rect(BTN_OFFSET.x, BTN_OFFSET.y + (BTN_HEIGHT + 5) * 5, BTN_WIDTH, BTN_HEIGHT), "Quit", [&]() {
				screenParticles = std::make_unique<Particles>(gfx::ScreenRect, 30);
				stateMachine.ChangeState(State::QUITTING);
			})
	};
	Button btnStartGame = Button(Rect(350, 500, 150, 50), "Start", [&]() { stateMachine.ChangeState(State::INITIALIZATION, screenTransition); });
#pragma endregion
};

