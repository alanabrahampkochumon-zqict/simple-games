#pragma once
/**
 * @file ComponentType.h
 * @author Alan Abraham P Kochumon
 * @date Created on: September 29, 2026
 *
 * @brief Signature for components.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <cstdint>

namespace u_ecs
{
    using ComponentType = uint8_t;
    inline constexpr size_t MAX_COMPONENTS = 64;
} // namespace u_ecs
