/**
 * @file Component.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: August 31, 2026
 *
 * @brief Implementation of member functions declared in Component.h
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "Component.h"

#include "actor/Actor.h"

namespace tower_defense::comp
{

    Component::Component(actor::Actor* owner, const int updateOrder) noexcept
        : _owner{ owner }, _updateOrder{ updateOrder }
    {
        // Add this component to the owning actor's component list
        // Shared functionality, creating a component will attach it to the owner
        _owner->addComponent(this);
    }


    Component::~Component() noexcept
    {
        // Remove this component from the actors component list
        _owner->removeComponent(this);
    }
} // namespace tower_defense::comp
