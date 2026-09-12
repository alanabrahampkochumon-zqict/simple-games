#pragma once
/**
 * @file Entity.h
 * @author Alan Abraham P Kochumon
 * @date Created on: September 12, 2026
 *
 * @brief Entities with generation support for reuse.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <cstdint>

namespace ecs
{
    using Entity = uint32_t;

    // The upper 10 bits are reserved for tracking entity generation.
    inline constexpr uint32_t ENTITY_ID_BITS         = 22;
    inline constexpr uint32_t ENTITY_GENERATION_BITS = 10;
    inline constexpr uint32_t ENTITY_GENERATION_MASK = 0xFFC00000;
    inline constexpr uint32_t ENTITY_ID_MASK         = ~ENTITY_GENERATION_MASK;

    inline Entity incEntityGeneration(const Entity entity) { return entity + 1 << ENTITY_ID_BITS; }
    inline uint32_t getGeneration(const Entity entity) { return entity >> ENTITY_ID_BITS; }

} // namespace ecs
