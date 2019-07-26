#pragma once

#include <string>
#include <cstdint>

class Bitmap
{
private:
	int _width{ 0 };
	int _height{ 0 };
	std::unique_ptr<std::uint8_t[]> _pPixels{ nullptr };

public:
	Bitmap(int width, int height);
	virtual ~Bitmap();

	void setPixel(int x, int y, std::uint8_t red, std::uint8_t green, std::uint8_t blue);
	bool write(std::string filename);
};

