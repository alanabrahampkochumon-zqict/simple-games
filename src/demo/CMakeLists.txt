add_executable(DemoApp
        Game.cpp
        Game.h)
target_compile_features(DemoApp PRIVATE cxx_std_20)


target_sources(
        DemoApp
        PRIVATE
            Main.cpp

        PRIVATE
        FILE_SET HEADERS
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
        FILES
            Utils.h
)

target_include_directories(
        DemoApp PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(
        DemoApp PRIVATE
        StrictWarnings
        SDL3::SDL3
        imgui
        SDL3_image::SDL3_image
)
