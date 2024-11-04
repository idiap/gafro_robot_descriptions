@PACKAGE_INIT@

get_filename_component(gafro_robot_descriptions_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)

if(NOT TARGET gafro_robot_descriptions::gafro_robot_descriptions)
    include("${gafro_robot_descriptions_CMAKE_DIR}/gafro_robot_descriptions-config-targets.cmake")
    include("${gafro_robot_descriptions_CMAKE_DIR}/gafro_robot_descriptions-packages.cmake")
endif()

get_target_property(gafro_robot_descriptions_INCLUDE_DIRS gafro_robot_descriptions::gafro_robot_descriptions INTERFACE_INCLUDE_DIRECTORIES)

check_required_components(gafro_robot_descriptions)