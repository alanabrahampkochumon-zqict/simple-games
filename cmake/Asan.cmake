include_guard()
option(ASAN "Enable ASan" OFF) # Option to enable ASAN

add_library(${PROJECT_NAME}-ASan INTERFACE) # Used for linking ASan

if (ASAN)
    # Enables Address Sanitizer for all the projects globally.
    message(STATUS "Turning on Address Sanitizer for Debug Builds")
    if (MSVC AND NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        target_compile_options(${PROJECT_NAME}-StrictWarnings INTERFACE $<$<CONFIG:Debug>:/fsanitize=address;/Zi>)
        target_link_options(${PROJECT_NAME}-StrictWarnings INTERFACE $<$<CONFIG:Debug>:/INCREMENTAL:NO>)
    else ()
        target_compile_options(${PROJECT_NAME}-StrictWarnings INTERFACE $<$<CONFIG:Debug>:-fsanitize=address;-fno-omit-frame-pointer>)
        target_link_options(${PROJECT_NAME}-StrictWarnings INTERFACE $<$<CONFIG:Debug>:-fsanitize=address>)
    endif ()
endif ()