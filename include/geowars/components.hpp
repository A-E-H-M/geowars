#pragma once

#include "vec2.hpp"
#include <SFML/Graphics.hpp>

// Entity position and movement properties
class CTransform
{	
	public:
		Vec2 pos		= { 0.0, 0.0 };
		Vec2 velocity	= { 0.0, 0.0 };
		float angle		= 0;

		CTransform(const Vec2 & p, const Vec2 & v, float a)
			: pos(p), velocity(v), angle(a) {}
};

// Entity graphic properties
class CShape
{	
	public:
		sf::CircleShape circle;

		CShape(float radius, int points, const sf::Color & fill, const sf::Color & outline, float thickness)
			: circle(radius, points)
		{
			circle.setFillColor(fill);
			circle.setOutlineColor(outline);
			circle.setOutlineThickness(thickness);
			circle.setOrigin(radius, radius);
		}
};

// Entity collision properties
class CCollision
{	
	public:
		sf::FloatRect boundingBox;

		CCollision(sf::FloatRect bB)
			: boundingBox(bB) {}
};

// Game score properties
class CScore
{	
	public:
		int score		= 0;
		
		CScore(int s)
			: score(s) {}
};

// Entity lifespan properties
class CLifespan
{	
	public:
		int remaining	= 0;
		int total		= 0;
		CLifespan(int total)
			: remaining(total), total(total) {}
};

// User input properties
class CInput
{	
	public:
		bool up			= false;
		bool left		= false;
		bool right		= false;
		bool down		= false;
		bool shoot		= false;

		CInput() {}
};
