#pragma once
/**
 * @file Vec4.h
 * @author Alan Abraham P Kochumon
 * @date Created on: September 01, 2026
 *
 * @brief 4D-vector (float) class.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "Vec2.h"
#include "Vec3.h"

#include <cmath>


// Peregrine Simple Math
namespace math
{

    struct alignas(16) Vec4
    {
        float x, y, z, w;

        Vec4() = default;

        [[nodiscard]] constexpr explicit Vec4(float _x, float _y, float _z, float _w) noexcept;

        /// @brief Add two vector together and return a new vector containing the vector sum.
        [[nodiscard]] constexpr Vec4 operator+(const Vec4& other) const noexcept;

        /// @brief Add two vector together and return a new vector containing the vector sum.
        constexpr Vec4 operator+=(const Vec4& other) noexcept;

        /// @brief Subtract a vector from this vector and return a new vector containing the vector difference.
        [[nodiscard]] constexpr Vec4 operator-(const Vec4& other) const noexcept;

        /// @brief Multiply this vector by a scalar and return a new scaled vector.
        [[nodiscard]] constexpr Vec4 operator*(float scalar) const noexcept;

        /// @brief Divide this vector by a scalar and return a new inverse scaled vector.
        [[nodiscard]] constexpr Vec4 operator/(float scalar) const noexcept;

        /// @brief Compute the dot product of this vector with @p other.
        [[nodiscard]] constexpr float dot(const Vec4& other) const noexcept;

        /// @brief Compute the cross product of this vector with @p other.
        [[nodiscard]] constexpr Vec4 cross(const Vec4& other) const noexcept;

        /// @brief Compute the squared magnitude of this vector.
        /// @relatedalso mag()
        [[nodiscard]] constexpr float magSq() const noexcept;

        /// @brief Compute the magnitude of this vector.
        /// @relatedalso magSq()
        [[nodiscard]] float mag() const noexcept;

        /// @brief Compute the squared distance between two vector.
        [[nodiscard]] constexpr float distSq(const Vec4& other) const noexcept;

        /// @brief Compute the distance between two vector.
        [[nodiscard]] float dist(const Vec4& other) const noexcept;

        /// @brief Normalize this vector and return a new vector.
        [[nodiscard]] Vec4 normalize() const noexcept;

        /// @brief Get the xy component of the vector as a 2D vector.
        [[nodiscard]] constexpr Vec2 xy() const noexcept;
    };



    //+=+=+=+=+=+=+=+=+=
    // IMPLEMENTATIONS
    //+=+=+=+=+=+=+=+=+=

    constexpr Vec4::Vec4(const float _x, const float _y, const float _z, const float _w) noexcept
        : x{ _x }, y{ _y }, z{ _z }, w{ _w }
    {}

    constexpr Vec4 Vec4::operator+(const Vec4& other) const noexcept
    { return Vec4{ x + other.x, y + other.y, z + other.z, w + other.w }; }


    constexpr Vec4 Vec4::operator+=(const Vec4& other) noexcept
    {
        *this = *this + other;
        return *this;
    }

    constexpr Vec4 Vec4::operator-(const Vec4& other) const noexcept
    { return Vec4{ x - other.x, y - other.y, z - other.z, w - other.w }; }

    constexpr Vec4 Vec4::operator*(const float scalar) const noexcept
    { return Vec4{ x * scalar, y * scalar, z * scalar, w * scalar }; }

    constexpr Vec4 Vec4::operator/(const float scalar) const noexcept
    {
        const float factor = 1.0f / scalar;
        return *this * factor;
    }


    constexpr float Vec4::dot(const Vec4& other) const noexcept
    { return x * other.x + y * other.y + z * other.z + w * other.w; }

    constexpr float Vec4::magSq() const noexcept { return dot(*this); }

    inline float Vec4::mag() const noexcept { return std::sqrt(magSq()); }

    constexpr float Vec4::distSq(const Vec4& other) const noexcept
    {
        const auto dx = other.x - x;
        const auto dy = other.y - y;
        const auto dz = other.z - z;
        const auto dw = other.w - w;
        return dx * dx + dy * dy + dz * dz + dw * dw;
    }


    constexpr Vec2 Vec4::xy() const noexcept { return Vec2{ x, y }; }

    constexpr Vec3 Vec4::xy() const noexcept { return Vec3{ x, y, z }; }

    inline float Vec4::dist(const Vec4& other) const noexcept { return std::sqrt(distSq(other)); }

    inline Vec4 Vec4::normalize() const noexcept { return *this / mag(); }



} // namespace math
