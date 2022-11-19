#include "Game.h"

void Game::Initialize()
{
	stateMachine.ChangeState(State::SETUP);
	const int columns = setupMenu.GetColumns();
	const int rows = setupMenu.GetRows();
	const int colors = setupMenu.GetColors();
	board = std::make_unique<Board>(columns, rows, colors);
	highScore = FileRW::ReadHighScore(highScoreFileName, columns, rows, colors);
}

void Game::Update(float dt)
{
	stateMachine.Update(dt);

	switch (stateMachine.GetState()) {
	case State::SETUP:
		setupMenu.Update();
		btnStartGame.Update();
		break;
	case State::INITIALIZATION:
	{
		const int columns = setupMenu.GetColumns();
		const int rows = setupMenu.GetRows();
		const int colors = setupMenu.GetColors();
		Board::Settings boardSettings = board->GetSettings();
		boardSettings.columns = columns;
		boardSettings.rows = rows;
		boardSettings.colors = colors;
		board.reset();
		board = std::make_unique<Board>(boardSettings);
		UpdateButtonLabels();
		highScore = FileRW::ReadHighScore(highScoreFileName, boardSettings.columns, boardSettings.rows, boardSettings.colors);
		stateMachine.ChangeState(State::PLAYING);
	}
		break;
	case State::PLAYING:
		for (Button& b : buttons) b.Update();
		board->Update(dt);
		board->UpdateParticles(dt);
		if (!board->ShouldAnimate() && !board->GetValidMoves()) {
			FileRW::WriteHighScore(highScoreFileName, max(board->GetScore(), highScore), setupMenu.GetColumns(), setupMenu.GetRows(), setupMenu.GetColors());
			stateMachine.ChangeState(State::OVER);
		}
		break;
	case State::OVER:
		for (Button& b : buttons) b.Update();
		board->UpdateParticles(dt);
		break;
	case State::QUITTING:
		screenParticles->Update(dt);
		if (screenParticles->Expired())
			PostQuitMessage(0);
		break;
	}
}

void Game::Draw()
{
	switch (stateMachine.GetState()) {
	case State::SETUP:
		setupMenu.Draw();
		btnStartGame.Draw();
		break;
	
	case State::OVER:
		txt::Print("GAME OVER", 120, 565, Colors::RED);
		if (board->GetScore() > highScore) {
			txt::Print("(New High Score!)", 520, 565, Colors::GREEN);
		}
		//No break is intentional
	case State::PLAYING:
		for (const Button& b : buttons) {
			b.Draw();
		}
		txt::Print("SCORE: " + std::to_string(board->GetScore()), 325, 565, Colors::WHITE);
		txt::Print("HIGH SCORE: " + std::to_string(highScore), 305, 15, Colors::WHITE);
		board->Draw();
		break;
	case State::QUITTING:
		screenParticles->Draw();
		break;
	}
	stateMachine.DrawTransitions();
}

void Game::UpdateButtonLabels()
{
	buttons[2].ChangeLabel(board->GetViewString());
	buttons[3].ChangeLabel(board->GetParticlesEnabledString());
	buttons[4].ChangeLabel(board->GetAnimSpeedString());
}

