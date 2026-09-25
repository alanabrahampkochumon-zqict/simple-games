#pragma once
/**
 * @file BaseComponentArray.h
 * @author Alan Abraham P Kochumon
 * @date Created on: September 25, 2026
 *
 * @brief Base component, required for maintaining a list of components arrays.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "../entity/Entity.h"

namespace u_ecs
{
    class BaseComponentArray
    {
    public:
        virtual ~BaseComponentArray() = default;

        virtual void remove(Entity entity)   = 0;
        virtual void contains(Entity entity) = 0;
    };
} // namespace u_ecs
