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
        Vec3 v;
        float s; /// x, y, z make up the vector part and s the scalar part.

        [[nodiscard]] explicit constexpr Quat(const Vec3& v, float s) noexcept;

        [[nodiscard]] explicit constexpr Quat(float x, float y, float z, float s) noexcept;


        /// Get a rotation quaternion.
        ///
        /// @param angle The rotation angle in radians. Use @ref math::toRad() to convert from degrees to radians.
        /// @param axis  The axis of rotation. Must be a unit vector.
        [[nodiscard]] static Quat makeRotation(float angle, const Vec3& axis) noexcept;
    };



    //+=+=+=+=+=+=+=+=+=
    //  IMPLEMENTATION
    //+=+=+=+=+=+=+=+=+=

    constexpr Quat::Quat(const Vec3& v, const float s) noexcept: v{ v }, s{ s } {}

    constexpr Quat::Quat(const float x, const float y, const float z, const float s) noexcept: v{ x, y, z }, s{ s } {}

    inline Quat Quat::makeRotation(const float angle, const Vec3& axis) noexcept
    {
        // [axis * sin(a/2), cos(a/2)]
        const float s = std::sin(angle * 0.5f);
        const float c = std::cos(angle * 0.5f);
        return Quat{ .v = axis * s, .s = c };
    }
} // namespace math
