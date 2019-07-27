// Fractal Image Drawer.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include "pch.h"
#include <iostream>
#include <cstdint>
#include <memory>
#include <math.h>

#include "Zoom.h"
#include "FractalCreator.h"

using namespace std;

int main()
{
	int const WIDTH = 800;
	int const HEIGHT = 600;

	FractalCreator fractalCreator(WIDTH, HEIGHT);

	fractalCreator.addZoom(Zoom(WIDTH / 2, HEIGHT / 2, 4.0 / WIDTH));
	fractalCreator.addZoom(Zoom(300, HEIGHT / 2, 0.9));
	fractalCreator.addZoom(Zoom(388, HEIGHT - 160, 0.1));
	fractalCreator.addZoom(Zoom(557, HEIGHT - 310, 0.1));

	fractalCreator.calculateIteration();
	fractalCreator.drawFractal();
	fractalCreator.writeBitmap("Test.bmp");
}
