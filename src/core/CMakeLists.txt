add_library(EngineCore STATIC
        ecs/ECS.h
        ecs/Entity.h
        ecs/EntityManager.h
        ecs/Signature.h

        ecs/components/Component.h
        ecs/components/Transform.h
        ecs/components/ComponentArray.h
        ecs/components/ComponentManager.h
        ecs/system/SystemManager.h
        ecs/system/System.h
        ecs/Coordinator.h
        ecs/system/RenderingSystem.h
        ecs/system/InputSystem.h
        Dummy.cpp
        ecs2/Entity.h
        ecs2/Registry.h
        ecs2/DenseArray.h # TODO: REMOVE as linker needs atleast one compilation unit
)
target_compile_features(EngineCore PRIVATE cxx_std_20)

target_include_directories(
        EngineCore PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
        EngineCore PRIVATE
        StrictWarnings
        SDL3::SDL3
        imgui
        SDL3_image::SDL3_image
        SimpleMath
)
