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

#include "AIState.h"

#include <SDL3/SDL.h>

namespace tower_defense::comp
{
    AIComponent::AIComponent(actor::Actor* owner) noexcept: Component{ owner } {}

    void AIComponent::update(const float deltaTime) noexcept
    {
        if (_currentAIState != nullptr)
        {
            _currentAIState->update(deltaTime);
        }
    }

    void AIComponent::changeState(const std::string& stateName) noexcept
    {
        // Exit the current state if it exist
        if (_currentAIState)
        {
            _currentAIState->onEnter();
        }

        // If the provided state is valid then, call it's enter function
        if (const auto iterator = _aiStates.find(stateName); iterator != _aiStates.end())
        {
            _currentAIState = iterator->second;
            _currentAIState->onEnter();
        }
        else
        {
            SDL_Log(
                "State with name %s not found in the registry.\nTry registering the state first using registerState",
                stateName.c_str());
            _currentAIState = nullptr;
        }
    }


    void AIComponent::registerState(AIState* state) noexcept { _aiStates.emplace(state->getName(), state); }

} // namespace tower_defense::comp
