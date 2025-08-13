#pragma once

#include <SFML/System.hpp>

#include "geowars/entity.hpp"

namespace GWars
{
    class Input
    {
        public:

            void userInput(const sf::Event& event, class Game& game);
            void keyboardPressed(const sf::Event& event, class Game& game);
            void keyboardReleased(const sf::Event& event, class Game& game);
            void mouseButtonPressed(const sf::Event& event, class Game& game);

            Input(){};
    };
}