cmake_minimum_required(VERSION 3.10)

# for Google Test
find_package(Threads REQUIRED)

# Download Google Test
include(${PROJECT_SOURCE_DIR}/cmake/DownloadProject/DownloadProject.cmake)
download_project(PROJ googletest
                GIT_REPOSITORY https://github.com/google/googletest.git
                GIT_TAG master
                UPDATE_DISCONNECTED 1
)

# To use google test

include(GoogleTest)
add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
add_subdirectory(parts)
include_directories(${PROJECT_SOURCE_DIR}/inc ${GTEST_INCLUDE_DIRS})
