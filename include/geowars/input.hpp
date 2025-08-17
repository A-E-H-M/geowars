#pragma once

#include <SFML/System.hpp>

#include "geowars/entity.hpp"

namespace GWars
{
    class Input
    {
        private:
            void keyboardPressed(const sf::Event& event, class Game& game);
            void keyboardReleased(const sf::Event& event, class Game& game);
            void mouseButtonPressed(const sf::Event& event, class Game& game);

        public:
            Input(){};
            void userInput(const sf::Event& event, class Game& game);
    };
}