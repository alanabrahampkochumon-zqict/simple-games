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
        template <typename ComponentType>
        ComponentType get(Entity entity)
        {
            const auto denseIndex = _componentSparseArray<ComponentType>.get(entity);
            return _componentDenseArray<ComponentType>.get(denseIndex);
        }


    private:
        template <typename ComponentType>
        SparseArray<ComponentType> _componentSparseArray{};
        template <typename ComponentType>
        DenseArray<ComponentType> _componentDenseArray{};

        // Sparse Set set with paging
    };
} // namespace u_ecs
