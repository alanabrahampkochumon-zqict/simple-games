/**
 * @file Game.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: September 03, 2026
 *
 * @brief Implementation of member functions declared in Game.h
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Game.h"

namespace fps
{

    constexpr bool Game::initialize() noexcept { return true; }

    constexpr void Game::run() const noexcept
    {
        while (_isRunning)
        {
            // RUN
        }
    }

    constexpr void Game::shutdown() const noexcept
    {
        // TODO: Shutdown down systems
    }

} // namespace fps
