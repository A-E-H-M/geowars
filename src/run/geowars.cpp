#include <iostream>
#include "../include/geowars/vec2.hpp"
#include "../include/geowars/entity.hpp"

#include "../include/geowars/game.hpp"

int main()
{	
	Game g("config.txt");
	g.run();
}
