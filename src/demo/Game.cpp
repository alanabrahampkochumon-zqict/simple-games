/**
 * @file Game.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: August 26, 2026
 *
 * @brief Implementation of member functions in declared Game.h
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Game.h"

#include <SDL3/SDL.h>


namespace tower_defense
{

    bool Game::initialize() noexcept
    {
        SDL_SetAppMetadata(GAME_NAME, VERSION, ID);
        if (!SDL_Init(SDL_INIT_VIDEO))
        {
            SDL_Log("There was an error initializing SDL\n%s", SDL_GetError());
            return false;
        }

        _window = SDL_CreateWindow(GAME_NAME, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
        if (_window == nullptr)
        {
            SDL_Log("There was an error initializing SDL window\n%s", SDL_GetError());
            return false;
        }

        _renderer = SDL_CreateRenderer(_window, nullptr);
        if (_renderer == nullptr)
        {
            SDL_Log("There was an error initializing SDL renderer\n%s", SDL_GetError());
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

    void Game::shutdown() noexcept
    {
        SDL_DestroyRenderer(_renderer);
        SDL_DestroyWindow(_window);
    }

    void Game::_processInput()
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

    void Game::_update()
    {
        // TODO: Update Loop
    }

    void Game::_render()
    {
        SDL_SetRenderDrawColor(_renderer, CLEAR_COLOR[0], CLEAR_COLOR[1], CLEAR_COLOR[2], CLEAR_COLOR[3]);
        SDL_RenderClear(_renderer);

        // TODO: Put rendering logic here

        SDL_RenderPresent(_renderer);
    }

} // namespace tower_defense
