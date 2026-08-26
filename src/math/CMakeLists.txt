add_library(SimpleMath INTERFACE
        math/SimpleMath.h
        math/vec/Vec2.h
        math/vec/Vec3.h
        math/Rotations.h
        math/Utils.h
)

target_include_directories(SimpleMath INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})