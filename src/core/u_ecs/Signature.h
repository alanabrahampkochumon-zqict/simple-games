#pragma once
#include "IDGen.h"

#include <bit>
#include <bitset>
namespace u_ecs
{
    template<typename T>
    struct Signature
    {
        constexpr size_t ID = IDGen::generate<Signature>();
    };
}