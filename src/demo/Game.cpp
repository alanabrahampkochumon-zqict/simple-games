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
#include <format>

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

    void Game::addActor(actor::Actor* actor) noexcept
    {
        // Add the actor to actors list if the game is not currently
        // update, else add it the pending actors list
        if (_isUpdatingActors)
        {
            _pendingActors.emplace_back(actor);
        }
        else
        {
            _actors.emplace_back(actor);
        }
    }

    void Game::removeActor(actor::Actor* actor) noexcept
    {
        auto actorToRemove = std::ranges::find(_pendingActors, actor);
        if (actorToRemove != std::ranges::end(_pendingActors))
        {
            std::ranges::iter_swap(*actorToRemove, _pendingActors.back());
            _pendingActors.pop_back();
        }
        else if (actorToRemove = std::ranges::find(_actors, actor); actorToRemove != std::ranges::end(_actors))
        {
            std::ranges::iter_swap(*actorToRemove, _actors.back());
            _actors.pop_back();
        }
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
        // Frame Limit
        while (SDL_GetTicks() < _lastFrameTick + SYNC_TIME) {}

        // Calculate the delta time
        const auto currentTick = SDL_GetTicks();
        float deltaTime        = static_cast<float>(currentTick - _lastFrameTick) / 1000.0f;
        _lastFrameTick         = currentTick;
#ifndef NDEBUG
        // Clamp maximum delta time (useful for debug breaks)
        deltaTime = deltaTime > 0.05f ? 0.05f : deltaTime;
#endif

        // Update the actors
        _isUpdatingActors = true;
        for (const auto actor : _actors)
        {
            actor->update(deltaTime);
        }
        _isUpdatingActors = false;


        // Add pending actors to actors
        for (auto pendingActor : _pendingActors)
        {
            _actors.emplace_back(pendingActor);
        }
        // Clear pending actors
        _pendingActors.clear();


        // Delete dead actors
        for (const auto actor : _actors)
        {
            if (actor->getState() == actor::State::DEAD)
            {
                delete actor; // This removes the actor from the actor list
            }
        }


        auto title = std::format("{} ({} FPS)", GAME_NAME, static_cast<int>(1.0f / deltaTime));
        SDL_SetWindowTitle(_window, title.c_str());
        // SDL_Log("Delta time: %0.03f", deltaTime);
    }

    void Game::_render()
    {
        SDL_SetRenderDrawColor(_renderer, CLEAR_COLOR[0], CLEAR_COLOR[1], CLEAR_COLOR[2], CLEAR_COLOR[3]);
        SDL_RenderClear(_renderer);

        // TODO: Put rendering logic here

        SDL_RenderPresent(_renderer);
    }

} // namespace tower_defense
