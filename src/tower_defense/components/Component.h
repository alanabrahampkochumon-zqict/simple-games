#pragma once
/**
 * @file Component.h
 * @author Alan Abraham P Kochumon
 * @date Created on: August 26, 2026
 *
 * @brief Component interface.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

namespace tower_defense
{
    namespace actor
    {
        /// Forward declaration
        class Actor;
    } // namespace actor

    namespace comp
    {
        class Component
        {
        public:
            /**
             * @brief Create a component for a given actor.
             *
             * @param owner       The actor that owns this component.
             * @param updateOrder The order for update. Lower order indicates earlier updates. Default: 100
             */
            explicit Component(actor::Actor* owner, const int updateOrder = 100) noexcept
                : _owner{ owner }, _updateOrder{ updateOrder }
            {}

            virtual ~Component() = default;

            virtual void update([[maybe_unused]] const float deltaTime) noexcept {}

            /// Process the input.
            /// @param keyState The keycode to process. 1-to-1 mapping to SDL3 keycodes.
            virtual void processInput([[maybe_unused]] const bool* keyState) noexcept {}

            [[nodiscard]] int getUpdateOrder() const { return _updateOrder; }

        private:
            [[maybe_unused]] actor::Actor* _owner;
            int _updateOrder{};
        };
    } // namespace comp
} // namespace tower_defense
