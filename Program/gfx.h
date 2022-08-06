#pragma once
#include "windows.h"
#include "Rect.h"
#include "Vector2i.h"

struct Color
{
public:
	constexpr Color(unsigned char R, unsigned char G, unsigned char B) : rawColor(R << 16u | G << 8u | B) {}

	bool operator==(const Color& other) const {
		return rawColor == other.GetRawColor();
	}
	bool operator!=(const Color& other) const {
		return !(*this == other);
	}

	unsigned int GetRawColor() const {
		return rawColor;
	}
private:
	unsigned int rawColor;
};

namespace Colors {
	static constexpr Color BLACK = Color(0, 0, 0);
	static constexpr Color WHITE = Color(255, 255, 255);
	static constexpr Color RED = Color(255, 0, 0);
	static constexpr Color GREEN = Color(0, 255, 0);
	static constexpr Color BLUE = Color(0, 0, 255);
	static constexpr Color YELLOW = Color(255, 255, 0);
}

class gfx
{
	friend int APIENTRY wWinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPWSTR, _In_ int);
	friend BOOL InitInstance(HINSTANCE, int);
public:
	static constexpr int ScreenWidth = 800;
	static constexpr int ScreenHeight = 600;
private:
	gfx();
	gfx(const gfx&) = delete;
	gfx& operator=(const gfx&) = delete;
	~gfx();
	static gfx& GetInstance();

	struct BitmapBuffer {
		int width;
		int height;
		BITMAPINFO bminfo;
		void* memory;
	};

	HWND handle = 0;
	BitmapBuffer buffer;
	static constexpr int BYTES_PER_PIXEL = 4;
	static constexpr Color backgroundColor = Colors::YELLOW;
private:
	static void SetWindowHandle(HWND hWnd);
	static void CopyBufferToWindow(HDC hdc);

public:
	static void ClearScreen();
	static void SetPixel(int x, int y, Color c);
	static void DrawRect(int x, int y, int width, int height, Color c);
	static void DrawRect(Vector2i pos, int width, int height, Color c) {
		DrawRect(pos.x, pos.y, width, height, c);
	}
	static void DrawRect(const Rect& rect, Color c) {
		DrawRect(rect.x, rect.y, rect.width, rect.height, c);
	}
};



