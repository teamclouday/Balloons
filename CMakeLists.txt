cmake_minimum_required(VERSION 3.15)

project(Balloons VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

file(GLOB SRC_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_executable(balloon ${SRC_FILES})

target_include_directories(balloon PRIVATE
    "${CMAKE_SOURCE_DIR}/include"
)

target_link_libraries(balloon
    GLUT::GLUT
    OpenGL::GL
    OpenGL::GLU
)