#pragma once
/**
 * @file SparseArray.h
 * @author Alan Abraham P Kochumon
 * @date Created on: September 15, 2026
 *
 * @brief Paged-sparse array.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "Entity.h"

#include <cstdint>
#include <vector>
#include <cassert>


namespace u_ecs
{
    using SpareArray_t = uint32_t;
    class SparseArray
    {
    public:
        static constexpr size_t PAGE_SIZE = 1024;

        constexpr SparseArray(): _storage(PAGE_SIZE) { _usedSlots = 0; }

        void add(const Entity entity, const SpareArray_t index)
        {
            assert(_storage[entity] == 0 && "Component already exists for entity");
            // Resize the sparse array if we have an entity
            // that cannot be stored in it.
            if (entity > _storage.size())
            {
                // Round up entity to the next multiple of page size
                // Hacker Delight [3-1]
                const auto newSize = entity + (-entity & PAGE_SIZE - 1);
                _storage.resize(newSize);
            }
            ++_usedSlots;
            _storage[entity] = index;
        }


        void removeComp(const Entity entity)
        {
            _storage[entity] = 0;
        }


    private:
        std::vector<SpareArray_t> _storage; /// Internal storage.
        static size_t _usedSlots;           /// Number of slots used in the sparse array.
    };
} // namespace u_ecs
