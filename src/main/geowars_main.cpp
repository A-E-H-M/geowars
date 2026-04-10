#include <string>

#include "geowars/game.hpp"
#include "geowars/config.hpp"

using namespace GWars;

int main(int argc, char* argv[])
{	
	auto game_config = Init("config.json");
	Game g(game_config);
	g.run();

	return 0;
}
