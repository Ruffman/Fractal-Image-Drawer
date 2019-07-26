#pragma once

class Mandelbrot
{
public:
	static const int MAX_ITERATIONS = 100;

public:
	Mandelbrot();
	~Mandelbrot();

	static int getIterations(double x, double y);
};

