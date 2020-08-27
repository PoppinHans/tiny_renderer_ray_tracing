cmake_minimum_required(VERSION 3.15)
project(tiny_renderer_ray_tracing)

set(CMAKE_CXX_STANDARD 11)

file(GLOB SRC
        ${PROJECT_SOURCE_DIR}/*.cpp
        ${PROJECT_SOURCE_DIR}/src/*.cpp
        )

add_executable(tiny_renderer_ray_tracing ${SRC} main.cc)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/cmake-build-debug)

add_subdirectory(test)