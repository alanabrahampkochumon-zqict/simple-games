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

#include "mat/Mat4.h"
#include "vec/Vec3.h"

#include <cmath>

namespace math
{
    struct Quat
    {
        Vec3 v;
        float s; /// x, y, z make up the vector part and s the scalar part.

        float& x = v.x;
        float& y = v.y;
        float& z = v.z;

        [[nodiscard]] explicit constexpr Quat(const Vec3& v, float s) noexcept;

        [[nodiscard]] explicit constexpr Quat(float x, float y, float z, float s) noexcept;


        /// @brief Get a rotation quaternion.
        ///
        /// @param angle The rotation angle in radians. Use @ref math::toRad() to convert from degrees to radians.
        /// @param axis  The axis of rotation. Must be a unit vector.
        [[nodiscard]] static Quat makeRotation(float angle, const Vec3& axis) noexcept;


        /// @brief Perform quaternion multiplication
        /// @note Rotation is applied in a right to left order.
        [[nodiscard]] constexpr Quat operator*(const Quat& other) const noexcept;

        /// @brief Transform a vector by this quaternion.
        /// @note This assume that this quaternion is a rotational(unit) quaternion.
        [[nodiscard]] constexpr Vec3 transform(const Vec3& vec) const noexcept;

        /// @brief Get the conjugate of this quaternion.
        ///
        /// @note For unit quaternion, this is the inverse.
        [[nodiscard]] constexpr Quat conjugate() const noexcept;

        /// @brief Get the matrix(rotation) from this quaternion.
        [[nodiscard]] constexpr Mat4 toMat() const noexcept;
    };



    //+=+=+=+=+=+=+=+=+=
    //  IMPLEMENTATION
    //+=+=+=+=+=+=+=+=+=

    constexpr Quat::Quat(const Vec3& v, const float s) noexcept: v{ v }, s{ s } {}

    constexpr Quat::Quat(const float x, const float y, const float z, const float s) noexcept: v{ x, y, z }, s{ s } {}

    constexpr Quat Quat::operator*(const Quat& other) const noexcept
    {
        // q1q2 = v1 x v2 + s1 * v2 + s2 * v1 - v1.v2
        auto v = v * other.s + other.v * s + v.cross(other.v);
        auto s = s * other.s - v.dot(other.v);
        return Quat{ v, s };
    }

    constexpr Vec3 Quat::transform(const Vec3& vec) const noexcept
    {
        // TODO: Recheck
        // FGED: qvq* = (c2 - s2)v + 2s^2(v.a)a + 2cs(a x v)
        const float b2 = v.x * v.x + v.y * v.y + v.z * v.z;
        return v * (s * s - b2) + vec * 2 * vec.dot(v) + v.cross(vec) * s * 2;
    }

    constexpr Quat Quat::conjugate() const noexcept { return Quat{ -v, s }; }

    constexpr Mat4 Quat::toMat() const noexcept
    {
        // Here w implies scalar part s
        const float x2 = x * x;
        const float y2 = y * y;
        const float z2 = z * z;
        const float xy = v.x * v.y;
        const float yz = v.y * v.z;
        const float zx = v.z * v.x;

        const float wx = s * v.x;
        const float wy = s * v.y;
        const float wz = s * v.z;

        return Mat4{ 1 - 2 * (y2 + z2),
                     2 * (xy - wz),
                     2 * (zx + wy),
                     0,
                     2 * (xy + wz),
                     1 - 2 * (x2 + z2),
                     2 * (yz - wx),
                     0,
                     2 * (zx - wy),
                     2 * (yz + wx),
                     1 - 2 * (x2 + y2),
                     0,
                     0,
                     0,
                     0,
                     1 };
    }

    inline Quat Quat::makeRotation(const float angle, const Vec3& axis) noexcept
    {
        // [axis * sin(a/2), cos(a/2)]
        const float s = std::sin(angle * 0.5f);
        const float c = std::cos(angle * 0.5f);
        return Quat{ .v = axis * s, .s = c };
    }
} // namespace math
