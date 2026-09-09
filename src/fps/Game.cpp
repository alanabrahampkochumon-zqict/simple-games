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

    bool Game::initialize() noexcept
    {
        SDL_SetAppMetadata(GAME_TITLE, GAME_VERSION, GAME_ID);
        if (!SDL_Init(SDL_INIT_VIDEO))
        {
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "There was an error initializing SDL.\n%s", SDL_GetError());
            return false;
        }

        _window = SDL_CreateWindow(GAME_TITLE, INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT, 0);
        if (!_window)
        {
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "There was an error creating the window.\n%s", SDL_GetError());
            return false;
        }

        _isRunning = true;
        return true;
    }

    void Game::run() noexcept
    {
        while (_isRunning)
        {
            _processInput();
            _update();
            _render();
        }
    }

    void Game::shutdown() const noexcept
    {
        // TODO: Shutdown down systems
        SDL_DestroyWindow(_window);
        SDL_Quit();
    }

    void Game::_processInput() noexcept
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_EVENT_QUIT:
                    _isRunning = false;
                    break;
                default:
                    break;
            }
        }
    }

    void Game::_update() noexcept {}

    void Game::_render() const noexcept {}

} // namespace fps
