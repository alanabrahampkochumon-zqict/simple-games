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

#include "ComponentArray.h"
#include "DenseArray.h"
#include "Entity.h"
#include "SparseArray.h"

#include <cstdint>
#include <vector>

namespace u_ecs
{
    class Registry
    {
    public:
        template <typename Component>
        [[nodiscard]] constexpr Component get(Entity entity) const noexcept
        { return _components<Component>.get(entity); }


        template <typename Component>
        constexpr void add(Entity entity, Component component) const noexcept
        { _components<Component>.add(entity, component); }


        template <typename Component>
        constexpr void remove(Entity entity, Component component) const noexcept
        { _components<Component>.remove(entity, component); }


        // template <typename Component>
        // constexpr void registerComponent() const noexcept
        // {}

    private:
        template <typename Component>
        ComponentArray<Component> _components;

        // Helpers
        static size_t _registeredCompCount;

        static constexpr size_t MAX_COMPONENTS = 500;

        // Sparse Set set with paging
    };

} // namespace u_ecs
  // registry.registerComponent<Type>();
