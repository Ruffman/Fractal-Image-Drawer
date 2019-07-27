#pragma once

#include <string>
#include <memory>

struct Zoom;
class ZoomList;
class Bitmap;

class FractalCreator
{
private:
	int _width{ -1 };
	int _height{ -1 };
	int _total{ -1 };
	std::unique_ptr<ZoomList> _zoomList{ nullptr };
	std::unique_ptr<Bitmap> _bitMap{ nullptr };
	std::unique_ptr<int[]> _histogram{ nullptr };
	std::unique_ptr<int[]> _pixelIterationInfo{ nullptr };

public:
	FractalCreator(int width, int height);
	~FractalCreator();

	void calculateIteration();
	int calculateTotalIterations();
	void drawFractal();
	void addZoom(const Zoom& zoom);
	void writeBitmap(std::string name);
};

