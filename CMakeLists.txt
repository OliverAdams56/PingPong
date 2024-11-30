cmake_minimum_required(VERSION 3.15)
project(PingPong)

set(CMAKE_CXX_STANDARD 17)

# Set build type
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build" FORCE)
endif()

# Fetch raylib
set(RAYLIB_VERSION 5.0)
include(FetchContent)
FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
)
FetchContent_MakeAvailable(raylib)

# Add the PingPong executable
add_executable(PingPong main.cpp)

# Link raylib
target_link_libraries(PingPong PRIVATE raylib)

# Include raylib headers
target_include_directories(PingPong PRIVATE ${raylib_SOURCE_DIR}/src)

# Suppress OpenGL deprecation warnings (macOS)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-deprecated-declarations")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")
