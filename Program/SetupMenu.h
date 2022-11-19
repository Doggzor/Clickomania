#pragma once
#include <vector>
#include "txt.h"
#include "Button.h"

class SetupMenu
{
public:
	void Update();
	void Draw() const;
	int GetRows() const;
	int GetColumns() const;
	int GetColors() const;
private:
	void IncrementRows();
	void DecrementRows();
	void IncrementColumns();
	void DecrementColumns();
	void IncrementColors();
	void DecrementColors();
private:
	std::vector<Button> buttons{
		Button({OFFSET.x , OFFSET.y, BTN_SIZE, BTN_SIZE}, "-", [&]() { DecrementRows(); }),
		Button({OFFSET.x + BTN_SIZE + BTN_PADDING, OFFSET.y, BTN_SIZE, BTN_SIZE}, "+", [&]() { IncrementRows(); }),
		Button({OFFSET.x, OFFSET.y + (BTN_SIZE + BTN_PADDING), BTN_SIZE, BTN_SIZE}, "-", [&]() { DecrementColumns(); }),
		Button({OFFSET.x + BTN_SIZE + BTN_PADDING, OFFSET.y + (BTN_SIZE + BTN_PADDING), BTN_SIZE, BTN_SIZE}, "+", [&]() { IncrementColumns(); }),
		Button({OFFSET.x, OFFSET.y + (BTN_SIZE + BTN_PADDING) * 2, BTN_SIZE, BTN_SIZE}, "-", [&]() { DecrementColors(); }),
		Button({OFFSET.x + BTN_SIZE + BTN_PADDING, OFFSET.y + (BTN_SIZE + BTN_PADDING) * 2, BTN_SIZE, BTN_SIZE}, "+", [&]() { IncrementColors(); })
	};
	int rows = 16;
	int columns = 12;
	int colors = 5;

	static constexpr Vec2i OFFSET = { 400, 200 };
	static constexpr int BTN_SIZE = 30;
	static constexpr int BTN_PADDING = 5;
	static constexpr int MAX_ROWS = 20;
	static constexpr int MIN_ROWS = 12;
	static constexpr int MAX_COLUMNS = 16;
	static constexpr int MIN_COLUMNS = 8;
	static constexpr int MAX_COLORS = 6;
	static constexpr int MIN_COLORS = 3;
};

