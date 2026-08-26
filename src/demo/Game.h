#pragma once
/**
 * @file Game.h
 * @author Alan Abraham P Kochumon
 * @date Created on: August 26, 2026
 *
 * @brief Defines the tower defense game.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include <SDL3/SDL.h>
#include <array>
#include <cstdint>

namespace tower_defense
{

    class Game
    {

    public:
        /// Initialize the game instance.
        bool initialize() noexcept;

        /// Run the game application
        void run() noexcept;

        /// Shutdown and cleanup the application
        void shutdown() noexcept;

    private:
        /// Process the input from IO devices like keyboard
        void _processInput();

        /// Update the game state
        void _update();

        /// Render the current game state
        void _render();


    private:
        //+=+=+=+=+=+=+=+=+=+=
        //  MEMBER VARIABLES
        //+=+=+=+=+=+=+=+=+=+=

        bool _isRunning{ false };

        SDL_Window* _window{ nullptr };
        SDL_Renderer* _renderer{ nullptr };



        //+=+=+=+=+=+=+=+=+=+=
        //    CONSTANTS
        //+=+=+=+=+=+=+=+=+=+=

        static constexpr auto GAME_NAME       = "Tower Defense";
        static constexpr auto ID              = "com.app.tower.defense";
        static constexpr auto VERSION         = "1.0";
        static constexpr size_t WINDOW_WIDTH  = 1280;
        static constexpr size_t WINDOW_HEIGHT = 720;
        static constexpr std::array<uint8_t, 4> CLEAR_COLOR{ 255, 255, 255, 255 };
    };
} // namespace tower_defense
