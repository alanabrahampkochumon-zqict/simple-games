/**
 * @file MoveComponent.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: August 31, 2026
 *
 * @brief Implementation of member functions declared in MoveComponent.h
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "MoveComponent.h"

#include "actor/Actor.h"

#include <math/Utils.h>

namespace tower_defense::comp
{
    void MoveComponent::update(const float deltaTime) noexcept
    {
        // Update the actors position and rotation if the speeds are not zero
        if (!math::nearZero(_forwardSpeed))
        {
            auto position      = _owner->getPosition();
            const auto forward = _owner->getForward();
            position += forward * _forwardSpeed * deltaTime;
            _owner->setPosition(position);
        }
        if (!math::nearZero(_angularSpeed))
        {
            auto rotation = _owner->getRotation();
            rotation += _angularSpeed * deltaTime;

            _owner->setRotation(rotation);
        }
    }

} // namespace tower_defense::comp
