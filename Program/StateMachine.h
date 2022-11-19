#pragma once
#include "ScreenTransition.h"
#include "Mouse.h"
#include "gfx.h"

enum class State {
	SETUP,
	INITIALIZATION,
	PLAYING,
	OVER,
	QUITTING
};

class StateMachine
{
public:
	void Update(float dt);
	void DrawTransitions() const;
	void ChangeState(State state);
	void ChangeState(State state, const ScreenTransition& transition);
	const State& GetState() const;

private:
	State currentState = State::SETUP;
	State nextState = State::SETUP;
	ScreenTransition screenTransition;
};

