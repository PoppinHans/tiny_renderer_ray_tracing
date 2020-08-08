cmake_minimum_required(VERSION 3.15)
project(tiny_renderer_ray_tracing)

set(CMAKE_CXX_STANDARD 11)

file(GLOB SRC ${PROJECT_SOURCE_DIR}/*.cpp)

add_executable(tiny_renderer_ray_tracing ${SRC})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/cmake-build-debug)