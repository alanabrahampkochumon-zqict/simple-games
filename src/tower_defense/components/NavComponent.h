#pragma once
/**
 * @file NavComponent.h
 * @author Alan Abraham P Kochumon
 * @date Created on: August 31, 2026
 *
 * @brief Component handling AI navigation.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "MoveComponent.h"

#include <math/SimpleMath.h>


namespace tower_defense::comp
{
    class NavComponent: public MoveComponent
    {
    public:
        explicit NavComponent(actor::Actor* owner, int updateOrder = 100) noexcept: MoveComponent{ owner, updateOrder }
        {}

        /// Rotate the entity in the direction of another entity, given its position
        void turnTo(math::Vec2 position) noexcept;

        void update(float deltaTime) noexcept override;

    private:
        math::Vec2 _nextPoint{};
    };

} // namespace tower_defense::comp
