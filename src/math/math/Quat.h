#pragma once
/**
 * @file Quat.h
 * @author Alan Abraham P Kochumon
 * @date Created on: September 02, 2026
 *
 * @brief Quaternions.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "vec/Vec3.h"

#include <cmath>

namespace math
{
    struct Quat
    {
        float x, y, z, s; /// x, y, z make up the vector part and s the scalar part.

        /// Get a rotation quaternion.
        ///
        /// @param angle The rotation angle in radians. Use @ref math::toRad() to convert from degrees to radians.
        /// @param axis  The axis of rotation. Must be a unit vector.
        [[nodiscard]] static Quat makeRotation(const float angle, Vec3 axis) noexcept
        {
            const float s = std::sin(angle * 0.5f);
            const float c = std::cos(angle * 0.5f);
            axis *= s;
            return Quat{ .x = axis.x, .y = axis.y, .z = axis.z, .s = c };
        }
    };
} // namespace math
