#include "Rectangle.h"
#include <algorithm>

Rectangle::~Rectangle()
{
}

bool Rectangle::isCompletelyContainedBy(const Rectangle &other) const
{
	if (other.left < left && other.top < top && other.right > right && other.bottom > bottom)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Rectangle::isCompletelyOutsideOf(const Rectangle & other) const
{
	if (other.left > right || other.top > bottom || other.right < left || other.bottom < top)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Rectangle::translate(int dX, int dY)
{
	left += dX;
	right += dX;
	top += dY;
	bottom += dY;
}

void Rectangle::clipTo(const Rectangle & destRect)
{
	left = std::max(left, destRect.left);
	right = std::min(right, destRect.right);
	top = std::max(top, destRect.top);
	bottom = std::min(bottom, destRect.bottom);
}