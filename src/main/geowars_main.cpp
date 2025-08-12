#include <string>

#include "geowars/game.hpp"
#include "geowars/config.hpp"

using namespace GWars;

int main()
{	
	std::string config_file_path = "config.json";
	GameConfig game(config_file_path);
	Game g(game.configInit());
	g.run();
}