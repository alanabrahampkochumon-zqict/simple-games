#pragma once
/**
 * @file Mat4.h
 * @author Alan Abraham P Kochumon
 * @date Created on: September 01, 2026
 *
 * @brief 4D matrix using column-major layout.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "../vec/Vec4.h"

#include <array>

namespace math
{
    struct Mat4
    {
        [[nodiscard]] constexpr Mat4(const Vec4& col0, const Vec4& col1, const Vec4& col2, const Vec4& col3) noexcept;
        [[nodiscard]] constexpr Mat4(float m00, float m01, float m02, float m03, float m10, float m11, float m12,
                                     float m13, float m20, float m21, float m22, float m23, float m30, float m31,
                                     float m32, float m33) noexcept;

        /// Get the vector at @p index (immutable).
        [[nodiscard]] constexpr const Vec4& operator[](size_t index) const noexcept;

        /// Get the vector at @p index (mutable).
        [[nodiscard]] constexpr Vec4& operator[](size_t index) noexcept;
        // Indexing unsupported due to slow ops
        // /// Get the element at (@p row, @p col) (immutable).
        // [[nodiscard]] const Vec4& operator()(size_t row, size_t col) const noexcept;
        //
        // /// Get the element at @p (@p row, @p col) (mutable).
        // [[nodiscard]] Vec4& operator()(size_t row, size_t col) noexcept;

        /// Add this matrix to @p other elementwise and return a new matrix.
        [[nodiscard]] constexpr Mat4 operator+(const Mat4& other) const noexcept;

        /// Add this matrix to @p other elementwise in-place.
        constexpr Mat4& operator+=(const Mat4& other) noexcept;

        /// Subtract this matrix from @p other elementwise and return a new matrix.
        [[nodiscard]] constexpr Mat4 operator-(const Mat4& other) const noexcept;

        /// Subtract this matrix from @p other elementwise in-place.
        constexpr Mat4& operator-=(const Mat4& other) noexcept;

        /// Multiply this matrix by @p s and return a new matrix.
        [[nodiscard]] constexpr Mat4 operator*(float s) const noexcept;

        /// Multiply this matrix by @p s in-place.
        constexpr Mat4& operator*=(float s) noexcept;

        /// Divide this matrix by @p s and return a new matrix.
        [[nodiscard]] constexpr Mat4 operator/(float s) const noexcept;

        /// Divide this matrix by @p s in-place.
        constexpr Mat4& operator/=(float s) noexcept;


        /// Multiply a vector by this matrix.
        [[nodiscard]] constexpr Vec4 operator*(const Vec4& vec) const noexcept;

        ///  Multiply this matrix with another matrix @p mat and return a new matrix.
        [[nodiscard]] constexpr Mat4 operator*(const Mat4& mat) const noexcept;

        ///  Multiply this matrix with another matrix @p mat in-place.
        [[nodiscard]] constexpr Mat4& operator*=(const Mat4& mat) noexcept;

        /// Get the raw pointer to the internal data.
        /// @note The data is strictly arranged in a column major order, so if you need a row-major layout
        ///       use @ref transpose.
        [[nodiscard]] float* ptr() const noexcept;

        /// Get a scale transformation factory along coordinate axis.
        [[nodiscard]] static constexpr Mat4 getScale(const float x, const float y, const float z) noexcept
        { return Mat4{ x, 0.0f, 0.0f, 0.0f, 0.0f, y, 0.0f, 0.0f, 0.0f, 0.0f, z, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f }; }

        /// Get a translation transform factory.
        [[nodiscard]] static constexpr Mat4 getTranslation(const float x, const float y, const float z) noexcept
        { return Mat4{ 1.0f, 0.0f, 0.0f, x, 0.0f, 1.0f, 0.0f, y, 0.0f, 0.0f, 1.0f, z, 0.0f, 0.0f, 0.0f, 1.0f }; }



    private:
        std::array<Vec4, 4> _data{};
    };


    //+=+=+=+=+=+=+=+=+=+=+=+=+=
    //    IMPLEMENTATIONS
    //+=+=+=+=+=+=+=+=+=+=+=+=+=

    constexpr Mat4::Mat4(const Vec4& col0, const Vec4& col1, const Vec4& col2, const Vec4& col3) noexcept
        : _data{ col0, col1, col2, col3 }
    {}

    constexpr Mat4::Mat4(const float m00, const float m01, const float m02, const float m03, const float m10,
                         const float m11, const float m12, const float m13, const float m20, const float m21,
                         const float m22, const float m23, const float m30, const float m31, const float m32,
                         const float m33) noexcept
        : _data{ Vec4{ m00, m10, m20, m30 }, Vec4{ m01, m11, m21, m31 }, Vec4{ m02, m12, m22, m32 },
                 Vec4{ m03, m13, m23, m33 } }
    {}


    constexpr const Vec4& Mat4::operator[](const size_t index) const noexcept { return _data[index]; }

    constexpr Vec4& Mat4::operator[](const size_t index) noexcept { return _data[index]; }

    constexpr Mat4 Mat4::operator+(const Mat4& other) const noexcept
    {
        return Mat4{
            _data[0] + other._data[0],
            _data[1] + other._data[1],
            _data[2] + other._data[2],
            _data[3] + other._data[3],
        };
    }


    constexpr Mat4& Mat4::operator+=(const Mat4& other) noexcept
    {
        *this = *this + other;
        return *this;
    }

    constexpr Mat4 Mat4::operator-(const Mat4& other) const noexcept
    {
        return Mat4{
            _data[0] - other._data[0],
            _data[1] - other._data[1],
            _data[2] - other._data[2],
            _data[3] - other._data[3],
        };
    }

    constexpr Mat4& Mat4::operator-=(const Mat4& other) noexcept
    {
        *this = *this - other;
        return *this;
    }

    constexpr Mat4 Mat4::operator*(const float s) const noexcept
    {
        return Mat4{
            _data[0] * s,
            _data[1] * s,
            _data[2] * s,
            _data[3] * s,
        };
    }

    constexpr Mat4& Mat4::operator*=(const float s) noexcept
    {
        *this = *this * s;
        return *this;
    }

    constexpr Mat4 Mat4::operator/(const float s) const noexcept
    {
        const float f = 1.0f / s;
        return *this * f;
    }

    constexpr Mat4& Mat4::operator/=(const float s) noexcept
    {
        *this = *this / s;
        return *this;
    }

    constexpr Vec4 Mat4::operator*(const Vec4& vec) const noexcept
    {
        const auto x = vec.x * _data[0].x + vec.y * _data[1].x + vec.z * _data[2].x + vec.w * _data[3].x;
        const auto y = vec.x * _data[0].y + vec.y * _data[1].y + vec.z * _data[2].y + vec.w * _data[3].y;
        const auto z = vec.x * _data[0].z + vec.y * _data[1].z + vec.z * _data[2].z + vec.w * _data[3].z;
        const auto w = vec.x * _data[0].w + vec.y * _data[1].w + vec.z * _data[2].w + vec.w * _data[3].w;
        return Vec4{ x, y, z, w };
    }

    constexpr Mat4 Mat4::operator*(const Mat4& mat) const noexcept
    { return Mat4{ *this * mat[0], *this * mat[1], *this * mat[2], *this * mat[3] }; }

    constexpr Mat4& Mat4::operator*=(const Mat4& mat) noexcept
    {
        *this = *this * mat;
        return *this;
    }

    inline float* Mat4::ptr() const noexcept { return *_data.data()[0]; }

} // namespace math
