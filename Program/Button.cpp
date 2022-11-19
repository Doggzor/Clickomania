#include "Button.h"

Button::Button(const Rect& rect, const std::string& label, std::function<void()> onClick)
	:
	rect(rect),
	label(label),
	onClick(onClick)
{
	labelPos = Vec2i(
		rect.GetCenter().x - (label.length() * txt::CHAR_WIDTH) / 2,
		rect.GetCenter().y - txt::CHAR_HEIGHT / 2
	);
}

void Button::Draw() const
{
	const int currentPressDepth = isPressed;
	const int depth = 4 - currentPressDepth;
	Rect visualRect = rect;
	visualRect.Move(0, currentPressDepth * 2);
	visualRect.Resize(-currentPressDepth);
	gfx::DrawRect(visualRect, color);
	for (int y = 0; y < depth; ++y) {
		for (int x = y; x < visualRect.width - y; ++x) {
			gfx::SetPixel(visualRect.x + x, visualRect.y + visualRect.height + y, shadowColor);
		}
	}
	const Vec2i visualLabelPos = Vec2i(labelPos.x + currentPressDepth / 2, labelPos.y + currentPressDepth * 2);
	txt::Print(label, visualLabelPos, Colors::BLACK);
	if (isHovered && !isPressed)
		gfx::DrawRectEmpty(rect.Resized(2), 2, Colors::GREEN);
}

void Button::Update()
{
	isHovered = Mouse::IsInputEnabled() && rect.Contains(Mouse::GetMousePos());
	if (isHovered && Mouse::IsLButtonPressed()) {
		isPressed = true;
		onClick();
	}
	if (!Mouse::IsLButtonDown() || !isHovered) isPressed = false;
}

void Button::ChangeLabel(const std::string& newLabel)
{
	label = newLabel;
	labelPos.x = rect.GetCenter().x - (label.length() * txt::CHAR_WIDTH) / 2;
}
