#pragma once

#include <vector>
#include <utility>

struct Zoom;

class ZoomList
{
private:
	int _width{ 0 };
	int _height{ 0 };
	double _xCenter{ 0 };
	double _yCenter{ 0 };
	double _scale{ 1.0 };
	std::vector<Zoom> _zoomList;

public:
	ZoomList() = default;
	ZoomList(int width, int height);
	~ZoomList();

	void add(const Zoom& zoom);
	std::pair<double, double> calculate(int x, int y);
};

