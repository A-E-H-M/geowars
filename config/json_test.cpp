#include <iostream>
#include <string>
//#include <fstream>
//#include <vector>
//#include <nlohmann/json.hpp>

#include "../include/geowars/config_components.hpp"
#include "../include/geowars/config.hpp"

using namespace GWars;

int main ()
{
GameConfig game("config.json");
configObject newGame = game.configInit();

std::cout << newGame.m_playerConfig.entity_type << std::endl;
std::cout << "Jine" << std::endl;

return 0;
}
