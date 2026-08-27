#pragma once
/**
 * @file AIComponent.h
 * @author Alan Abraham P Kochumon
 * @date Created on: August 27, 2026
 *
 * @brief Component for game AI.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Component.h"

#include <string>
#include <unordered_map>

namespace tower_defense::comp
{
    class AIState; /// Forward Declaration

    class AIComponent: Component
    {
    public:
        explicit AIComponent(actor::Actor* owner) noexcept;

        void update(float deltaTime) noexcept override;

        /// Change from the current AI state to another using it's name
        /// @note State must be registered first using the registerState function.
        void changeState(const std::string& stateName) noexcept;

        void registerState(AIState* state) noexcept;

    private:
        //+=+=+=+=+=+=
        // VARIABLES
        //+=+=+=+=+=+=
        std::unordered_map<std::string, AIState*> _aiStates{};
        AIState* _currentAIState{};
    };
} // namespace tower_defense::comp
