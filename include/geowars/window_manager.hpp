#pragma once

#include <vector>
#include <memory>

#include <SFML/Graphics.hpp>

#include "config.hpp"

// Template vector for storing SFML window objects
using WindowVec = std::vector<std::shared_ptr<sf::RenderWindow>>;

// Manages all windows
class Window_Manager 
{
	private:
		// Named vector for all windows
		WindowVec all_windows;
	public:
		Window_Manager();
		// Add a window to the vector of windows based on the window congfiguration passed by reference
		std::shared_ptr<sf::RenderWindow> add_window(const CWindow& _window);	
};
