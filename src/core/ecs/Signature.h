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


#include "components/Component.h"

#include <bitset>

namespace ecs
{
    using Signature = std::bitset<comp::MAX_COMPONENTS>;
}
