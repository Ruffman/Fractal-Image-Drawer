#include "pch.h"
#include "ZoomList.h"
#include "Zoom.h"

using namespace std;

ZoomList::ZoomList(int width, int height) : _width(width), _height(height)
{
}


ZoomList::~ZoomList()
{
}

void ZoomList::add(const Zoom& zoom)
{
	_zoomList.push_back(zoom);

	_xCenter += (zoom._x - _width / 2) * _scale;
	_yCenter += (zoom._y - _height / 2) * _scale;

	_scale *= zoom._scale;
}

pair<double, double> ZoomList::calculate(int x, int y)
{
	double xFractal = (x - _width / 2)*_scale + _xCenter;
	double yFractal = (y - _height / 2)*_scale + _yCenter;

	return pair<double, double>(xFractal, yFractal);
}
