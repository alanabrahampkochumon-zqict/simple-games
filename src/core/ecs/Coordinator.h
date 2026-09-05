#pragma once
/**
 * @file Coordinator.h
 * @author Alan Abraham P Kochumon
 * @date Created on: September 04, 2026
 *
 * @brief Orchestrates all the ECS managers.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "EntityManager.h"
#include "system/SystemManager.h"

#include <memory>
// #include "components/ComponentManager.h" TODO: Add back once merged

namespace ecs
{
    class Coordinator
    {
    public:
        Coordinator()
            : // _componentManager{std::make_unique<ComponentManager>()}, TODO: add back once merged
              _entityManager{ std::make_unique<EntityManager>() },
              _systemManager{ std::make_unique<system::SystemManager>() }
        {}

        [[nodiscard]] constexpr Entity createEntity() noexcept { return _entityManager->create(); }

        constexpr void destroyEntity(const Entity entity) const noexcept
        {
            _entityManager->destroy(entity);
            _systemManager->entityDestroyed(entity);
            // _componentManager->entityDestroyed(entity); TODO: add back once merged
        }

        template <typename T>
        constexpr void registerComponent() noexcept
        {
            // _componentManager->registerComponent<T>(); TODO: add back once merged
        }

        template <typename T>
        constexpr void addComponent(const Entity entity, [[maybe_unused]] const T& component) noexcept
        {
            // _componentManager->addComponent<T>(entity, component); TODO: add back once merged

            const auto signature = _entityManager->getSignature(entity);
            // signature.set(_componentManager->getComponentType<T>(), true); TODO: add back once merged
            _entityManager->setSignature(entity, signature);
            _systemManager->entitySignatureChanged(entity, signature);
        }


        template <typename T>
        constexpr void removeComponent(const Entity entity) noexcept
        {
            // _componentManager.removeComponent(entity); TODO: add back once merged

            const auto signature = _entityManager->getSignature(entity);
            // signature.set(_componentManager->getComponentType<T>(), true); TODO: add back once merged
            _entityManager->setSignature(entity, signature);
            _systemManager->entitySignatureChanged(entity, signature);
        }


        // template <typename T> TODO: add back once merged
        // constexpr T& getComponent(const Entity entity) noexcept
        // {
        //     return _componentManager->getComponent(entity);
        // }


        // template <typename T> TODO: add back once merged
        // constexpr comp::ComponentType getComponentType() noexcept
        // {
        //         return _componentManager->getComponentType<T>();
        // }


        template <typename T>
        [[nodiscard]] constexpr std::shared_ptr<T> registerSystem() noexcept
        { return _systemManager->registerSystem<T>(); }


        template <typename T>
        constexpr void setSystemSignature(const Signature signature) const noexcept
        { _systemManager->setSignature<T>(signature); }

    private:
        // std::unique_ptr<ComponentManager> _componentManager; TODO: add back once merged
        std::unique_ptr<EntityManager> _entityManager;
        std::unique_ptr<system::SystemManager> _systemManager;
    };
} // namespace ecs
