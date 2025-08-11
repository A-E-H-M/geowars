#include "geowars/window_manager.hpp"

namespace GWars
{
	Window_Manager::Window_Manager()
	{	
	}

	std::shared_ptr<sf::RenderWindow> Window_Manager::add_window(const CWindow& _window)
	{
		auto w_window = std::shared_ptr<sf::RenderWindow>(new sf::RenderWindow);
		w_window->create(sf::VideoMode(_window.width, _window.height), _window.window_title);
		w_window->setFramerateLimit(_window.frame_rate);
		all_windows.push_back(w_window);
		return w_window;
	}
}; // End namespace