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

#include <cstdint>

namespace tower_defense
{
    namespace comp
    {
        enum class AIState : uint8_t
        {
            PATROL,
            DEATH,
            ATTACK
        };

        class AIComponent: Component
        {
        public:
            explicit AIComponent(actor::Actor* owner) noexcept;

            void update(float deltaTime) noexcept override;

            void updateState(AIState state) noexcept;

        private:
            void _updatePatrol(float deltaTime) noexcept;
            void _updateDeath(float deltaTime) noexcept;
            void _updateAttack(float deltaTime) noexcept;


            //+=+=+=+=+=+=
            // VARIABLES
            //+=+=+=+=+=+=
            AIState _state{ PATROL };
        };
    } // namespace comp
} // namespace tower_defense
