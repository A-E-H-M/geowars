#pragma once

struct Vec2
{	
	float x;
	float y;

	Vec2() : x(0.0), y(0.0) {}
	Vec2(float xin, float yin) : x(xin), y(yin) {}

	// Single operator overloads
	Vec2 operator + (const Vec2 & rhs) const { return Vec2(x + rhs.x, y + rhs.y); }
	Vec2 operator - (const Vec2 & rhs) const { return Vec2(x - rhs.x, y - rhs.y); }	
	Vec2 operator / (const float val) const { return Vec2(x / val, y / val); }	
	Vec2 operator * (const float val) const { return Vec2(x * val, y * val); }	

	// Comparison operator overloads
	bool operator == (const Vec2 & rhs) const { return (x == rhs.x && y == rhs.y); }
	bool operator != (const Vec2 & rhs) const { return (x != rhs.x, y != rhs.y); }
		
	// Double operator overloads
	void operator += (const Vec2 & rhs) { x += rhs.x; y += rhs.y; }
	void operator -= (const Vec2 & rhs) { x -= rhs.x; y += rhs.y; }
	void operator *= (const float val) { x *= val; y *= val; }
	void operator /= (const float val) { x /= val; y /= val; }

		// TODO: Finish physics calculations
		// float dist(const Vec2 & rhs) const;
		// void normalize();
		// float length() const;
};
