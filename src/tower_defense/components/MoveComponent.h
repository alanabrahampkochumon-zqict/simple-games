#pragma once
/**
 * @file MoveComponent.h
 * @author Alan Abraham P Kochumon
 * @date Created on: August 31, 2026
 *
 * @brief Component for handling entity movement.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "Component.h"

namespace tower_defense::comp
{
    class MoveComponent: public Component
    {
    public:
        explicit MoveComponent(actor::Actor* owner, int updateOrder = 100) noexcept: Component{ owner, updateOrder } {}

        void update(float deltaTime) noexcept override;

        void setForwardSpeed(const float speed) { _forwardSpeed = speed; }
        void setAngularSpeed(const float speed) { _angularSpeed = speed; }

        [[nodiscard]] constexpr float getForwardSpeed() const noexcept { return _forwardSpeed; }
        [[nodiscard]] constexpr float getAngularSpeed() const noexcept { return _angularSpeed; }


    private:
        float _forwardSpeed{}, _angularSpeed{};
    };
} // namespace tower_defense::comp
