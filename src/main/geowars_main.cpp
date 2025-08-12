#include <iostream>

#include "geowars/game.hpp"

using namespace GWars;

int main()
{	
	Game g("config.json");
	g.run();
}
