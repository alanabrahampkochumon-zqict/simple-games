#pragma once
/**
 * @file DenseArray.h
 * @author Alan Abraham P Kochumon
 * @date Created on: September 15, 2026
 *
 * @brief Container for allocating and deallocating pages of components.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include <vector>

namespace u_ecs
{
    template <typename T>
    class DenseArray
    {
    public:
        static constexpr size_t RESIZE_FACTOR = 8; ///< Resize amount.

        constexpr DenseArray() noexcept { storage.reserve(RESIZE_FACTOR); }

        /// Add a @p component and return the added index.
        constexpr size_t add(T component)
        {
            // Resize the container if the we dont have any storage for components.
            // TODO: Look into whether there is way to eliminate.
            if ((storage.size() & (RESIZE_FACTOR - 1)) == 0)
            {
                storage.reserve(storage.size() + RESIZE_FACTOR);
            }
            storage.push_back(component);
            return storage.size() - 1;
        }

        /// Get the component at the given index.
        [[nodiscard]] constexpr T get(size_t index) const noexcept { return storage[index]; }

        [[nodiscard]] constexpr const std::vector<T>& getAllElements() const noexcept { return storage; }


        /// Remove a component at @p index.
        /// This is constant time operator(O(1)).
        constexpr void removeAt(size_t index) noexcept
        {
            /// Swap this component with the last one and remove the last one.
            storage[index] = storage.back();
            storage.pop_back();
            // TODO: IMPL if required a counter so that we dont need to delete the item and can just mark it as deleted.
        }

    private:
        std::vector<T> storage; // TODO: Swap to pmr vector
    };
} // namespace u_ecs
