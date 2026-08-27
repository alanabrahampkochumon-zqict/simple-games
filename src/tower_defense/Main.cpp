#include "Game.h"

int main()
{
    tower_defense::Game game{};
    if (game.initialize())
    {
        game.run();
    }
    game.shutdown();
}
