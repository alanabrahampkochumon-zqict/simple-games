#pragma once
/**
 * @file EntityManager.h
 * @author Alan Abraham P Kochumon
 * @date Created on: September 03, 2026
 *
 * @brief Manage entity generation.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "Entity.h"
#include "Signature.h"

#include <array>
#include <cassert>
#include <queue>

namespace u_ecs
{
    class EntityManager
    {
    public:
        EntityManager(): _entity(0) { _deadEntities.reserve(MIN_VECTOR_DEPTH); }

        /// Create and return a new entity
        [[nodiscard]] constexpr Entity create() noexcept
        {
            ++_totalEntities;
            return _deadEntities.size() > 0 ? _getFirstEntity() : _entity++;
        }

        /// Destroy an entity
        constexpr void destroy(Entity entity) noexcept
        {
            assert(entity < MAX_ENTITIES && "Entity out of range");

            // Reset signature
            _signatures[entity].reset();
            // Increase the generation
            entity = incEntityGeneration(entity);
            // Add entity to the total list
            _deadEntities.push_back(entity);
            --_totalEntities;
        }

        /// Set the signature for the @p entity.
        /// @note This will override any previously set signature on the entity.
        constexpr void setSignature(const Entity entity, const Signature signature) noexcept
        {
            assert(entity < MAX_ENTITIES && "Entity out of range");
            _signatures[entity] = signature;
        }

        /// Get the signature for a given entity.
        [[nodiscard]] constexpr Signature getSignature(const Entity entity) const noexcept
        {
            assert(entity < MAX_ENTITIES && "Entity out of range");
            return _signatures[entity];
        }

    private:
        constexpr Entity _getFirstEntity() noexcept
        {
            const auto fresh = _deadEntities[0];
            _deadEntities[0] = _deadEntities.back();
            _deadEntities.pop_back();
            return fresh;
        }

    private:
        // Create an entity bin which store dead entity that are ready for reuse
        std::vector<Entity> _deadEntities; // TODO: Update to PMR
        // The next available entity counter for keeping track of entities
        Entity _entity;
        uint32_t _totalEntities{};

        std::array<Signature, MAX_ENTITIES> _signatures{};

        static constexpr size_t MIN_VECTOR_DEPTH = 32;
    };
} // namespace u_ecs
