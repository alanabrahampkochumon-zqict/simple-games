#pragma once
/**
 * @file Actor.h
 * @author Alan Abraham P Kochumon
 * @date Created on: August 26, 2026
 *
 * @brief Actor interface class.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "components/Component.h"

#include <math/SimpleMath.h>
#include <unordered_set>

namespace tower_defense
{
    /// Forward declaration
    class Game;

    namespace actor
    {
        enum State
        {
            PAUSED,
            ACTIVE,
            DEAD
        };

        class Actor
        {
        public:
            explicit Actor(Game* owner) noexcept;
            Actor(Actor& actor) = default;
            virtual ~Actor() noexcept;


            /// Update called from game(non-overrideable)
            void update([[maybe_unused]] float deltaTime) noexcept;

            /// Update the components of the actor
            void updateComponents([[maybe_unused]] float deltaTime) const noexcept;

            /// Overrideable method to give additional functionality to inheriting actors.
            virtual void updateActor([[maybe_unused]] const float deltaTime) noexcept {}

            void addComponent(comp::Component* comp) noexcept;

            void removeComponent(comp::Component* comp) noexcept;

            /// Process the input.
            /// @param keyState The keycode to process. 1-to-1 mapping to SDL3 keycodes.
            void processInput(const bool* keyState) noexcept;

            /// Process the actor input.
            /// Overridable to provide additional functionality to deriving actors.
            /// @param keyState The keycode to process. 1-to-1 mapping to SDL3 keycodes.
            virtual void processActorInput([[maybe_unused]] const bool* keyState) noexcept {}


            //+=+=+=+=+=+=+=+=+=
            // GETTERS/SETTERS
            //+=+=+=+=+=+=+=+=+=
            [[nodiscard]] Game* getGame() const noexcept { return _owner; }

            [[nodiscard]] float getRotation() const noexcept { return _rotation; }

            [[nodiscard]] float getScale() const noexcept { return _scale; }

            [[nodiscard]] math::Vec2 getPosition() const noexcept { return _position; }

            [[nodiscard]] State getState() const noexcept { return _state; }

            /// Get the forward direction vector.
            [[nodiscard]] math::Vec2 getForward() const noexcept
            { return math::Vec2{ std::cos(_rotation), std::sin(_rotation) }; }



            void setRotation(const float rotation) { _rotation = rotation; }

            void setScale(const float scale) { _scale = scale; }

            void setPosition(const math::Vec2& position) { _position = position; }

            void setState(const State state) { _state = state; }

        private:
            State _state{ ACTIVE };
            float _rotation{}, _scale{};
            math::Vec2 _position{};

            Game* _owner;
            std::unordered_set<comp::Component*> _components{};
        };

    } // namespace actor
} // namespace tower_defense
