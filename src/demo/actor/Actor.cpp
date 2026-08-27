/**
 * @file Actor.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: August 27, 2026
 *
 * @brief Implementation of member functions declared in Actor.h
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Actor.h"
#include "Game.h"

namespace tower_defense::actor
{

    Actor::Actor(Game* owner) noexcept: _owner{ owner } { _owner->addActor(this); }

    Actor::~Actor() noexcept { _owner->removeActor(this); }

    void Actor::update(const float deltaTime) noexcept
    {
        updateComponents(deltaTime);
        updateActor(deltaTime);
    }

    void Actor::updateComponents(const float deltaTime) const noexcept
    {
        for (const auto& comp : _components)
        {
            comp->update(deltaTime);
        }
    }

    void Actor::addComponent(comp::Component* comp) noexcept { _components.insert(comp); }

    void Actor::removeComponent(comp::Component* comp) noexcept { _components.erase(comp); }

    void Actor::processInput(const bool* keyState) noexcept
    {
        if (_state == ACTIVE)
        {
            for (const auto comp : _components)
            {
                comp->processInput(keyState);
            }
            processActorInput(keyState);
        }
    }
} // namespace tower_defense::actor
