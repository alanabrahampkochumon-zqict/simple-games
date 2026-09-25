#pragma once
/**
 * @file Registry.h
 * @author Alan Abraham P Kochumon
 * @date Created on: September 12, 2026
 *
 * @brief Registry for managing entities, components and their sparse-sets.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "DenseArray.h"
#include "component/ComponentArray.h"
#include "ds/SparseArray.h"
#include "entity/Entity.h"
#include "entity/EntityManager.h"

#include <cstdint>
#include <memory>
#include <vector>

namespace u_ecs
{
    class Registry
    {
    public:
        [[nodiscard]] constexpr Entity createEntity() noexcept { return _entityManager.create(); }

        constexpr void destroyEntity(const Entity entity) noexcept
        {
            _entityManager.destroy(entity);

            /// Loop through the component array and remove them.
            for (const auto& comp : _components)
            {
                comp->remove(entity);
            }
        }

        // template<typename Component>
        // constexpr void add(const Entity entity) noexcept
        // {
        //     if (_entityManager.getSignature(entity) & )
        // }

        template <typename Component>
        [[nodiscard]] constexpr Component get(Entity entity) const noexcept
        { return _components<Component>.get(entity); }


        template <typename Component>
        [[nodiscard]] constexpr Component getAll() const noexcept
        { return _components<Component>._componentDenseArray.storage; }

        template <typename Component>
        constexpr void add(Entity entity, Component component) const noexcept
        { _components<Component>.add(entity, component); }


        template <typename Component>
        constexpr void remove(Entity entity, Component component) const noexcept
        { _components<Component>.remove(entity, component); }

    private:
        std::vector<std::unique_ptr<BaseComponentArray>> _components;

        EntityManager _entityManager{};

        // Sparse Set set with paging
    };

} // namespace u_ecs
  // registry.registerComponent<Type>();
