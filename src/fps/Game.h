#pragma once
/**
 * @file Game.h
 * @author Alan Abraham P Kochumon
 * @date Created on: September 03, 2026
 *
 * @brief Game class.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

namespace fps
{
    class Game
    {
    public:
        constexpr bool initialize() noexcept;

        constexpr void run() const noexcept;

        constexpr void shutdown() const noexcept;


    private:
        bool _isRunning {false};

    public:
        static constexpr size_t INITIAL_WINDOW_WIDTH = 1280;
        static constexpr size_t INITIAL_WINDOW_HEIGHT = 720;

        static constexpr auto GAME_TITLE = "First Person Shooter";
        static constexpr auto GAME_VERSION = "1.0";
        static constexpr auto GAME_ID = "com.simple.games.fps";
    };

} // namespace fps
