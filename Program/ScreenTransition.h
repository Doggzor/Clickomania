#pragma once
#include "gfx.h"

class ScreenTransition
{
public:
	enum class State {
		NONE,
		CLOSING,
		OPENING
	};
	ScreenTransition() = default;
	ScreenTransition(float closingDuration, float openingDuration);
	void Start();
	void Update(float dt);
	void Draw() const;
	bool IsTransitioning() const;
	bool IsSceneOpening() const;
	bool IsSceneClosing() const;

private:
	float closingDur = 0.0f, openingDur = 0.0f, speed = 0.0f;
	float size = 0.0f;
	static constexpr float MAX_SIZE = min(gfx::ScreenWidth, gfx::ScreenHeight) * 0.55f;
	static constexpr Color color = Color(32, 32, 32);
	State state = State::NONE;
};

