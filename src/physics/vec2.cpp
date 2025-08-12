#include <math.h>

#include "geowars/vec2.hpp"

namespace GWars
{
	// TODO: Finish physics calculations
	/*
	// Physics functions
	Vec2 Vec2::dist(const Vec2 & lhs, const Vec2 & rhs) const
	//float Vec2::dist(const Vec2 & rhs) const
	{
		return rhs - lhs;
	}

	Vec2 Vec2::normalize(Vec2 & lhs, const Vec2 & rhs)
	{
		// Getting distance between player and mouse click
		Vec2 tempVec = dist(lhs, rhs);

		// Getting angle
		lhs.angle = atan2f(tempVec.y, tempVec.x);

		// Normalizing vector
		float tempLeng = (tempVec *= tempVec);
		
		return tempVec / tempLeng;
	}

	Vec2 Vec2::velocity(const Vec2 & rhs, const float & speed) const
	{
		return rhs * speed;
	}
	*/
}; // End namespace
