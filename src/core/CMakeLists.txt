add_library(EngineCore STATIC
        Dummy.cpp # TODO: REMOVE as linker needs atleast one compilation unit
        u_ecs/entity/Entity.h
        u_ecs/entity/EntityManager.h
        u_ecs/entity/Signature.h

        u_ecs/component/ComponentManager.h
        u_ecs/component/ComponentArray.h

        u_ecs/ds/SparseArray.h
        u_ecs/ds/DenseArray.h

        u_ecs/Registry.h
        u_ecs/Config.h
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
