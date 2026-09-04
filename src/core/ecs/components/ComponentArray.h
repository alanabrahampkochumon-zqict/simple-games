#pragma once
/**
 * @file ComponentArray.h
 * @author Alan Abraham P Kochumon
 * @date Created on: September 04, 2026
 *
 * @brief A packing array for managing entity components.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "../Entity.h"

#include <cassert>
#include <unordered_map>

namespace ecs
{

    // Review the use
    class IComponentArray
    {
    public:
        virtual ~IComponentArray()                       = default;
        virtual void entityDestroyed(Entity entity) = 0;
    };

    template <typename T>
    class ComponentArray: public IComponentArray
    {
    public:
        constexpr void insert(const Entity entity, const T& component) noexcept
        {
            assert(!_entityToIndexMap.contains(entity) && "Component exists for entity.");

            // Add the entity and update the reference maps
            // _numValidEntities is the size so, we can assign it to entity without changing it's value
            _entityToIndexMap[entity]            = _numValidEntities;
            _indexToEntityMap[_numValidEntities] = entity;
            _components[_numValidEntities]       = component;
            // Increment the number of valid entities.
            ++_numValidEntities;
        }
        // TODO: Rewrite with vector
        constexpr void remove(const Entity entity) noexcept
        {
            assert(_entityToIndexMap.contains(entity) && "Cannot find the entity in the array");

            // Swap the entity to remove with the last entity to ensure that we are not moving memory
            size_t indexToRemove       = _entityToIndexMap[entity];
            size_t lastIndex           = _numValidEntities - 1;
            _components[indexToRemove] = _components[lastIndex];

            // Update the map
            const Entity lastEntity                = _indexToEntityMap[lastIndex];
            _entityToIndexMap[lastEntity]    = indexToRemove;
            _indexToEntityMap[indexToRemove] = lastEntity;

            _entityToIndexMap.erase(entity);
            _indexToEntityMap.erase(lastIndex);

            --_numValidEntities;
        }

        [[nodiscard]] constexpr T& getComponent(const Entity entity) const noexcept
        {
            assert(_entityToIndexMap.contains(entity) && "Entity not registered!");
            return _components[_entityToIndexMap.at(entity)];
        }

        constexpr void entityDestroyed(const Entity entity) override
        {
            if (_entityToIndexMap.contains(entity))
            {
                remove(entity);
            }
        }

    private:
        std::array<T, MAX_ENTITIES> _components{}; /// The packed array of components

        // Data structure to enable component index access with entity id and vice versa.
        std::unordered_map<Entity, size_t> _entityToIndexMap{};
        std::unordered_map<size_t, Entity> _indexToEntityMap{};

        size_t _numValidEntities{}; ///< Total Entities in the array.
    };
} // namespace ecs
