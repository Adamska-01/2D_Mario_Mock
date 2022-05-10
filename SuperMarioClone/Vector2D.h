#pragma once
#include <ostream>

class Vector2D
{
public:
	float x = 0.0f;
	float y = 0.0f;

	Vector2D();
	Vector2D(float x, float y);
	~Vector2D() {}

	// basic functions
	float dist(const Vector2D& v) const;
	bool empty() { return (x == 0 && y == 0) ? true : false; }

	/*The following operators simply return Vector2ds that
	  have operations performed on the relative (x, y) values*/
	Vector2D& operator=(const Vector2D&);

	Vector2D operator+(const Vector2D&) const;
	Vector2D operator-(const Vector2D&) const;
	Vector2D operator*(const Vector2D&) const;
	Vector2D operator/(const Vector2D&) const;

	Vector2D& operator+=(const Vector2D& v);
	Vector2D& operator-=(const Vector2D& v);
	Vector2D& operator*=(const Vector2D& v);
	Vector2D& operator/=(const Vector2D& v);

	Vector2D operator*(const float vl) const;

	bool operator==(const Vector2D& v) const;

	friend std::ostream& operator<<(std::ostream& out, const Vector2D& v);
};

