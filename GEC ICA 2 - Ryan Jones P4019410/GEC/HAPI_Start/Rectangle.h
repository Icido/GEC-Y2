#pragma once
class Rectangle
{
private:
	int left{ 0 }, right{ 0 }, top{ 0 }, bottom{ 0 };

public:
	//Default Rectangle constructor
	Rectangle() = default;
	//Left/Right/Top/Bottom Rectangle constructor
	Rectangle(int left, int right, int top, int bottom) : left(left), right(right), top(top), bottom(bottom) {}
	//Width/Height Rectangle constructor, assume Left = 0 and Top = 0
	Rectangle(int width, int height) : left(0), right(width), top(0), bottom(height) {}

	~Rectangle();

	//Functions used to return a side of the rectangle or calculate the width/height of the rectangle
	int getLeft() const { return left;  }
	int getTop() const { return top; }
	int Width() const { return right - left; }
	int Height() const { return bottom - top; }

	//Does the passed-in rectangle completely contain this rectangle?
	//If this rectangle is completely inside "other" rectangle, return true
	//If not, return false
	bool isCompletelyContainedBy(const Rectangle &other) const;

	//Is this rectangle completely outside of the passed-in rectangle?
	//If yes, return true
	//If not, return false
	bool isCompletelyOutsideOf(const Rectangle &other) const;

	//Used to translate a rectangle on the screen space
	void translate(int dX, int dY);

	//Used to clip this rectangle to passed-in rectangle
	void clipTo(const Rectangle &destRect);
};

