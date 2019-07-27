// Fractal Image Drawer.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include "pch.h"
#include <iostream>
#include <cstdint>
#include <memory>
#include <math.h>

#include "Bitmap.h"
#include "Mandelbrot.h"
#include "ZoomList.h"
#include "Zoom.h"

using namespace std;

int main()
{
	int const WIDTH = 800;
	int const HEIGHT = 600;
	int const OFFSET = WIDTH * 0.25;

	Bitmap bitmap(WIDTH, HEIGHT);

	ZoomList zoomList(WIDTH, HEIGHT);
	zoomList.add(Zoom(WIDTH / 2, HEIGHT / 2, 4.0 / WIDTH));
	zoomList.add(Zoom(300, HEIGHT / 2, 0.9));
	zoomList.add(Zoom(388, HEIGHT - 160	, 0.1));
	zoomList.add(Zoom(557, HEIGHT - 310, 0.1));

	unique_ptr<int[]> histogram(new int[Mandelbrot::MAX_ITERATIONS]{ 0 });
	unique_ptr<int[]> pixelIterationInfo(new int[WIDTH * HEIGHT]);

	for (int w = 0; w < WIDTH; ++w)
	{
		for (int h = 0; h < HEIGHT; ++h)
		{
			auto fractalCoord = zoomList.calculate(w, h);

			int iterations = Mandelbrot::getIterations(fractalCoord.first, fractalCoord.second);

			pixelIterationInfo[h * WIDTH + w] = iterations;

			if (iterations != Mandelbrot::MAX_ITERATIONS)
			{
				histogram[iterations]++;
			}
		}
		if(w % 100 == 0)
		cout << w << endl;
	}

	int total = 0;
	for(int i = 0; i < Mandelbrot::MAX_ITERATIONS; i++)
	{
		total += histogram[i];
	}

	for (int w = 0; w < WIDTH; ++w)
	{
		for (int h = 0; h < HEIGHT; ++h)
		{
			uint8_t red = 0;
			uint8_t green = 0;
			uint8_t blue = 0;

			int iterations = pixelIterationInfo[h * WIDTH + w];

			if (iterations != Mandelbrot::MAX_ITERATIONS)
			{
				uint8_t color = (uint8_t)(256 * (double)iterations / Mandelbrot::MAX_ITERATIONS);

				double hue = 0.0;

				for (int i = 0; i <= iterations; i++)
				{
					hue += ((double)histogram[i]) / total;
				}

				red = pow(255, hue);
				green = 0;
				blue = 0;
			}
			bitmap.setPixel(w, h, red, green, blue);
		}
	}

	bitmap.write("Test.bmp");
}
