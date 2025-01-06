#pragma once

struct Vec2
{	
	float x;
	float y;

	Vec2() : x(0.0), y(0.0) {};
	Vec2(float xin, float yin) : x(xin), y(yin) {};
	Vec2 operator + (const Vec2 & rhs) const;
	Vec2 operator - (const Vec2 & rhs) const;
	Vec2 operator / (const float val) const;
	Vec2 operator * (const float val) const;
		
	bool operator == (const Vec2 & rhs) const;
	bool operator != (const Vec2 & rhs) const;
		
	void operator += (const Vec2 & rhs);
	void operator -= (const Vec2 & rhs);
	void operator *= (const float val);
	void operator /= (const float val);

		// TODO: Finish physics calculations
		// float dist(const Vec2 & rhs) const;
		// void normalize();
		// float length() const;
};
