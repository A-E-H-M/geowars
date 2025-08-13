#pragma once

#include <string>
#include <string_view>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

namespace GWars
{
	class Terrain
	{
	public:
		Terrain(int difficulty, std::string_view name_type, const sf::Texture& texture_type)
				: t_difficulty(difficulty),
				t_type(name_type),
				t_texture(texture_type)
				{};
		const sf::Texture& terrain_texture() { return t_texture; }
		const int& terrain_difficulty() { return t_difficulty; }
		const std::string& terrain_type() { return t_type; }
		
	private:
		int t_difficulty;
		std::string t_type;
		sf::Texture t_texture;
	};
} // End namespace