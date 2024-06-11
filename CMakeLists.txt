cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 23)

project(Chess)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

set(copy_source_dir "${CMAKE_SOURCE_DIR}")
set(copy_dest_dir "${CMAKE_BINARY_DIR}")
set(copy_file_name "resources")

add_subdirectory(src)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
