#pragma once
#include "gfx.h"
#include "Sprite.h"
#include <string>
#include "Vec2.h"

static Sprite font = { "font_monospace12x20.bmp" };
class txt
{
public:
	static void Print(const std::string& txt, int x, int y, Color color) {
		Vec2i posCur = { x, y };
		for (auto c : txt) {
			if (c == '\n' || c == '\r') {
				posCur.x = x;
				posCur.y += CHAR_HEIGHT;
			}
			else {
				assert(c >= CHAR_FIRST && c <= CHAR_LAST);
				gfx::DrawSpriteColored(font, posCur.x, posCur.y, color, Colors::WHITE, RectAt(c));
				posCur.x += CHAR_WIDTH;
			}
		}
	}
	static void Print(const std::string& txt, const Vec2i& pos, Color color) {
		Print(txt, pos.x, pos.y, color);
	}
	static void Print(const std::string& txt, int x, int y, Color color, bool is3D) {
		if (is3D) {
			Color shadowC = color * 0.5f;
			Print(txt, x++, y--, shadowC);
			Print(txt, x++, y--, shadowC);
		}
		Print(txt, x, y, color);
	}
private:
	static Rect RectAt(char c) {
		return {
			((c - CHAR_FIRST) % CHARS_PER_ROW) * CHAR_WIDTH,
			((c - CHAR_FIRST) / CHARS_PER_ROW) * CHAR_HEIGHT,
			CHAR_WIDTH,
			CHAR_HEIGHT
		};
	}
public:
	static constexpr int CHAR_WIDTH = 12;
	static constexpr int CHAR_HEIGHT = 20;
private:
	static constexpr int CHARS_PER_ROW = 32;
	static constexpr char CHAR_FIRST = ' ';
	static constexpr char CHAR_LAST = '~';
};