cmake_minimum_required(VERSION 3.12)
project(robotarm)

set(CMAKE_CXX_STANDARD 14)

add_executable(robotarm main.cpp Arm.cpp Arm.h ArmSegment.cpp ArmSegment.h)