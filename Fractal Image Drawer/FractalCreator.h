#pragma once

#include <string>

struct Zoom;

class FractalCreator
{
public:
	FractalCreator();
	~FractalCreator();

	void calculateIteration();
	void drewFractal();
	void addZoom(const Zoom& zoom);
	void writeBitmap(std::string name);
};

