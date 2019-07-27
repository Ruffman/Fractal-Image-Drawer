#include "pch.h"
#include "FractalCreator.h"
#include "ZoomList.h"
#include "Zoom.h"
#include "Bitmap.h"
#include "Mandelbrot.h"

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
}

FractalCreator::~FractalCreator()
{
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
	for (int i = 0; i < Mandelbrot::MAX_ITERATIONS; i++)
	{
		_total += _histogram[i];
	}
	return _total;
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

			if (iterations != Mandelbrot::MAX_ITERATIONS)
			{
				uint8_t color = (uint8_t)(256 * (double)iterations / Mandelbrot::MAX_ITERATIONS);

				double hue = 0.0;

				for (int i = 0; i <= iterations; i++)
				{
					hue += ((double)_histogram[i]) / _total;
				}

				red = pow(255, hue);
				green = 0;
				blue = 0;
			}
			_bitMap->setPixel(w, h, red, green, blue);
		}
	}
}

void FractalCreator::addZoom(const Zoom & zoom)
{
	_zoomList->add(zoom);
}

void FractalCreator::writeBitmap(std::string name)
{
	_bitMap->write(name);
}
