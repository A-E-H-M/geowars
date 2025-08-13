
#include "geowars/game.hpp"

int main(int argc, char* argv[])
{	
	std::string config_file_path = "config.json";
	GameConfig game(config_file_path);
	Game g(game.configInit());
	g.run();

	return 0;
}
