#pragma once
/**
 * @file System.h
 * @author Alan Abraham P Kochumon
 * @date Created on: September 04, 2026
 *
 * @brief Encapsulation of related entities.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "../Entity.h"

#include <set>


namespace ecs::system
{
    class System
    {
    public:
        std::set<Entity> entities{};
    };
} // namespace ecs::system
