#include <string>

#include "geowars/game.hpp"
#include "geowars/config.hpp"

using namespace GWars;

int main(int argc, char* argv[])
{	
	//std::string config_file_path = "config.json";
	GameConfig game("config.json");
	Game g(game.configInit());
	g.run();

	return 0;
}
