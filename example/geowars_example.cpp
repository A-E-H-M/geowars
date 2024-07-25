// COMP4300 - Game Programming - Assignment 2 - Geometry Wars

//#include <SFML/Graphics.hpp>
#include <iostream>
#include "../include/geowars/vec2.h"
#include "../include/geowars/entity.h"

#include "../include/geowars/game.h"

int main ()
{
	Game g("config.txt");
	g.run();
}
