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

namespace ecs
{
    class EntityManager
    {
    public:
        EntityManager()
        {
            for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
            {
                _availableEntities.push(entity);
            }
        }

        /// Create and return a new entity
        [[nodiscard]] constexpr Entity create() noexcept
        {
            assert(_totalEntities < MAX_ENTITIES && "Unable to allocate more than MAX_ENTITIES");

            const Entity entity = _availableEntities.front();
            _availableEntities.pop();
            ++_totalEntities;

            return entity;
        }

        /// Destroy an entity
        constexpr void destroy(const Entity entity) noexcept
        {
            assert(entity < MAX_ENTITIES && "Entity out of range");

            _signatures[entity].reset();
            _availableEntities.push(entity);
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
        // Queue of available entities
        std::queue<Entity> _availableEntities{};

        std::array<Signature, MAX_ENTITIES> _signatures{};

        uint32_t _totalEntities{};
    };
} // namespace ecs
