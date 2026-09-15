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

namespace u_ecs
{
    using Entity = uint32_t;

    // The upper 10 bits are reserved for tracking entity generation.
    inline constexpr uint32_t ENTITY_GENERATION_BITS = 10;
    inline constexpr uint32_t ENTITY_ID_BITS         = sizeof(Entity) - ENTITY_GENERATION_BITS;
    inline constexpr uint32_t ENTITY_GENERATION_MASK = 0xFFC00000;
    inline constexpr uint32_t ENTITY_ID_MASK         = ~ENTITY_GENERATION_MASK;

    /// Get the generation of the @p entity.
    inline uint32_t getGeneration(const Entity entity) { return entity >> ENTITY_ID_BITS; }

    /// Get the entity id without generation information.
    inline uint32_t stripGeneration(const Entity entity) { return entity & ~ENTITY_GENERATION_BITS; }

    /// Increment the entity generation.
    inline Entity incEntityGeneration(const Entity entity)
    {
        // To increment entity generate we need to first get the current generation, increment it's value, and shift it
        // to its correct position. Then zero out the generation, and OR it with the new generation.
        // Suppose there is 2 bit for gen and 6 for entity id, then
        // 0100 0001 (Entity with mask)
        // 0000 0001 (Current Gen)
        // 0000 0010 (Incremented Gen)
        // 1000 0000 (Generation in correct place)
        // 0100 0001 & ~(1100 0000) = 0100 0001 & 0011 1111 = 0000 0001
        // 1000 0000 | 0000 0001 (Ent | Gen) = 1000 0001 (Updated Entity)
        // Entity only
        return ((getGeneration(entity) + 1) << ENTITY_ID_BITS) | stripGeneration(entity);
    }

} // namespace u_ecs
