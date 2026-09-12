#pragma once
#include <cstdint>
/**
 * @file Registry.h
 * @author Alan Abraham P Kochumon
 * @date Created on: September 12, 2026
 *
 * @brief Registry for managing entities, components and their sparse-sets.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

namespace u_ecs
{
    class Registry
    {
    public:
        static constexpr uint32_t SPARE_SET_PAGE_SIZE = 1024;

    private:
        // Sparse Set set with paging
    };
} // namespace u_ecs
