/**
 * @file NavComponent.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: August 31, 2026
 *
 * @brief Implementation of member functions declared in NavComponent.h
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "NavComponent.h"

#include "actor/Actor.h"

namespace tower_defense::comp
{

    void NavComponent::turnTo(const math::Vec2 position) noexcept
    {
        // Get the direction vector from the enemy to the player
        const auto direction = position - _owner->getPosition();

        // Compute the angle between the player and the enemy
        const float angle = math::atan2(direction.x, direction.y);

        _owner->setRotation(angle);
    }


    void NavComponent::update(const float deltaTime) noexcept
    {
        // TODO: Add impl
        MoveComponent::update(deltaTime);
    }
} // namespace tower_defense::comp
