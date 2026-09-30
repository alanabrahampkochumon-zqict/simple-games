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


#include "ComponentArray.h"
#include "ComponentType.h"

#include <cassert>
#include <memory>
#include <typeindex>
#include <unordered_map>

namespace u_ecs
{
    class ComponentManager
    {
    public:
        ComponentManager() { _componentArrays.resize(MAX_COMPONENTS); }

        template <typename T>
        constexpr void registerComponent() noexcept
        {
            const auto typeIndex = std::type_index(typeid(T));
            assert(!_componentTypes.contains(typeIndex) && "Component already registered");
            _componentTypes.insert({ typeIndex, _nextComponentType });
            _componentArrays[_nextComponentType] = std::make_shared<ComponentArray<T>>();
            ++_nextComponentType;
        }


        template <typename T>
        [[nodiscard]] constexpr ComponentType getComponentType() noexcept
        {
            const auto typeIndex = std::type_index(typeid(T));
            assert(_componentTypes.contains(typeIndex) && "Component not registered");
            return _componentTypes.at(typeIndex);
        }


        template <typename T>
        constexpr void add(const Entity entity, const T& component) noexcept
        { getComponentType<T>()->add(entity, component); }


        template <typename T>
        [[nodiscard]] constexpr T& get(Entity entity) const noexcept
        { return getComponentArray<T>()->get(entity); }


        constexpr void entityDestroyed(const Entity entity) const
        {
            for (const auto& component : _componentArrays)
            {
                component->remove(entity);
            }
        }

        /// Casts an BaseComponentArray to its derived Component class.
        template <typename T>
        [[nodiscard]] constexpr std::shared_ptr<ComponentArray<T>> getComponentArray() const
        {
            const auto typeIndex = std::type_index(typeid(T));
            assert(_componentTypes.contains(typeIndex) && "Component doesn't exist");
            return std::static_pointer_cast<ComponentArray<T>>(_componentArrays[_componentTypes.at(typeIndex)]);
        }

    private:
        /// TODO: Update this to maybe a typelist?
        /// Mapping from each component name to its type.
        std::unordered_map<std::type_index, ComponentType> _componentTypes{};
        // Array of component arrays
        std::vector<std::shared_ptr<BaseComponentArray>> _componentArrays{};

        /// Component type to assign to next registered component
        ComponentType _nextComponentType{};
    };
} // namespace u_ecs
