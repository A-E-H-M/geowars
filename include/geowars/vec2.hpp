#pragma once

namespace GWars
{
	// 2D vector template class for position and velocity calculations
	template <typename T>
	struct Vec2
	{
		T x{};
		T y{};

		Vec2(T a, T b) : x(a), y(b) {}

		// Single operator overloads
		Vec2 operator + (const Vec2& rhs) const { return Vec2(x + rhs.x, y + rhs.y); }
		Vec2 operator - (const Vec2& rhs) const { return Vec2(x - rhs.x, y - rhs.y); }	
		Vec2 operator / (const float val) const { return Vec2(x / val, y / val); }	
		Vec2 operator * (const float val) const { return Vec2(x * val, y * val); }	

		// Comparison operator overloads
		bool operator == (const Vec2& rhs) const { return (x == rhs.x && y == rhs.y); }
		bool operator != (const Vec2& rhs) const { return (x != rhs.x, y != rhs.y); }
			
		// Double operator overloads
		void operator += (const Vec2& rhs) { x += rhs.x; y += rhs.y; }
		void operator -= (const Vec2& rhs) { x -= rhs.x; y += rhs.y; }
		void operator *= (const float val) { x *= val; y *= val; }
		void operator /= (const float val) { x /= val; y /= val; }

			// TODO: Finish physics calculations
			// float dist(const Vec2 & rhs) const;
			// void normalize();
			// float length() const;
	};
} // End namespace