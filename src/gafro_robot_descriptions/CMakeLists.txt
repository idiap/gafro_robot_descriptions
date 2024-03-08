configure_file(${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}_package_config.h.in "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}_package_config.hpp")

find_package(gafro REQUIRED)

add_library(${PROJECT_NAME} SHARED
    ${PROJECT_NAME}.cpp
    SystemVisual.cpp
)

target_compile_options(${PROJECT_NAME}
	PUBLIC
    "-Wall"
    "-Wextra"
    "-Werror=vla"
    "-Wno-unused-function"
    "-Wno-missing-braces"
    "-Wno-unknown-pragmas"
    "-Wno-parentheses"
    "-pedantic"
    "-Wconversion"
    "-Werror=pedantic"
    "-O2"
)

include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES
  VERSION ${${PROJECT_NAME}_VERSION}
  SOVERSION 1
  INTERFACE_${PROJECT_NAME}_MAJOR_VERSION 1
)

target_include_directories(${PROJECT_NAME}
	PUBLIC
		$<INSTALL_INTERFACE:${${PROJECT_NAME}_PREFIX_INCLUDE}>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}>
		$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
    $<BUILD_INTERFACE:${YAML_CPP_INCLUDE_DIRS}>
	PRIVATE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>/..
)

target_include_directories(${PROJECT_NAME} 
	SYSTEM PRIVATE
)

target_link_libraries(${PROJECT_NAME}
	PUBLIC 
    gafro::gafro
    ${YAML_CPP_LIBRARIES}
)

install(
	FILES 
    "${PROJECT_NAME}.hpp"
    FrankaEmikaRobot.hpp
    UR5.hpp
    AnymalC.hpp
    Atlas.hpp
    LeapHand.hpp
    SystemVisual.hpp
		"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}_package_config.hpp" 
	DESTINATION 
		${${PROJECT_NAME}_PREFIX_INCLUDE}/${PROJECT_NAME} 
	COMPONENT 
		Devel
)

add_subdirectory(serialization)