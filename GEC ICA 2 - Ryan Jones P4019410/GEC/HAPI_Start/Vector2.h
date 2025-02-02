// 2D Vector class
// Partially created for GEC - up to you to finish it off

#pragma once

// Required for sqrt:
#include <cmath>
#include <ostream>

class Vector2
{
public:
	// In small classes like this it is OK to make data public
	float x{ 0 };
	float y{ 0 };

	// Constructors
	Vector2() = default;
	Vector2(float newX, float newY) : x(newX), y(newY) {}

	// + operator. Returns the result of adding the rhs to this
	Vector2 operator + (const Vector2 &rhs) const
	{
		return Vector2(x + rhs.x, y + rhs.y);
	}

	// TODO
	// - operator. Returns the result of subtracting the rhs from this
	Vector2 operator - (const Vector2 &rhs) const
	{
		return Vector2(x - rhs.x, y - rhs.y);
	}

	// * operator. Returns the result of multiplying the rhs scaler to this
	Vector2 operator * (float rhs) const
	{
		return Vector2(x * rhs, y * rhs);
	}

	// *= operator. Alters this to be the result of multiplying by the rhs scaler. 
	// Returns a reference to this for chaining purposes
	Vector2& operator *= (float rhs)
	{
		this->x = (x * rhs);
		this->y = (y * rhs);
		return Vector2(x, y);
	}

	// += operator. Alters this to be the result of adding by the rhs scaler. 
	// Returns a reference to this for chaining purposes
	Vector2& operator += (float rhs)
	{
		this->x = (x + rhs);
		this->y = (y + rhs);
		return Vector2(x, y);
	}

	// += operator. Alters this to be the result of adding by the rhs Vector. 
	Vector2 operator += (Vector2 rhs)
	{
		this->x = (x + rhs.x);
		this->y = (y + rhs.y);
		return Vector2(x, y);
	}

	// *= operator. Alters this to be the result of subtracting by the rhs scaler. 
	// Returns a reference to this for chaining purposes
	Vector2& operator -= (float rhs)
	{
		this->x = (x - rhs);
		this->y = (y - rhs);
		return Vector2(x, y);
	}

	/*
	void vectorOutput()
	{
		std::cout << "Animated texture loaded in Sprite class" << std::endl;
	}
	*/

	// Returns the length (magnitude) of this vector
	float Length() const
	{
		return sqrt(x*x + y*y);
	}

	// Returns the squared length (squared magnitude) of this vector
	float SquaredLength() const
	{
		return (x*x + y*y);
	}

	// Normalises this vector so its length is 1
	// The resulting vector is known as a unit vector
	// Useful when you wish to just use the vector as a direction
	void NormaliseInPlace()
	{
		float len = Length();

		if (len == 0)
			return;

		x /= len;
		y /= len;
	}

	/*
	The dot product can be used to calculate the angle between 2 vectors.
	If both vectors are already unit vectors then the dot product returns the
	cosine of the angle between them. If they are not unit vectors then you must divide
	the result by the product of the vector lengths to get the cosine of the angle.
	Another use of the dot product is to find the distance of a point to a plane
	*/
	float Dot(const Vector2& other) const
	{
		return x * other.x + y * other.y;
	}

	/*
	The cross product gives a value which is 2 times the area of the triangle.
	Can also be used to find which rotation direction a vector is, relative to another (+-)
	*/
	float Cross(const Vector2 &other) const
	{
		return x * other.y - y * other.x;
	}

	Vector2 Lerp(const Vector2 &other) const
	{
		float speed = 1;
		Vector2 dir = Vector2 (other.x - this->x, other.y - this->y);
		dir.NormaliseInPlace();

		return Vector2 (this->x + (dir.x * speed), this->y + (dir.y * speed));
	}
};