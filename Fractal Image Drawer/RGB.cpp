#include "pch.h"
#include "RGB.h"



RGB::RGB(double r, double g, double b) : _r(r), _g(g), _b(b)
{
}

RGB operator-(const RGB& first, const RGB& second)
{
	return RGB(first._r - second._r, first._g - second._g, first._b - second._b);
}