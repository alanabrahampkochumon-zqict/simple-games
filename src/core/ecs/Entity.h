#pragma once
/**
 * @file Entity.h
 * @author Alan Abraham P Kochumon
 * @date Created on: September 03, 2026
 *
 * @brief ECS entity.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include <cstdint>

namespace ecs
{
    using Entity = uint32_t;

    constexpr Entity MAX_ENTITIES = 5000;

} // namespace ecs
