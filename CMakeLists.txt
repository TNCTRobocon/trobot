cmake_minimum_required(VERSION 3.10.0)

# CMake Options
enable_testing()

# C++ Options
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_definitions(TRB_PSEUDO)

project(trobot CXX)
add_subdirectory(src)
add_subdirectory(test)
