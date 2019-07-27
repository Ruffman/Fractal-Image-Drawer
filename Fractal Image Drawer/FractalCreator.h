#pragma once

#include <string>
#include <memory>
#include <vector>

struct Zoom;
class ZoomList;
class Bitmap;
class RGB;

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

	std::vector<double> _ranges;
	std::vector<RGB> _rangeColors;
	std::vector<int> _rangeTotals;

	bool _bGotFirstRange{ false };

private:
	void calculateIteration();
	int calculateTotalIterations();
	void calculateRangeTotals();
	void drawFractal();
	void writeBitmap(std::string name);
	int getRange(int iterations) const;

public:
	FractalCreator(int width, int height);
	~FractalCreator();

	void addZoom(const Zoom& zoom);
	void addRange(double rangeEnd, const RGB& rgb);
	void run(std::string outFileName);
};

