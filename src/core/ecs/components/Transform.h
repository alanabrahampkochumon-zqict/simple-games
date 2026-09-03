#pragma once
/**
 * @file Transform.h
 * @author Alan Abraham P Kochumon
 * @date Created on: September 03, 2026
 *
 * @brief Transform component.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include <math/SimpleMath.h>

namespace ecs::comp
{
    struct Transform
    {
        math::Vec3 position;
        math::Quat rotation;
        math::Vec3 scale;
    };
}