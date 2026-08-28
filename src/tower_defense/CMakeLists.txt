add_executable(TowerDefense
        Game.cpp
        Game.h
        Main.cpp

        components/Component.h

        actor/Actor.h
        actor/Actor.cpp
        components/AIComponent.cpp
        components/AIComponent.h
        components/AIState.h
        struct/Graph.h
)
target_compile_features(TowerDefense PRIVATE cxx_std_20)

target_include_directories(
        TowerDefense PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
        TowerDefense PRIVATE
        StrictWarnings
        SDL3::SDL3
        imgui
        SDL3_image::SDL3_image
        SimpleMath
)
