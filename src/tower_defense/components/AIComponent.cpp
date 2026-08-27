/**
 * @file AIComponent.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: August 27, 2026
 *
 * @brief Implementation of member functions declared in AIComponent.h
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "AIComponent.h"

#include <SDL3/SDL.h>

namespace tower_defense::comp
{
    AIComponent::AIComponent(actor::Actor* owner) noexcept: Component{ owner } {}

    void AIComponent::update(const float deltaTime) noexcept
    {
        switch (_state)
        {
            case PATROL:
                _updatePatrol(deltaTime);
                break;
            case DEATH:
                _updateDeath(deltaTime);
                break;
            case ATTACK:
                _updateAttack(deltaTime);
                break;
            default:
                SDL_Log("Invalid AI state!");
                break;
        }
    }
    void AIComponent::updateState(const AIState state) noexcept
    {
        // TODO: Before transition (Exit function)
        // call corresponding function

        _state = state;

        // TODO: After transition (Enter function)
        // call corresponding function
    }


    void AIComponent::_updatePatrol(const float deltaTime) noexcept
    {
        // TODO: Impl
        SDL_Log("Updating Patrol %0.03f", deltaTime);
    }


    void AIComponent::_updateDeath(const float deltaTime) noexcept
    {
        // TODO: Impl
        SDL_Log("Updating Death %0.03f", deltaTime);
    }


    void AIComponent::_updateAttack(const float deltaTime) noexcept
    {
        // TODO: Impl
        SDL_Log("Updating Attack %0.03f", deltaTime);
    }
} // namespace tower_defense::comp
