#pragma once

namespace GWars
{
    class Game; // Forward declaration

    class Movement
    {
        private:
            void updateSpeed(Game& game);
            void inputMovement(Game& game);
        public:
            Movement(){};
            void updatePlayer(Game& game);
    };
}