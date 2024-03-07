add_executable(unittests
    main.cpp
)

target_compile_options(unittests PUBLIC "-O3")

target_include_directories(unittests
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>/src
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
        $<BUILD_INTERFACE:${YAML_CPP_INCLUDE_DIRS}>
        $<INSTALL_INTERFACE:${YAML_CPP_INCLUDE_DIRS}>
)

target_link_libraries(unittests
    PRIVATE
        gafro
        $<BUILD_INTERFACE:${YAML_CPP_LIBRARIES}>
        $<INSTALL_INTERFACE:${YAML_CPP_LIBRARIES}>
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(unittests PUBLIC "-Wall" "-Wno-class-memaccess")
endif()

add_subdirectory(algebra)
add_subdirectory(optimization)
add_subdirectory(physics)
add_subdirectory(robots)

# Run the unit tests
add_custom_target(run-unittests ALL unittests
                  DEPENDS unittests
                  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                  COMMENT "Unit testing..." VERBATIM
)
