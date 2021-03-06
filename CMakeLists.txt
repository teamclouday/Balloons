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
# clear directory
file(REMOVE_RECURSE "${CMAKE_SOURCE_DIR}/bin")

# set preference for linux
if(UNIX)
    set(OpenGL_GL_PREFERENCE "LEGACY")
endif(UNIX)

# configure GLUT
option(FREEGLUT_BUILD_DEMOS "Controls whether the demos are built or not" OFF)
option(FREEGLUT_BUILD_SHARED_LIBS "Build freeglut as a shared library" OFF)
option(FREEGLUT_BUILD_STATIC_LIBS "Build freeglut as a static library" ON)
add_subdirectory("${CMAKE_SOURCE_DIR}/external/glut/freeglut-3.2.1")

# configure irrklang
if(WIN32)
    if(MSVC)
        file(GLOB irrklangLIB "${CMAKE_SOURCE_DIR}/external/irrklang/irrKlang-64bit-1.6.0/bin/winx64-visualStudio/*.dll")
        file(COPY ${irrklangLIB} DESTINATION "${CMAKE_SOURCE_DIR}/bin")
        link_directories("${CMAKE_SOURCE_DIR}/external/irrklang/irrKlang-64bit-1.6.0/lib/Winx64-visualStudio/")
    else()
        message("Unsupported system (Windows but not MSVC)" FATAL_ERROR)    
    endif()
elseif(UNIX)
    if(APPLE)
        file(GLOB irrklangLIB "${CMAKE_SOURCE_DIR}/external/irrklang/irrKlang-64bit-1.6.0/bin/macosx-gcc/*.dylib")
        file(COPY ${irrklangLIB} DESTINATION "${CMAKE_SOURCE_DIR}/bin")
        link_directories("${CMAKE_SOURCE_DIR}/external/irrklang/irrKlang-64bit-1.6.0/bin/macosx-gcc/")
    else()
        file(GLOB irrklangLIB "${CMAKE_SOURCE_DIR}/external/irrklang/irrKlang-64bit-1.6.0/bin/linux-gcc-64/*.so")
        file(COPY ${irrklangLIB} DESTINATION "${CMAKE_SOURCE_DIR}/bin")
        link_directories("${CMAKE_SOURCE_DIR}/external/irrklang/irrKlang-64bit-1.6.0/bin/linux-gcc-64/")
    endif()
else()
    message("Unsupported system (not Windows, Linux or MacOS)" FATAL_ERROR)
endif()

# configure OpenGL
find_package(OpenGL REQUIRED)

# configure pThread
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# configure assets
file(COPY "${CMAKE_SOURCE_DIR}/assets" DESTINATION "${CMAKE_SOURCE_DIR}/bin")

# prepare source files
file(GLOB SRC_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_executable(balloon ${SRC_FILES})

target_include_directories(balloon PRIVATE
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_SOURCE_DIR}/external/glut/freeglut-3.2.1/include"
    "${CMAKE_SOURCE_DIR}/external/glm/glm"
    "${CMAKE_SOURCE_DIR}/external/irrklang/irrKlang-64bit-1.6.0/include"
    "${CMAKE_SOURCE_DIR}/external/tinygltf/tinygltf-2.5.0"
    "${CMAKE_SOURCE_DIR}/external/stb"
)

target_link_libraries(balloon
    freeglut_static
    OpenGL::GL
    OpenGL::GLU
    Threads::Threads
)

if(MSVC)
    target_link_libraries(balloon irrKlang.lib)
elseif(APPLE)
    target_link_libraries(balloon libirrklang.dylib)
else()
    target_link_libraries(balloon libIrrKlang.so)
endif()