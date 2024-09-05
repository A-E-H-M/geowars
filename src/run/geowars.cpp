#include <iostream>
#include "../include/geowars/vec2.h"
#include "../include/geowars/entity.h"

#include "../include/geowars/game.h"

int main ()
{
	Game g("config.txt");
	g.run();
}
