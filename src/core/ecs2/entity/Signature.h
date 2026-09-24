#pragma once
/**
 * @file Signature.h
 * @author Alan Abraham P Kochumon
 * @date Created on: September 03, 2026
 *
 * @brief Bitset for identifying component type.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "../Config.h"

#include <bitset>

namespace u_ecs
{
    using Signature = std::bitset<MAX_COMPONENTS>;
}
