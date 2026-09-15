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

#include "Entity.h"

#include <cstdint>
#include <vector>

namespace u_ecs
{
    class Registry
    {
    public:
        static constexpr uint32_t SPARE_SET_PAGE_SIZE = 1024;

    private:
        /// The array that maps from entity id to packed array
        std::vector<std::array<Entity, SPARE_SET_PAGE_SIZE>> _sparseEntityArray{};
        /// Packed
        std::vector<std::array<uint32_t, SPARE_SET_PAGE_SIZE>>

        template<typename ComponentType>
        std::vector<std::array<ComponentType, SPARE_SET_PAGE_SIZE>> _componentPage{};

        // Sparse Set set with paging
    };
} // namespace u_ecs
