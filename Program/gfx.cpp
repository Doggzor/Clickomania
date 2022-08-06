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

	buffer.memory = VirtualAlloc(0, (buffer.width * buffer.height * BYTES_PER_PIXEL), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
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
	BitmapBuffer& buffer = GetInstance().buffer;

	StretchDIBits(
		deviceContext,
		0, 0, ScreenWidth, ScreenHeight,
		0, 0, buffer.width, buffer.height,
		buffer.memory, &buffer.bminfo, DIB_RGB_COLORS, SRCCOPY);
}

void gfx::ClearScreen()
{
	DrawRect(0, 0, ScreenWidth, ScreenHeight, backgroundColor);
}

void gfx::SetPixel(int x, int y, Color c)
{
	BitmapBuffer& buffer = GetInstance().buffer;

	if (x < 0 || x > ScreenWidth || y < 0 || y > ScreenHeight)
		return;

	unsigned int* pixel = reinterpret_cast<unsigned int*>(
		reinterpret_cast<unsigned char*> (buffer.memory) + (y * (buffer.width * BYTES_PER_PIXEL) + x * BYTES_PER_PIXEL)
		);
	*pixel = c.GetRawColor();
}

void gfx::DrawRect(int x, int y, int width, int height, Color c)
{
	int startX = max(x, 0);
	int startY = max(y, 0);
	int endX = min(x + width, ScreenWidth);
	int endY = min(y + height, ScreenHeight);

	for (int x = startX; x < endX; ++x) {
		for (int y = startY; y < endY; ++y) {
			SetPixel(x, y, c);
		}
	}
}
