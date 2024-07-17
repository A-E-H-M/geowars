// COMP4300 - Game Programming - Assignment 2 - Geometry Wars

//#include <SFML/Graphics.hpp>
#include <iostream>
#include "vec2.h"
#include "entity.h"

#include "game.h"

int main ()
{
	/*
	std::vector<Entity> all_entities;
	Entity entity1(89, "player");
	all_entities.push_back(entity1);
	Entity entity2(5, "bullet");
	all_entities.push_back(entity2);

	for (auto e : all_entities)
	{
		std::cout << e.tag() << std::endl;
		std::cout << e.id() << std::endl;
	}
	*/	

	//Vec2 v1(100, 100);
	//Vec2 v2(300, 500);

	//Vec2 v3 = v1 + v2;
	//v1 /= -4.35;
	//std::cout << v3.x << " " << v3.y << std::endl;
	Game g("config.txt");
	g.run();
}
