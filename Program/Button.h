#pragma once
#include <functional>
#include <string>
#include "Rect.h"
#include "gfx.h"
#include "Mouse.h"
#include "txt.h"

class Button
{
public:
	Button(const Rect& rect, const std::string& label, std::function<void()> onClick);
	void Draw() const;
	void Update();
	void ChangeLabel(const std::string& newLabel);

private:
	Rect rect;
	std::string label;
	static constexpr Color color = Color(150, 150, 150);
	static constexpr Color shadowColor = Color(100, 100, 100);
	std::function<void()> onClick;
	Vec2i labelPos;
	bool isHovered = false, isPressed = false;
};

