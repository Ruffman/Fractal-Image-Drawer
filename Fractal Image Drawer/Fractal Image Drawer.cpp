// Fractal Image Drawer.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include "pch.h"
#include <iostream>
#include <cstdint>
#include <memory>

#include "Bitmap.h"
#include "Mandelbrot.h"

using namespace std;

int main()
{
	int const WIDTH = 800;
	int const HEIGHT = 600;
	int const OFFSET = WIDTH * 0.25;

	Bitmap bitmap(WIDTH, HEIGHT);

	unique_ptr<int[]> histogram(new int[Mandelbrot::MAX_ITERATIONS + 1]{ 0 });

	for (int w = 0; w < WIDTH; ++w)
	{
		for (int h = 0; h < HEIGHT; ++h)
		{
			double xFractal = (w - WIDTH / 2.0 - OFFSET) * 2.0 / HEIGHT;
			double yFractal = (h - HEIGHT / 2.0) * 2.0 / HEIGHT;

			int iterations = Mandelbrot::getIterations(xFractal, yFractal);

			histogram[iterations]++;

			uint8_t color = (uint8_t)(256 * (double)iterations / Mandelbrot::MAX_ITERATIONS);

			color = color * color;

			bitmap.setPixel(w, h, 0, color, 0);

			cout << w << ", " << h << endl;
		}
	}

	for (int i = 0; i <= Mandelbrot::MAX_ITERATIONS; i++)
	{
		cout << histogram[i] << endl;
	}

	bitmap.write("Test.bmp");
}
