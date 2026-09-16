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
        {
            const auto denseIndex = _componentSparseArray<Component>.get(entity);
            return _componentDenseArray<Component>.get(denseIndex);
        }


        template <typename Component>
        constexpr void add(Entity entity, Component component) const noexcept
        {
            const auto denseIndex = _componentDenseArray<Component>.add(component);
            _componentSparseArray<Component>.add(entity, denseIndex);
        }


        template <typename Component>
        constexpr void remove(Entity entity, Component component) const noexcept
        {
            const auto denseIndex = _componentSparseArray<Component>.removeComp(entity);
            _componentDenseArray<Component>.removeAt(denseIndex);
        }

        // template<typename Component>
        // constexpr std::vector<Component>&

    private:
        template <typename Component>
        SparseArray<Component> _componentSparseArray{};
        template <typename Component>
        DenseArray<Component> _componentDenseArray{};

        // Sparse Set set with paging
    };
} // namespace u_ecs
