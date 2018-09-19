cmake_minimum_required(VERSION 3.12)
project(robotarm)

set(CMAKE_CXX_STANDARD 14)

add_executable(robotarm main.cpp Arm.cpp Arm.h ArmSegment.cpp ArmSegment.h)

set(CMAKE_MODULE_PATH "/usr/local/Cellar/sfml/2.4.2_1/share/SFML/cmake/Modules" ${CMAKE_MODULE_PATH})
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(robotarm ${SFML_LIBRARIES})
endif()