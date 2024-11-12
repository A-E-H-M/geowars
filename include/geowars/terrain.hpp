#pragma once

#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class Terrain
{
public:
	Terrain(int difficulty, std::string name_type, const sf::Texture& texture_type)
			: t_difficulty(difficulty),
			  t_type(name_type),
			  t_texture(texture_type)
			{}
	const sf::Texture& terrain_texture();
	const int& terrain_difficulty();
	const std::string& terrain_type();
	
private:
	int t_difficulty;
	std::string t_type;
	sf::Texture t_texture;
};


