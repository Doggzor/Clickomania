#include "Sprite.h"
#include <cassert>
#include <fstream>
#include "gfx.h"

Sprite::Sprite(const std::string& filename)
{
	std::ifstream file(filename, std::ios::binary);
	assert(file);
	BITMAPFILEHEADER bmfh;
	file.read(reinterpret_cast<char*>(&bmfh), sizeof(bmfh));
	BITMAPINFOHEADER bmih;
	file.read(reinterpret_cast<char*>(&bmih), sizeof(bmih));

	assert(bmih.biBitCount == 24 || bmih.biBitCount == 32);
	assert(bmih.biCompression == BI_RGB);

	const bool is32bit = bmih.biBitCount == 32;
	const bool isHeightPositive = bmih.biHeight > 0;
	width = bmih.biWidth;
	height = isHeightPositive * bmih.biHeight - bmih.biHeight * !isHeightPositive;
	pixels = new Color[width * height];

	const int padding = (bmih.biBitCount == 24) * (width % 4);
	file.seekg(bmfh.bfOffBits);

	//Adjust these based on if rows are reversed in the bmp file
	int y = (height - 1) * (isHeightPositive);
	const int yEnd = height * !isHeightPositive - isHeightPositive;
	const int yIncrement = !isHeightPositive - isHeightPositive;

	for (; y != yEnd; y += yIncrement) {
		for (int x = 0; x < width; ++x) {
			const unsigned char b = file.get();
			const unsigned char g = file.get();
			const unsigned char r = file.get();
			SetPixel(x, y, Color(r, g, b));
			file.seekg(is32bit, std::ios::cur);
		}
		file.seekg(padding, std::ios::cur);
	}
}

Sprite::Sprite(int width, int height)
	:
	width(width),
	height(height),
	pixels(new Color[width * height])
{
}

Sprite::~Sprite()
{
	delete[] pixels;
	pixels = nullptr;
}

Sprite::Sprite(const Sprite& src)
	:
	Sprite(src.width, src.height)
{
	const int nPixels = width * height;
	for (int i = 0; i < nPixels; ++i) {
		pixels[i] = src.pixels[i];
	}
}

Sprite& Sprite::operator=(const Sprite& src)
{
	if (this == &src) return *this;
	width = src.width;
	height = src.height;
	delete[] pixels;
	const int nPixels = width * height;
	pixels = new Color[nPixels];
	for (int i = 0; i < nPixels; ++i) {
		pixels[i] = src.pixels[i];
	}
	return *this;
}

void Sprite::SetPixel(int x, int y, Color c)
{
	assert(x >= 0);
	assert(x < width);
	assert(y >= 0);
	assert(y < height);
	pixels[y * width + x] = c;
}

Color& Sprite::GetPixel(int x, int y) const
{
	return pixels[y * width + x];
}

int Sprite::GetWidth() const
{
	return width;
}

int Sprite::GetHeight() const
{
	return height;
}