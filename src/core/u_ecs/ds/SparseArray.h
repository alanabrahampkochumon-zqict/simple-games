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

#include "../entity/Entity.h"

#include <cassert>
#include <cstdint>
#include <vector>


namespace u_ecs
{
    using SpareArray_t = uint32_t;
    template <typename Component>
    class SparseArray
    {
    public:
        static constexpr size_t PAGE_SIZE      = 1024;
        static constexpr SpareArray_t SENTINEL = 0; // TODO: Update from zero

        constexpr SparseArray(): _storage(PAGE_SIZE) { _usedSlots = 0; }

        constexpr void add(const Entity entity, const SpareArray_t index) noexcept
        {
            assert(_storage[entity] == SENTINEL && "Component already exists for entity");
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


        [[nodiscard]] constexpr SpareArray_t get(const Entity entity) const noexcept
        {
            // TODO: Add assert after adding sentinel value
            assert(entity < _storage.size() && "Entity not registered!");
            return _storage[entity];
        }

        constexpr SpareArray_t removeComp(const Entity entity) noexcept
        {
            const auto index = _storage[entity];
            _storage[entity] = SENTINEL;
            return index;
        }


    private:
        std::vector<SpareArray_t> _storage; /// Internal storage.
        static size_t _usedSlots;           /// Number of slots used in the sparse array.
    };
} // namespace u_ecs
