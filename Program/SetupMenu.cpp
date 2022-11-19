#include "SetupMenu.h"

void SetupMenu::Update()
{
	for (Button& b : buttons) {
		b.Update();
	}
}

void SetupMenu::Draw() const
{
	const int txtOffsetX = OFFSET.x - 150;
	const int txtOffsetY = OFFSET.y + (BTN_SIZE - txt::CHAR_HEIGHT) / 2;
	txt::Print("Rows: " + std::to_string(rows), txtOffsetX, txtOffsetY, Colors::WHITE);
	txt::Print("Columns: " + std::to_string(columns), txtOffsetX, txtOffsetY + (BTN_SIZE + BTN_PADDING), Colors::WHITE);
	txt::Print("Colors: " + std::to_string(colors), txtOffsetX, txtOffsetY + (BTN_SIZE + BTN_PADDING) * 2, Colors::WHITE);
	for (const Button& b : buttons) {
		b.Draw();
	}
}

int SetupMenu::GetRows() const
{
	return rows;
}

int SetupMenu::GetColumns() const
{
	return columns;
}

int SetupMenu::GetColors() const
{
	return colors;
}

void SetupMenu::IncrementRows()
{
	if (rows < MAX_ROWS) ++rows;
}

void SetupMenu::DecrementRows()
{
	if (rows > MIN_ROWS) --rows;
}

void SetupMenu::IncrementColumns()
{
	if (columns < MAX_COLUMNS) ++columns;
}

void SetupMenu::DecrementColumns()
{
	if (columns > MIN_COLUMNS) --columns;
}

void SetupMenu::IncrementColors()
{
	if (colors < MAX_COLORS) ++colors;
}

void SetupMenu::DecrementColors()
{
	if (colors > MIN_COLORS) --colors;
}
