add_executable(FirstPersonShooter
        Game.cpp
        Game.h
        Main.cpp
)
target_compile_features(FirstPersonShooter PRIVATE cxx_std_20)

target_include_directories(
        FirstPersonShooter PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
        FirstPersonShooter PRIVATE
        StrictWarnings
        SDL3::SDL3
        imgui
        SDL3_image::SDL3_image
        SimpleMath
        EngineCore
)
