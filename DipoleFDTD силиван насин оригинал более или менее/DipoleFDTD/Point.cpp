#include "stdafx.h"
#include "Point.h"
#include <iostream>

Point::Point()
{
	x = 0;	y = 0; z = 0;
}
Point::Point(double X, double Y, double Z)
{
	x = X; y = Y; z = Z; 
};
Point::operator Point() const
{
	return Point(x, y, z);
};
bool Point::operator == (Point point)
{
	double diffX = abs(x - point.x);
	double diffY = abs(y - point.y);
	if ((diffX < 1.e-16) && (diffY < 1.e-16))
	{
		return true;
	}
	else
		return false;

};
bool Point::operator != (Point point)
{
	if (*this == point)
	{
		return false;
	}
	else
		return true;
};
bool Point::operator > (const Point & right) const
{
	double r1 = x * x + y * y;
	double r2 = right.x * right.x + right.y * right.y;
	double alpha1 = atan2(y, x);
	if (alpha1 < 0)
		alpha1 = alpha1 + 2 * 3.1415;
	double alpha2 = atan2(right.y, right.x);
	if (alpha2 < 0)
		alpha2 = alpha2 + 2 * 3.1415;
	if (r1 > r2)
	{
		return true;
	}
	else if ((abs(r1 - r2) == 0 ) && (alpha1 > alpha2))
	{
		return true;
	}
	else
		return false;
	
};
bool Point::operator < (const Point & right) const
{
	double r1 = x * x + y * y;
	double r2 = right.x * right.x + right.y * right.y;
	double alpha1 = atan2(y, x);

	double alpha2 = atan2(right.y, right.x);
	if (r1 < r2)
	{
		return true;
	}
	else
	{
		if ((abs(r1 - r2) == 0))
		{
			if (alpha1 < alpha2)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
}
