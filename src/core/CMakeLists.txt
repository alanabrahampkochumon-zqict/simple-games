add_library(EngineCore STATIC
        Dummy.cpp # TODO: REMOVE as linker needs atleast one compilation unit
        ecs2/entity/Entity.h
        ecs2/Registry.h
        ecs2/DenseArray.h
        ecs2/SparseArray.h
        ecs2/ComponentArray.h
        ecs2/entity/EntityManager.h
        ecs2/entity/Entity.h
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
