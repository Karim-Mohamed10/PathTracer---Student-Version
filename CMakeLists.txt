cmake_minimum_required(VERSION 3.10.0)
project(path-tracer VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/material.cpp
    src/shapes.cpp
    src/backgrounds.cpp
    src/aabb.cpp
    src/camera.cpp
    src/bvh.cpp
    src/scene.cpp
    src/image.cpp
    src/pathtracer.cpp
    src/scene_setup.cpp
)
target_include_directories(${PROJECT_NAME} PRIVATE
    src
    vendor/glm
    vendor/stb
)