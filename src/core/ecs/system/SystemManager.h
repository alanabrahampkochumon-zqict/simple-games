#pragma once
/**
 * @file SystemManager.h
 * @author Alan Abraham P Kochumon
 * @date Created on: September 04, 2026
 *
 * @brief Manages different systems.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "../Signature.h"
#include "System.h"

#include <cassert>
#include <memory>
#include <ranges>
#include <unordered_map>

namespace ecs::system
{
    class SystemManager
    {
    public:
        template <typename T>
        [[nodiscard]] constexpr std::shared_ptr<T> registerSystem() noexcept
        {
            const char* typeName = typeid(T).name();

            assert(!_systems.contains(typeName) && "System is already registered!");

            auto system = std::make_shared<T>();
            _systems.insert({ typeName, system });
            return system;
        }

        template <typename T>
        constexpr void setSignature(const Signature signature) noexcept
        {
            const char* typeName = typeid(T).name();
            assert(!_systems.contains(typeName) && "Signature is already registered!");

            _signatures.insert({ typeName, signature });
        }


        void entityDestroyed(const Entity entity) noexcept
        {
            for (const auto& system : _systems | std::views::values)
            {
                system->entities.erase(entity);
            }
        }

        void entitySignatureChanged(const Entity entity, const Signature signature) noexcept
        {
            // Notify each system's corresponding entity that the signature has changed
            for (const auto& [type, system] : _systems)
            {
                const auto& systemSignature = _signatures[type];
                // If system signature match with the passed in signature insert the entity
                // else remove it.
                if ((signature & systemSignature) == systemSignature)
                {
                    system->entities.insert(entity);
                }
                else
                {
                    system->entities.erase(entity);
                }
            }
        }

    private:
        // Maps type name to signature and *system
        std::unordered_map<const char*, Signature> _signatures{};
        std::unordered_map<const char*, std::shared_ptr<System>> _systems{};
    };
} // namespace ecs::system
