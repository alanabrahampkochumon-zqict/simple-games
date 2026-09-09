/**
 * @file Main.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: September 03, 2026
 *
 * @brief Main entry point.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "Game.h"

int main()
{
    fps::Game game;
    if (game.initialize())
    {
        game.run();
    }
    game.shutdown();
}
