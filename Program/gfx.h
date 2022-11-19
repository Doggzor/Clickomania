#pragma once
#include "windows.h"
#include "Rect.h"
#include "Vec2.h"
#include "Sprite.h"
#include <cassert>

struct Color
{
public:
	constexpr Color() : rawColor(0) {}
	constexpr Color(unsigned int rawColor) : rawColor(rawColor) {}
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

	unsigned char GetR() const
	{
		return (rawColor >> 16u) & 0xFFu;
	}
	unsigned char GetG() const
	{
		return (rawColor >> 8u) & 0xFFu;
	}
	unsigned char GetB() const
	{
		return rawColor & 0xFFu;
	}

	Color operator* (float n) const {
		return Color(
			(unsigned char)((float)GetR() * n),
			(unsigned char)((float)GetG() * n),
			(unsigned char)((float)GetB() * n)
		);
	}
	Color& operator*= (float n) {
		return *this = *this * n;
	}
private:
	unsigned int rawColor;
};

namespace Colors {
	static constexpr Color BLACK = Color(0, 0, 0);
	static constexpr Color WHITE = Color(255, 255, 255);
	static constexpr Color GRAY = Color(128, 128, 128);
	static constexpr Color RED = Color(255, 0, 0);
	static constexpr Color GREEN = Color(0, 255, 0);
	static constexpr Color BLUE = Color(0, 0, 255);
	static constexpr Color YELLOW = Color(255, 255, 0);
	static constexpr Color CYAN = Color(0, 255, 255);
	static constexpr Color MAGENTA = Color(255, 0, 255);
	static constexpr Color ORANGE = Color(255, 128, 32);
}

class gfx
{
	friend int APIENTRY wWinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPWSTR, _In_ int);
	friend BOOL InitInstance(HINSTANCE, int);
public:
	static constexpr int ScreenWidth = 800;
	static constexpr int ScreenHeight = 600;
	static constexpr Vec2i ScreenCenter = { ScreenWidth / 2, ScreenHeight / 2 };
	static constexpr Rect ScreenRect = { 0, 0, ScreenWidth, ScreenHeight };
	static constexpr Color BackgroundColor = Colors::BLACK;

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
private:
	static void SetWindowHandle(HWND hWnd);
	static void CopyBufferToWindow(HDC hdc);

public:
	static void ClearScreen();
	static void SetPixel(int x, int y, Color c);
	static const Color GetPixel(int x, int y);
	static void DrawRect(int x, int y, int width, int height, Color c);
	static void DrawRect(const Vec2i& pos, int width, int height, Color c) {
		DrawRect(pos.x, pos.y, width, height, c);
	}
	static void DrawRect(const Rect& rect, Color c) {
		DrawRect(rect.x, rect.y, rect.width, rect.height, c);
	}
	static void DrawRect3D(const Rect& rect, int depth, Color c);
	static void DrawRectEmpty(int x, int y, int width, int height, int thickness, Color c);
	static void DrawRectEmpty(const Vec2i& pos, int width, int height, int thickness, Color c) {
		DrawRectEmpty(pos.x, pos.y, width, height, thickness, c);
	}
	static void DrawRectEmpty(const Rect& rect, int thickness, Color c) {
		DrawRectEmpty(rect.x, rect.y, rect.width, rect.height, thickness, c);
	}
	static void DrawRectEmpty3D(const Rect& rect, int thickness, int depth, Color c);
	static void DrawBorder3D(const Rect& rect, int depth, Color c, bool inside);
	static void DrawCircle(int x, int y, int radius, Color c);
	static void DrawCircle(const Vec2i& center, int radius, Color c) {
		DrawCircle(center.x, center.y, radius, c);
	}
	static void DrawSprite(const Sprite& sprite, int x, int y);
	static void DrawSprite(const Sprite& sprite, int x, int y, Color chroma, const Rect& spritePart);
	static void DrawSpriteColored(const Sprite& sprite, int x, int y, Color color, Color chroma, const Rect& spritePart);
	static Sprite CopyScreenPart(const Rect& rect);
	static Sprite CopyScreen() {
		return CopyScreenPart(ScreenRect);
	}
};



