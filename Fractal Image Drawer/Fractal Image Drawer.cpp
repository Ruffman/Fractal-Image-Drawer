// Fractal Image Drawer.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include "pch.h"
#include <iostream>

#include "FractalCreator.h"
#include "Zoom.h"
#include "RGB.h"

using namespace std;

int main()
{
	int const WIDTH = 2048;
	int const HEIGHT = 2048;

	FractalCreator fractalCreator(WIDTH, HEIGHT);

	fractalCreator.addZoom(Zoom(WIDTH * 0.2373828125, HEIGHT / 2, 0.5));
	fractalCreator.addZoom(Zoom(1327, HEIGHT - 946, 0.1));
	fractalCreator.addZoom(Zoom(777, HEIGHT - 421, 0.1));
	fractalCreator.addZoom(Zoom(810, HEIGHT - 892, 0.6));


	fractalCreator.addRange(0.0, RGB(0, 0, 0));
	fractalCreator.addRange(0.05, RGB(255, 0, 0));
	fractalCreator.addRange(0.1, RGB(0, 255, 0));
	fractalCreator.addRange(1.0, RGB(0, 255, 255));

	fractalCreator.run("Test.bmp");
}
