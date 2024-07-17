cmake_minimum_required(VERSION 3.5)
project(finite_diffs)

include_directories(include)
add_executable(${PROJECT_NAME} src/main.cpp src/utils.cpp src/solver.cpp)