#pragma once
/**
 * @file ComponentArray.h
 * @author Alan Abraham P Kochumon
 * @date Created on: September 17, 2026
 *
 * @brief An sparse-set based array for faster component lookups.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "DenseArray.h"
#include "SparseArray.h"

namespace u_ecs
{
    template <typename Component>
    class ComponentArray
    {
    public:
        [[nodiscard]] constexpr Component get(Entity entity) const noexcept
        {
            const auto denseIndex = _componentSparseArray.get(entity);
            return _componentDenseArray.get(denseIndex);
        }


        constexpr void add(Entity entity, Component component) const noexcept
        {
            const auto denseIndex = _componentDenseArray.add(component);
            _componentSparseArray.add(entity, denseIndex);
        }


        constexpr void remove(Entity entity, Component component) const noexcept
        {
            const auto denseIndex = _componentSparseArray.removeComp(entity);
            _componentDenseArray.removeAt(denseIndex);
        }

        [[nodiscard]] constexpr DenseArray<Component> getAll()
        {
            return _componentDenseArray.getAllElements();
        }

    private:
        SparseArray<Component> _componentSparseArray{};
        DenseArray<Component> _componentDenseArray{};
    };
} // namespace u_ecs
