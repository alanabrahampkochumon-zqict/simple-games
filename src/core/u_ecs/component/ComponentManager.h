#pragma once
/**
 * @file ComponentManager.h
 * @author Alan Abraham P Kochumon
 * @date Created on: September 04, 2026
 *
 * @brief Manages components.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Component.h"
#include "ComponentArray.h"

#include <cassert>
#include <memory>
#include <unordered_map>

namespace ecs
{
    class ComponentManager
    {
    public:
        template <typename T>
        constexpr void registerComponent() noexcept
        {
            const char* typeName = typeid(T).name();
            assert(!_componentTypes.contains(typeName) && "Component already registered");

            _componentTypes.insert({ typeName, _nextComponentType });
            _componentArrays.insert({ typeName, std::make_shared<ComponentArray<T>>() });
            ++_nextComponentType;
        }

        template <typename T>
        [[nodiscard]] constexpr comp::ComponentType getComponentType() noexcept
        {
            const char* typeName = typeid(T).name();
            assert(_componentTypes.contains(typeName) && "Component not registered");

            return _componentTypes[typeName];
        }

        template <typename T>
        constexpr void add(const Entity entity, const T& component) noexcept
        { getComponentType<T>()->insert(entity, component); }


        template <typename T>
        [[nodiscard]] constexpr T& get(Entity entity) noexcept
        { return getComponentArray<T>()->getComponent(entity); }


        constexpr void entityDestroyed(const Entity entity)
        {
            for (const auto& pair : _componentArrays)
            {
                const auto& component = pair.second;
                component->entityDestroyed(entity);
            }
        }

    private:
        /// Mapping from each component name to its type.
        std::unordered_map<const char*, comp::ComponentType> _componentTypes{};

        /// Mapping from a component name to its component array
        std::unordered_map<const char*, std::shared_ptr<IComponentArray>> _componentArrays{};

        /// Component type to assign to next registered component
        comp::ComponentType _nextComponentType{};


        /// Casts an IComponent to its derived Component class.
        template <typename T>
        [[nodiscard]] constexpr std::shared_ptr<ComponentArray<T>> getComponentArray()
        {
            const char* typeName = typeid(T).name();
            assert(_componentTypes.contains(typeName) && "Component doesn't exist");

            return std::static_pointer_cast<ComponentArray<T>>(_componentArrays[typeName]);
        }
    };
} // namespace ecs
