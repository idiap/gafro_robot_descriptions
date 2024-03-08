This repository contains classes of different robot descriptions for the usage with the gafro library.

Currently available robots: 
    - FrankaEmikaRobot
    - AnymalC
    - Atlas
    - LeapHand
    - UR5


The descriptions and mesh files are located in the assets folder. 

## Installation

    mkdir build && cd build
    cmake ..
    make
    sudo make install

## Usage 

Link to this library. 
    
    find_package(gafro_robot_descriptions)
    target_link_libraries(TARGET gafro_robot_descriptions::gafro_robot_descriptions)

Include the header.

    #include <gafro_robot_descriptions/gafro_robot_descriptions.hpp>

Load a specific robot e.g.

    gafro::FrankaEmikaRobot<double> panda;