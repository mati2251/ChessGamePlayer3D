cmake_minimum_required(VERSION 3.15)
project(asteroid_3d)
set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

include_directories(src)
include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${GLFW_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})

set(SOURCES
        src/main_file.cpp
        src/shaderprogram/shaderprogram.cpp)

add_executable(main_file ${SOURCES})

target_link_libraries(main_file
        ${OPENGL_LIBRARIES}
        glfw
        ${GLEW_LIBRARIES}
        )