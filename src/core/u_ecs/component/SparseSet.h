#pragma once
/**
 * @file SparseSet.h
 * @author Alan Abraham P Kochumon
 * @date Created on: September 30, 2026
 *
 * @brief Sparse-set implementation.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "../entity/Entity.h"
#include "ComponentType.h"

#include <memory>
#include <vector>


namespace u_ecs
{
    template <typename T>
    class SparseSet
    {
        static constexpr size_t LOG_SPARSE_ARRAY_PAGE_SIZE = 10;
        static constexpr size_t SPARSE_ARRAY_PAGE_SIZE     = 1 << LOG_SPARSE_ARRAY_PAGE_SIZE;
        static constexpr size_t DENSE_ARRAY_PAGE_SIZE      = 32;

        SparseSet() noexcept
        {
            _sparseArray.reserve(SPARSE_ARRAY_PAGE_SIZE);
            _denseArray.reserve(DENSE_ARRAY_PAGE_SIZE);
        }

        /// Add a @p T @p component to an @p entity.
        constexpr void add(const Entity entity, const T& component)
        {
            const auto denseIndex = _denseArray.size();
            _denseArray.emplace_back(component);
            // if (entity >= (_sparseArray.size() >> LOG_SPARSE_ARRAY_PAGE_SIZE))
            // TODO: Add resizing
            _sparseArray[entity] = denseIndex;
        }

        constexpr void remove(const Entity entity)
        {
            // Get the dense index.
            const size_t denseIndex = _sparseArray[entity];
            // Swap the component in the dense array with the last component

        }


        /// Remove a component at @p index.
        /// This is constant time operator(O(1)).
        constexpr void removeAt(size_t index) noexcept
        {
            /// Swap this component with the last one and remove the last one.
            storage[index] = storage.back();
            storage.pop_back();
            // TODO: IMPL if required a counter so that we dont need to delete the item and can just mark it as deleted.
        }

        static constexpr size_t PAGE_SIZE      = 1024;
        static constexpr SpareArray_t SENTINEL = 0; // TODO: Update from zero

        constexpr SparseArray(): _storage(PAGE_SIZE) { _usedSlots = 0; }

        constexpr void add(const Entity entity, const SpareArray_t index) noexcept
        {
            assert(_storage[stripGeneration(entity)] == SENTINEL && "Component already exists for entity");
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
            _storage[stripGeneration(entity)] = index;
        }


        [[nodiscard]] constexpr SpareArray_t get(const Entity entity) const noexcept
        {
            // TODO: Add assert after adding sentinel value
            assert(entity < _storage.size() && "Entity not registered!");
            return _storage[stripGeneration(entity)];
        }

        constexpr SpareArray_t removeComp(const Entity entity) noexcept
        {
            const auto index                  = _storage[stripGeneration(entity)];
            _storage[stripGeneration(entity)] = SENTINEL;
            return index;
        }

        constexpr SpareArray_t contains(const Entity entity) const noexcept
        { return _storage.size() > entity && _storage[stripGeneration(entity)] != SENTINEL; }




    private:
        std::vector<std::unique_ptr<std::array<Entity, SPARSE_ARRAY_PAGE_SIZE>>> _sparseArray{};
        std::vector<T> _denseArray{};
    };
} // namespace u_ecs
