#include "../include/geowars/vec2.hpp"
#include <math.h>

//Constructors
Vec2::Vec2()
{
}

Vec2::Vec2(float xin, float yin)
	: x(xin), y(yin)
{	
}

// Single operator overloads
Vec2 Vec2::operator + (const Vec2 & rhs) const
{
	return Vec2(x+rhs.x, y+rhs.y);
}

Vec2 Vec2::operator - (const Vec2& rhs) const
{
	return Vec2(x-rhs.x, y-rhs.y);
}

Vec2 Vec2::operator / (const float val) const
{
	return Vec2(x/val, y/val);
}

Vec2 Vec2::operator * (const float val) const
{
	return Vec2(x*val, y*val);
}

// Comparison overloads
bool Vec2::operator == (const Vec2 & rhs) const
{
	return (x == rhs.x && y == rhs.y);
}

bool Vec2::operator != (const Vec2& rhs) const
{
	return (x != rhs.x || y != rhs.y);
}

// Double operator overloads
void Vec2::operator += (const Vec2& rhs)
{
	x += rhs.x;
	y += rhs.y;
}

void Vec2::operator -= (const Vec2& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
}

void Vec2::operator *= (const float val)
{
	x *= val;
	y *= val;
}

void Vec2::operator /= (const float val)
{
	x /= val;
	y /= val;
}

// Physics functions
float Vec2::dist(const Vec2 & rhs) const
{
	// TODO: Write function
	return 0;
}

void Vec2::normalize()
{
	// TODO: Write function
}

float Vec2::length()const
{
	// TODO: Write function
	return 0;
}
