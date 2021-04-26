cmake_minimum_required(VERSION 3.15)

project(Balloons VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set compile flags for gcc system
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall")

# set output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
if(MSVC)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin")
endif(MSVC)

# configure GLUT
option(FREEGLUT_BUILD_DEMOS "Controls whether the demos are built or not" OFF)
option(FREEGLUT_BUILD_SHARED_LIBS "Build freeglut as a shared library" OFF)
option(FREEGLUT_BUILD_STATIC_LIBS "Build freeglut as a static library" ON)
add_subdirectory("${CMAKE_SOURCE_DIR}/external/glut/freeglut-3.2.1")

# configure OpenGL
find_package(OpenGL REQUIRED)

# prepare source files
file(GLOB SRC_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_executable(balloon ${SRC_FILES})

target_include_directories(balloon PRIVATE
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_SOURCE_DIR}/external/glut/freeglut-3.2.1/include"
    "${CMAKE_SOURCE_DIR}/external/glm/glm"
)

target_link_libraries(balloon
    freeglut_static
    OpenGL::GL
    OpenGL::GLU
)