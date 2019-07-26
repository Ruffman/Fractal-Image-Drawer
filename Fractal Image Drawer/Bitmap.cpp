#include "pch.h"
#include "Bitmap.h"
#include "BitmapFileHeader.h"
#include "BitmapInfoHeader.h"

#include <fstream>

using namespace std;

Bitmap::Bitmap(int width, int height) : _width(width),
										_height(height), 
										_pPixels(new uint8_t[width * height * 3]{ 0 })
{
}


Bitmap::~Bitmap()
{
}

void Bitmap::setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue)
{
	uint8_t *pPixel = _pPixels.get();

	pPixel += (3 * y) * _width + (3 * x);

	pPixel[0] = blue;
	pPixel[1] = green;
	pPixel[2] = red;
}

bool Bitmap::write(string filename)
{
	BitmapFileHeader fileHeader;
	BitmapInfoHeader infoHeader;

	fileHeader.fileSize = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader) + _width * _height * 3;
	fileHeader.dataOffset = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);

	infoHeader.width = _width;
	infoHeader.height = _height;

	ofstream outStream;
	outStream.open(filename, ios::binary);

	if (!outStream.is_open())
	{
		return false;
	}

	outStream.write((char*)&fileHeader, sizeof(fileHeader));
	outStream.write((char*)&infoHeader, sizeof(infoHeader));
	outStream.write((char*)_pPixels.get(), _width*_height * 3);

	outStream.close();

	if (outStream.is_open())
	{
		return false;
	}

	return true;
}
