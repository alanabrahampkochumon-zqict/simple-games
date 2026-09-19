#pragma once
/**
 * @file IDGen.h
 * @author Alan Abraham P Kochumon
 * @date Created on: September 19, 2026
 *
 * @brief Static time ID generator.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

namespace u_ecs
{
    class IDGen
    {
    public:
        template <typename>
        static size_t generate()
        {
            static const size_t value = getID();
            return value;
        }

    private:
        static size_t getID() noexcept
        {
            static size_t value = 0;
            return value++;
        }
    };
} // namespace u_ecs
