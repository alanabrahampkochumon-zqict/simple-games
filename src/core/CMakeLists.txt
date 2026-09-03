add_library(EngineCore STATIC
        ecs/ECS.h
        ecs/Entity.h
        ecs/Signature.h

        ecs/components/Component.h
        ecs/components/Transform.h
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
