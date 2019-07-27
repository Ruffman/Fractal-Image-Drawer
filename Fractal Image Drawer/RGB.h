#pragma once

struct RGB
{
public:
	double _r;
	double _g;
	double _b;

public:
	RGB(double  r, double g, double b);
};

RGB operator-(const RGB& first, const RGB& second);
