#pragma once
/**
 * @file AIState.h
 * @author Alan Abraham P Kochumon
 * @date Created on: August 27, 2026
 *
 * @brief AI State interface.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include <string>

namespace tower_defense::comp
{
    /// Forward declaration
    class AIComponent;

    class AIState
    {
    public:
        explicit AIState(AIComponent* owner) noexcept: _owner{ owner } {}

        virtual void update(float deltaTime) noexcept = 0;

        /// Transition from this state.
        virtual void onExit() noexcept = 0;

        /// Transition into this state.
        virtual void onEnter() noexcept = 0;

        /// Get the name of this state
        virtual std::string getName() noexcept = 0;

    protected:
        AIComponent* _owner;
    };
} // namespace tower_defense::comp
