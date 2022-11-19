#include "gfx.h"

gfx::gfx()
{
	buffer = {};
	buffer.width = ScreenWidth;
	buffer.height = ScreenHeight;
	buffer.bminfo.bmiHeader.biSize = sizeof(buffer.bminfo.bmiHeader);
	buffer.bminfo.bmiHeader.biWidth = buffer.width;
	buffer.bminfo.bmiHeader.biHeight = -buffer.height;
	buffer.bminfo.bmiHeader.biPlanes = 1;
	buffer.bminfo.bmiHeader.biBitCount = 32;
	buffer.bminfo.bmiHeader.biCompression = BI_RGB;

	buffer.memory = VirtualAlloc(0, (buffer.width * buffer.height * sizeof(Color)), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
}

gfx::~gfx()
{
	if (buffer.memory) {
		VirtualFree(buffer.memory, 0, MEM_RELEASE);
	}
}

gfx& gfx::GetInstance()
{
	static gfx gfx;
	return gfx;
}

void gfx::SetWindowHandle(HWND hWnd)
{
	GetInstance().handle = hWnd;
}

void gfx::CopyBufferToWindow(HDC deviceContext)
{
	const BitmapBuffer& buffer = GetInstance().buffer;

	StretchDIBits(
		deviceContext,
		0, 0, ScreenWidth, ScreenHeight,
		0, 0, buffer.width, buffer.height,
		buffer.memory, &buffer.bminfo, DIB_RGB_COLORS, SRCCOPY);
}

void gfx::ClearScreen()
{
	DrawRect(0, 0, ScreenWidth, ScreenHeight, BackgroundColor);
}

void gfx::SetPixel(int x, int y, Color c)
{
	const BitmapBuffer& buffer = GetInstance().buffer;

	if (x < 0 || x >= ScreenWidth || y < 0 || y >= ScreenHeight)
		return;

	const int bytesPerPixel = sizeof(Color);
	Color* pixel = reinterpret_cast<Color*>(
		reinterpret_cast<unsigned char*> (buffer.memory) + (y * (buffer.width * bytesPerPixel) + x * bytesPerPixel)
		);
	*pixel = c;
}

const Color gfx::GetPixel(int x, int y)
{
	const BitmapBuffer& buffer = GetInstance().buffer;

	if (x < 0 || x >= ScreenWidth || y < 0 || y >= ScreenHeight) {
		return BackgroundColor;
	}

	const int bytesPerPixel = sizeof(Color);
	Color* pixel = reinterpret_cast<Color*>(
		reinterpret_cast<unsigned char*> (buffer.memory) + (y * (buffer.width * bytesPerPixel) + x * bytesPerPixel)
		);

	return *pixel;
}

void gfx::DrawRect(int x, int y, int width, int height, Color c)
{
	int startX = max(x, 0);
	int startY = max(y, 0);
	int endX = min(x + width, ScreenWidth);
	int endY = min(y + height, ScreenHeight);

	if (startX > endX) std::swap(startX, endX);
	if (startY > endY) std::swap(startY, endY);

	for (int x = startX; x < endX; ++x) {
		for (int y = startY; y < endY; ++y) {
			SetPixel(x, y, c);
		}
	}
}

void gfx::DrawRect3D(const Rect& rect, int depth, Color c)
{
	assert(depth <= min(rect.width, rect.height) / 2);
	const Rect topRect = rect.Resized(-depth);
	DrawRect(topRect, c * 0.8f);
	DrawBorder3D(topRect, depth, c, false);
}

void gfx::DrawRectEmpty(int x, int y, int width, int height, int thickness, Color c)
{
	for (int i = 0; i < thickness; ++i) {
		for (int w = 0; w < width; ++w) {
			SetPixel(x + w, y + i, c);
			SetPixel(x + w, y + height - i - 1, c);
		}
		for (int h = 0; h < height - thickness * 2; ++h) {
			SetPixel(x + i, y + thickness + h, c);
			SetPixel(x + width - i - 1, y + thickness + h, c);
		}
	}
	//v2
	{
		//for (int w = 0; w < width; ++w) {
		//	for (int h = 0; h < height; ++h) {
		//		if ((w < thickness || w >= width - thickness) || (h < thickness || h >= height - thickness))
		//			Pixel(x + w, y + h, c);
		//	}
		//}
	}
	//v1
	{
		//DrawRect(x, y, width, thickness, c); //Top
		//DrawRect(x, y + height - thickness, width, thickness, c); //Bottom
		//DrawRect(x, y + thickness, thickness, height - 2 * thickness, c); //Left
		//DrawRect(x + width - thickness, y + thickness, thickness, height - 2 * thickness, c); //Right
	}
}

void gfx::DrawRectEmpty3D(const Rect& rect, int thickness, int depth, Color c)
{
	assert(thickness >= depth);
	gfx::DrawRectEmpty(rect, thickness - depth, c * 0.8f);
	gfx::DrawBorder3D(rect.Resized(depth - thickness), depth, c, true);
}

void gfx::DrawBorder3D(const Rect& border, int depth, Color c, bool inside)
{
	Color topC, bottomC, leftC, rightC;
	Rect newBorder = border;
	if (inside) {
		assert(depth <= min(border.width, border.height) / 2);
		newBorder.Resize(-depth);
		topC = c * 0.6f;
		bottomC = c * 0.95f;
		leftC = c * 0.67f;
		rightC = c * 0.88f;
	}
	else {
		topC = c * 0.95f;
		bottomC = c * 0.6f;
		leftC = c * 0.88f;
		rightC = c * 0.67f;
	}
	for (int d = 0; d < depth; ++d) {
		for (int w = d; w <= newBorder.width + d * 3; ++w) {
			//Top
			SetPixel(newBorder.x - d * 2 + w, newBorder.y - d - 1, topC);
			//Bottom
			SetPixel(newBorder.x - d * 2 + w - 1, newBorder.y + newBorder.height + d, bottomC);
		}
		for (int h = d; h <= newBorder.height + d * 3; ++h) {
			//Left
			SetPixel(newBorder.x - d - 1, newBorder.y - d * 2 + h - 1, leftC);
			//Right
			SetPixel(newBorder.x + newBorder.width + d, newBorder.y - d * 2 + h, rightC);
		}
	}
}

void gfx::DrawCircle(int x, int y, int radius, Color c)
{
	const int sqRadius = radius * radius;
	for (int b = y - radius + 1; b < y + radius; ++b)
	{
		for (int a = x - radius + 1; a < x + radius; ++a)
		{
			const int sqLengthA = (x - a) * (x - a);
			const int sqLengthB = (y - b) * (y - b);
			if ((sqLengthA + sqLengthB <= sqRadius))
			{
					SetPixel(a, b, c);
			}
		}
	}
}

void gfx::DrawSprite(const Sprite& sprite, int x, int y)
{
	const int width = sprite.GetWidth();
	const int height = sprite.GetHeight();
	for (int sy = 0; sy < height; ++sy) {
		for (int sx = 0; sx < width; ++sx) {
			SetPixel(x + sx, y + sy, sprite.GetPixel(sx, sy));
		}
	}
}

void gfx::DrawSprite(const Sprite& sprite, int x, int y, Color chroma, const Rect& spritePart)
{
	assert(spritePart.x >= 0);
	assert(spritePart.x + spritePart.width <= sprite.GetWidth());
	assert(spritePart.y >= 0);
	assert(spritePart.y + spritePart.height <= sprite.GetHeight());

	for (int sy = spritePart.y; sy < spritePart.y + spritePart.height; ++sy) {
		for (int sx = spritePart.x; sx < spritePart.x + spritePart.width; ++sx) {
			Color c = sprite.GetPixel(sx, sy);
			if (c != chroma) SetPixel(x + sx - spritePart.x, y + sy - spritePart.y, c);
		}
	}
}

void gfx::DrawSpriteColored(const Sprite& sprite, int x, int y, Color color, Color chroma, const Rect& spritePart)
{
	assert(spritePart.x >= 0);
	assert(spritePart.x + spritePart.width <= sprite.GetWidth());
	assert(spritePart.y >= 0);
	assert(spritePart.y + spritePart.height <= sprite.GetHeight());

	for (int sy = spritePart.y; sy < spritePart.y + spritePart.height; ++sy) {
		for (int sx = spritePart.x; sx < spritePart.x + spritePart.width; ++sx) {
			if (sprite.GetPixel(sx, sy) != chroma) SetPixel(x + sx - spritePart.x, y + sy - spritePart.y, color);
		}
	}
}

Sprite gfx::CopyScreenPart(const Rect& rect)
{
	Sprite spr(rect.width, rect.height);
	for (int x = 0; x < rect.width; ++x) {
		for (int y = 0; y < rect.height; ++y) {
			spr.SetPixel(x, y, GetPixel(rect.x + x, rect.y + y));
		}
	}
	return spr;
}
