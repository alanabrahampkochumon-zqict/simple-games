#pragma once
/**
 * @file Registry.h
 * @author Alan Abraham P Kochumon
 * @date Created on: September 12, 2026
 *
 * @brief Registry for managing entities, components and their sparse-sets.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "component/ComponentManager.h"
#include "entity/Entity.h"
#include "entity/EntityManager.h"

#include <memory>

namespace u_ecs
{
    class Registry
    {
    public:
        [[nodiscard]] constexpr Entity createEntity() noexcept { return _entityManager.create(); }

        constexpr void destroyEntity(const Entity entity) noexcept
        {
            _entityManager.destroy(entity);
            _componentManager.entityDestroyed(entity);
        }


        template <typename Component>
        [[nodiscard]] constexpr Component get(const Entity entity) const noexcept
        { return _componentManager.get<Component>(entity); }


        template <typename Component>
        [[nodiscard]] constexpr std::shared_ptr<ComponentArray<Component>> getAll() const noexcept
        { return _componentManager.getComponentArray<Component>(); }

        template <typename Component>
        constexpr void add(Entity entity, Component component) noexcept
        {
            _componentManager.add(entity, component);
        }


        template <typename Component>
        constexpr void remove(Entity entity, Component component) noexcept
        { _componentManager. }

    private:
        EntityManager _entityManager{};
        ComponentManager _componentManager{};

        // Sparse Set set with paging
    };

} // namespace u_ecs
  // registry.registerComponent<Type>();
