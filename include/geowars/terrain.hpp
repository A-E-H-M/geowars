#pragma once

#include <string>
#include <string_view>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

namespace GWars
{
	class Terrain
	{
	public:
		Terrain(const sf::Texture& texture_type, std::string_view name_type, int difficulty)
				: t_texture(texture_type),
				t_type(name_type),
				t_difficulty(difficulty)
				{};
		const sf::Texture& terrain_texture() { return t_texture; }
		const std::string& terrain_type() { return t_type; }
		const int& terrain_difficulty() { return t_difficulty; }
		
	//private:
		sf::Texture t_texture;
		std::string t_type;
		int t_difficulty;
	};

} // End namespace