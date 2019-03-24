#pragma once;
class Point
{
public:
	Point();
	Point(double X, double Y, double Z);
	double x, y, z;
	operator Point() const;
	bool operator == (Point point);
	bool operator != (Point point);
	bool operator > (const Point & right) const;
	bool operator < (const Point & right) const;
};