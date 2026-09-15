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

namespace u_ecs
{
    using SpareArray_t = uint32_t;
    class SparseArray
    {
    public:
        static constexpr size_t PAGE_SIZE = 1024;

        constexpr SparseArray(): _storage(PAGE_SIZE) { _size = 0; }

        void add(Entity entity, SpareArray_t index)
        {
            // Resize if the space is more page is required.
            if (entity & (PAGE_SIZE - 1) == 0)// TODO: Redo masking logic.
            {
                _storage.resize(_storage.size() + PAGE_SIZE);
            }
            ++_size;
            _storage[entity] = index;
            return _size - 1;
        }


    private:
        std::vector<SpareArray_t> _storage; /// Internal storage.
        static size_t _size;                /// Used size of storage.
    };
} // namespace u_ecs
