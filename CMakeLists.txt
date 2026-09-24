cmake_minimum_required(VERSION 3.28)

project(PathfindingVisualizer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# This project uses #include, not C++20 modules. Without this, CMake adds
# GCC-only module-scanning flags (-fmodules-ts, -fmodule-mapper=, -fdeps-format=)
# to every compile command, which clangd cannot parse and reports as errors.
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

# SFML is fetched and built from source, so there is nothing to install
# system-wide and nothing for PATH to find. Static linking means no DLLs
# need to sit next to the .exe either.
include(FetchContent)

set(BUILD_SHARED_LIBS OFF)
set(SFML_BUILD_AUDIO OFF)
set(SFML_BUILD_NETWORK OFF)

FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM
)
FetchContent_MakeAvailable(SFML)

add_executable(PathfindingVisualizer
    src/main.cpp
    src/Application.cpp
    src/Grid.cpp
    src/Algo.cpp
    src/Node.cpp
)

target_include_directories(PathfindingVisualizer PRIVATE include)

# Graphics pulls in Window and System transitively.
target_link_libraries(PathfindingVisualizer PRIVATE SFML::Graphics)

# Fold the MinGW runtime (libstdc++, libgcc, winpthread) into the .exe so it
# does not depend on the compiler's bin directory being on PATH.
if(MINGW)
    target_link_options(PathfindingVisualizer PRIVATE -static)
endif()
