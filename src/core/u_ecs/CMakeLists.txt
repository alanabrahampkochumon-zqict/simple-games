set(ECS_LIB_NAME MicroECS)

add_library(${ECS_LIB_NAME} INTERFACE
        component/BaseComponentArray.h
        component/ComponentArray.h
        component/ComponentManager.h
        component/ComponentType.h
        component/SparseSet.h

        entity/Entity.h
        entity/EntityManager.h
        entity/Signature.h

        Registry.h
)

target_include_directories(${ECS_LIB_NAME} INTERFACE ${CMAKE_CURRENT_LIST_DIR}) # TODO: Update

target_compile_features(${ECS_LIB_NAME} INTERFACE cxx_std_20)
set_target_properties(${ECS_LIB_NAME} PROPERTIES CXX_STANDARD_REQUIRED ON CXX_EXTENSIONS OFF)

add_library(${ECS_LIB_NAME}::${ECS_LIB_NAME} ALIAS ${ECS_LIB_NAME})
