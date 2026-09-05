#pragma once
/**
 * @file System.h
 * @author Alan Abraham P Kochumon
 * @date Created on: September 04, 2026
 *
 * @brief Parent class for creating a system of components.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "../Entity.h"

namespace ecs
{
    class System
    {
    public:
        std::set<Entity> _entities;
    };
} // namespace ecs
