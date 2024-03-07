target_sources(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/Visual.cpp
)

if (gafro_USE_YAML_CPP)
    target_sources(${PROJECT_NAME}
        PRIVATE
            ${CMAKE_CURRENT_LIST_DIR}/SystemSerialization.cpp
            ${CMAKE_CURRENT_LIST_DIR}/FilePath.cpp
    )
endif()

# Only do that when using the gafro source code directly, not from a submodule
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    install(
        FILES
            SystemSerialization.hpp
            Visual.hpp
            FilePath.hpp
        DESTINATION
            ${${PROJECT_NAME}_PREFIX_INCLUDE}/gafro_robot_descriptions/serialization
        COMPONENT
            Devel
    )
endif()
