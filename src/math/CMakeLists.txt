add_library(SimpleMath INTERFACE
        math/SimpleMath.h
        math/vec/Vec2.h
        math/vec/Vec3.h
        math/vec/Vec4.h
        math/Rotations.h
        math/Utils.h
        math/mat/Mat4.h
        math/Quat.h
)

target_include_directories(SimpleMath INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})