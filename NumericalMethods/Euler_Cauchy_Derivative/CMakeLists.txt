cmake_minimum_required(VERSION 3.0)
project(euler)

include_directories(include)
add_executable(${PROJECT_NAME} src/main.cpp src/solver.cpp src/utils.cpp)