#include "ScreenTransition.h"

ScreenTransition::ScreenTransition(float closingDuration, float openingDuration)
	:
	closingDur(closingDuration),
	openingDur(openingDuration)
{
}

void ScreenTransition::Start()
{
	if (!IsTransitioning()) {
		state = State::CLOSING;
	}
}

void ScreenTransition::Update(float dt)
{
	switch (state) {
	case State::CLOSING:
		speed = MAX_SIZE * dt / closingDur;
		size += speed;
		if (size >= MAX_SIZE) {
			state = State::OPENING;
		}
		break;
	case State::OPENING:
		speed = MAX_SIZE * dt / openingDur;
		size -= speed;
		if (size <= 0.0f) {
			state = State::NONE;
		}
		break;
	}
}

void ScreenTransition::Draw() const
{
	if (state != State::NONE)
		gfx::DrawRectEmpty(gfx::ScreenRect, (int)size, color);
}

bool ScreenTransition::IsTransitioning() const
{
	return state != State::NONE;
}

bool ScreenTransition::IsSceneOpening() const
{
	return state == State::OPENING;
}

bool ScreenTransition::IsSceneClosing() const
{
	return state == State::CLOSING;
}
