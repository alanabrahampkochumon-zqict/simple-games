include(u_ecs/MircoECS.cmake)

add_library(EngineCore STATIC
        Dummy.cpp # TODO: REMOVE as linker needs atleast one compilation unit
        ${U_ECS_FILES}
)
target_compile_features(EngineCore PRIVATE cxx_std_20)

target_include_directories(
        EngineCore PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
        EngineCore PRIVATE
        ${PROJECT_NAME}-StrictWarnings
        SDL3::SDL3
        imgui
        SDL3_image::SDL3_image
        SimpleMath
)
