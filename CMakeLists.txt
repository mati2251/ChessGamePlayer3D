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
        src/shaderprogram/shaderprogram.cpp
        src/chessboard/chessboard.cpp
        src/shaders_container/shaders_container.cpp
        src/program_state/program_state.cpp
        src/rotate_controller/rotate_controller.cpp
        src/obj_reader/obj_reader.cpp
        src/obj_reader/mesh/mesh.cpp
        src/texture/texture.cpp
        src/lodepng/lodepng.cpp
        src/figure/figure.cpp
        src/texture_container/texture_container.cpp
        src/game/game.cpp src/game/game.h)

add_executable(main_file ${SOURCES})

target_link_libraries(main_file
        ${OPENGL_LIBRARIES}
        glfw
        ${GLEW_LIBRARIES}
        assimp
        )