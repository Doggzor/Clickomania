#include "StateMachine.h"

void StateMachine::Update(float dt)
{
	screenTransition.Update(dt);
	if (screenTransition.IsTransitioning()) {
		Mouse::DisableInput();
		if (screenTransition.IsSceneOpening()) {
			currentState = nextState;
		}
	}
	else {
		Mouse::EnableInput();
	}
}

void StateMachine::DrawTransitions() const
{
	screenTransition.Draw();
}

void StateMachine::ChangeState(State state)
{
	currentState = state;
	nextState = state;
}

void StateMachine::ChangeState(State state, const ScreenTransition& transition)
{
	screenTransition = transition;
	screenTransition.Start();
	nextState = state;
}

const State& StateMachine::GetState() const
{
	return currentState;
}
