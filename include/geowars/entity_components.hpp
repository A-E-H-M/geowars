#pragma once

#include <SFML/Graphics.hpp>

#include "geowars/vec2.hpp"

namespace GWars
{
	// Entity position and movement properties
	struct CTransform
	{	
		Vec2<int> pos;
		Vec2<int> velocity;
		Vec2<int> speed;
		float angle;

		CTransform(const Vec2<int>& p, const Vec2<int>& v, const float a)
			: pos(p), velocity(v), speed(v), angle(a) {}
	};

	// Entity graphic properties
	struct CShape
	{	
		sf::CircleShape circle;

		CShape(const float radius, const int points, const sf::Color& fill, const sf::Color& outline, const float thickness)
			: circle(radius, points)
			{
				circle.setFillColor(fill);
				circle.setOutlineColor(outline);
				circle.setOutlineThickness(thickness);
				circle.setOrigin(radius, radius);
			}
	};

	// Entity collision properties
	struct CCollision
	{	
		sf::FloatRect boundingBox;

		CCollision(const sf::FloatRect& bB)
			: boundingBox(bB) {}
	};

	// Game score properties
	struct CScore
	{	
		int score{0};
			
		CScore(const int s)
			: score(s) {}
	};

	// Entity lifespan properties
	struct CLifespan
	{	
		int remaining{0};
		int total{0};

		CLifespan(const int total)
			: remaining(total), total(total) {}
	};

	// User input properties
	struct CInput
	{	
		bool up			= false;
		bool left		= false;
		bool right		= false;
		bool down		= false;
		bool shoot		= false;
	};
} // End namespace