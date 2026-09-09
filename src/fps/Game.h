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

#include <SDL3/SDL.h>

namespace fps
{
    class Game
    {
    public:
        bool initialize() noexcept;

        void run() noexcept;

        void shutdown() const noexcept;


    private:
        bool _isRunning{ false };

        SDL_Window* _window{ nullptr };
        SDL_GPUDevice* _gpu{ nullptr };


        /// Process the input from IO devices like keyboard
        void _processInput() noexcept;
        /// Update the game state
        void _update() noexcept;
        /// Render the current game state
        void _render() const noexcept;

    public:
        static constexpr size_t INITIAL_WINDOW_WIDTH  = 1280;
        static constexpr size_t INITIAL_WINDOW_HEIGHT = 720;

        static constexpr auto GAME_TITLE   = "First Person Shooter";
        static constexpr auto GAME_VERSION = "1.0";
        static constexpr auto GAME_ID      = "com.simple.games.fps";
    };

} // namespace fps
