#pragma once
/**
 * @file Component.h
 * @author Alan Abraham P Kochumon
 * @date Created on: September 03, 2026
 *
 * @brief Shared component parameters.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include <cstdint>

namespace ecs::comp
{
    using ComponentType = uint8_t;

    constexpr ComponentType MAX_COMPONENTS = 32;
} // namespace ecs::comp
