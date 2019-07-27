#include "pch.h"
#include "FractalCreator.h"
#include "ZoomList.h"
#include "Zoom.h"
#include "Bitmap.h"
#include "Mandelbrot.h"
#include "RGB.h"

#include <assert.h>
#include <iostream>

using namespace std;

FractalCreator::FractalCreator(int width, int height) :
	_width(width),
	_height(height),
	_total(0),
	_zoomList(new ZoomList(_width, _height)), 
	_bitMap(new Bitmap(_width, _height)), 
	_histogram(new int[Mandelbrot::MAX_ITERATIONS]{ 0 }), 
	_pixelIterationInfo(new int[_width * _height])
{
	addZoom(Zoom(_width / 2, _height / 2, 4.0 / _width));
}

FractalCreator::~FractalCreator()
{
}

void FractalCreator::run(string outFileName)
{
	calculateIteration();
	calculateRangeTotals();
	drawFractal();
	writeBitmap(outFileName);
}

void FractalCreator::calculateIteration()
{
	for (int w = 0; w < _width; ++w)
	{
		for (int h = 0; h < _height; ++h)
		{
			auto fractalCoord = _zoomList->calculate(w, h);

			int iterations = Mandelbrot::getIterations(fractalCoord.first, fractalCoord.second);

			_pixelIterationInfo[h * _width + w] = iterations;

			if (iterations != Mandelbrot::MAX_ITERATIONS)
			{
				_histogram[iterations]++;
			}
		}
		if (w % 100 == 0)
			cout << w << endl;
	}
}

int FractalCreator::calculateTotalIterations()
{
	for (int i = 0; i < Mandelbrot::MAX_ITERATIONS; ++i)
	{
		_total += _histogram[i];
	}
	return _total;
}

void FractalCreator::calculateRangeTotals()
{
	int rangeIndex = 0;

	for (int i = 0; i < Mandelbrot::MAX_ITERATIONS; ++i)
	{
		int pixels = _histogram[i];

		if (i >= _ranges[rangeIndex + 1])
		{
			++rangeIndex;
		}

		_rangeTotals[rangeIndex] += pixels;
	}
}

void FractalCreator::drawFractal()
{
	calculateTotalIterations();

	for (int w = 0; w < _width; ++w)
	{
		for (int h = 0; h < _height; ++h)
		{
			uint8_t red = 0;
			uint8_t green = 0;
			uint8_t blue = 0;

			int iterations = _pixelIterationInfo[h * _width + w];

			int range = getRange(iterations);
			int rangeTotal = _rangeTotals[range];
			int rangeStart = _ranges[range];

			RGB& startColor = _rangeColors[range];
			RGB& endColor = _rangeColors[range + 1];
			RGB colorDiff = endColor - startColor;

			if (iterations != Mandelbrot::MAX_ITERATIONS)
			{
				int totalPixels = 0;

				for (int i = rangeStart; i <= iterations; ++i)
				{
					totalPixels += _histogram[i];
				}

				red = startColor._r + colorDiff._r * (double)totalPixels / rangeTotal;
				green = startColor._g + colorDiff._g * (double)totalPixels / rangeTotal;
				blue = startColor._b + colorDiff._b * (double)totalPixels / rangeTotal;
			}
			_bitMap->setPixel(w, h, red, green, blue);
		}
	}
}

void FractalCreator::addZoom(const Zoom& zoom)
{
	_zoomList->add(zoom);
}

void FractalCreator::addRange(double rangeEnd, const RGB& rgb)
{
	_ranges.push_back(rangeEnd * Mandelbrot::MAX_ITERATIONS);
	_rangeColors.push_back(rgb);

	if (_bGotFirstRange)
	{
		_rangeTotals.push_back(0);
	}
	_bGotFirstRange = true;
}

void FractalCreator::writeBitmap(string name)
{
	_bitMap->write(name);
}

int FractalCreator::getRange(int iterations) const
{
	int range = 0;

	for (int i = 1; i < _ranges.size(); ++i)
	{
		range = i;

		if (_ranges[i] > iterations)
		{
			break;
		}
	}

	--range;

	assert(range > -1);
	assert(range < _ranges.size());

	return range;
}
